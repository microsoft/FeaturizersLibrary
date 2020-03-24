# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

import itertools
import os
import sys
import textwrap

from collections import OrderedDict

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import FileSystem
from CommonEnvironment import Interface
from CommonEnvironment import StringHelpers

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from Plugin import Plugin as PluginBase, TypeVisitor as TypeVisitorBase


# ----------------------------------------------------------------------
@Interface.staticderived
class Plugin(PluginBase):
    # ----------------------------------------------------------------------
    # |  Properties
    Name                                    = Interface.DerivedProperty("MLNet")
    Description                             = Interface.DerivedProperty(
        "Generates code used during the Shared Library import/export layer interfacing with the shared C++ functionality",
    )

    # ----------------------------------------------------------------------
    # |  Methods
    @staticmethod
    @Interface.override
    def Generate(open_file_func, global_custom_structs, global_custom_enums, data, output_dir, status_stream):
        result_code = 0

        status_stream.write("Preprocessing data for ML.NET...")
        with status_stream.DoneManager():
            # Convert the types into the corresponding C#/CPP types that will be used
            # in the Shared Library interface.
            csharp_data = []
            unsupported_types = set()
            for items in data:
                csharp_data.append(
                    [_FillList(item, status_stream, unsupported_types, global_custom_structs, global_custom_enums) for item in items],
                )

        for desc, func in [("Generating C# files...", _GenerateCSharpFile)]:
            status_stream.write(desc)
            with status_stream.DoneManager(
                suffix="\n",
            ) as dm:
                for index, (items, items_csharp_data) in enumerate(
                    zip(data, csharp_data),
                ):
                    dm.stream.write(
                        "Processing '{}' ({} of {})...".format(
                            items[0].name,
                            index + 1,
                            len(data),
                        ),
                    )
                    with dm.stream.DoneManager() as this_dm:
                        this_dm.result = func(
                            open_file_func,
                            output_dir,
                            items,
                            items_csharp_data,
                            this_dm.stream,
                        )

                if dm.result < 0:
                    return dm.result

                result_code = result_code or dm.result

        return result_code


# ----------------------------------------------------------------------
def _FillList(item, status_stream, unsupported_types, global_custom_structs, global_custom_enums):
    try:
        return CSharpData(item, global_custom_structs, global_custom_enums)
    except Exception as e:
        if "is not a supported type" in e.args[0] and hasattr(item, "custom_structs"):
            if item.custom_structs[0].name not in unsupported_types:
                status_stream.write(
                    "{}\tUnsupported type '{}' found in class '{}'. The corrsponding methods will not be generated for this type.\n".format(
                        "\n" if len(unsupported_types) == 0 else "",
                        item.custom_structs[0].name,
                        item.estimator_name,
                    ),
                )
                unsupported_types.add(item.custom_structs[0].name)
        else:
            raise e


def _GenerateCSharpFile(open_file_func, output_dir, items, csharp_data_items, output_stream):
    baseName = items[0].name.replace("Featurizer", "")
    transformerName = baseName + "Transformer"
    estimatorName = baseName + "Estimator"
    entrypointName = baseName + "Entrypoint"

    with open_file_func(os.path.join(output_dir, "{}.cs".format(items[0].name)), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                // Licensed to the .NET Foundation under one or more agreements.
                // The .NET Foundation licenses this file to you under the MIT license.
                // See the LICENSE file in the project root for more information.

                using System;
                using System.Collections.Generic;
                using System.Linq;
                using System.Runtime.InteropServices;
                using System.Security;
                using System.Text;
                using Microsoft.ML;
                using Microsoft.ML.CommandLine;
                using Microsoft.ML.Data;
                using Microsoft.ML.EntryPoints;
                using Microsoft.ML.Featurizers;
                using Microsoft.ML.Internal.Utilities;
                using Microsoft.ML.Runtime;
                using Microsoft.ML.Transforms;
                using Microsoft.Win32.SafeHandles;
                using static Microsoft.ML.Featurizers.CommonExtensions;

                [assembly: LoadableClass(typeof({transformerName}), null, typeof(SignatureLoadModel),
                    {transformerName}.UserName, {transformerName}.LoaderSignature)]

                [assembly: LoadableClass(typeof(IRowMapper), typeof({transformerName}), null, typeof(SignatureLoadRowMapper),
                {transformerName}.UserName, {transformerName}.LoaderSignature)]

                [assembly: EntryPointModule(typeof({entrypointName}))]

                namespace Microsoft.ML.Featurizers
                {{
                    public static class {baseName}ExtensionClass
                    {{
                        public static {estimatorName} {transformerName}(this TransformsCatalog catalog, string outputColumnName, string inputColumnName = null /* Insert additional params here as needed*/{optionalInput})
                        {{
                            var options = new {estimatorName}.Options
                            {{
                                Columns = new {estimatorName}.Column[] {{ new {estimatorName}.Column() {{ Name = outputColumnName, Source = inputColumnName ?? outputColumnName }} }},
                                {optionalInputOptions}
                                /* Codegen: add extra options here as needed */
                            }};

                            return new {estimatorName}(CatalogUtils.GetEnvironment(catalog), options);
                        }}

                        public static {estimatorName} {transformerName}(this TransformsCatalog catalog, InputOutputColumnPair[] columns /* Insert additional params here as needed*/{optionalInput})
                        {{
                            var options = new {estimatorName}.Options
                            {{
                                Columns = columns.Select(x => new {estimatorName}.Column {{ Name = x.OutputColumnName, Source = x.InputColumnName ?? x.OutputColumnName }}).ToArray(),
                                {optionalInputOptions}
                                /* Codegen: add extra options here as needed */
                            }};

                            return new {estimatorName}(CatalogUtils.GetEnvironment(catalog), options);
                        }}
                    }}

                    public class {estimatorName} : IEstimator<{transformerName}>
                    {{
                        private Options _options;
                        private readonly IHost _host;

                        /* Codegen: Add additional needed class members here */

                        #region Options

                        /* If not one to one need to change this */
                        internal sealed class Column : OneToOneColumn
                        {{
                            internal static Column Parse(string str)
                            {{
                                Contracts.AssertNonEmpty(str);

                                var res = new Column();
                                if (res.TryParse(str))
                                    return res;
                                return null;
                            }}

                            internal bool TryUnparse(StringBuilder sb)
                            {{
                                Contracts.AssertValue(sb);
                                return TryUnparseCore(sb);
                            }}
                        }}

                        internal sealed class Options: TransformInputBase
                        {{
                            [Argument(ArgumentType.Multiple | ArgumentType.Required, HelpText = "New column definition (optional form: name:src)",
                                Name = "Column", ShortName = "col", SortOrder = 1)]
                            public Column[] Columns;

                            {optionalInputOptionClass}

                            /* Codegen: Add additonal options as needed */
                        }}

                        #endregion

                        internal {estimatorName}(IHostEnvironment env, Options options)
                        {{
                            Contracts.CheckValue(env, nameof(env));
                            _host = env.Register(nameof({estimatorName}));
                            Contracts.CheckNonEmpty(options.Columns, nameof(options.Columns));
                            /* Codegen: Any other checks for options go here */

                            _options = options;
                        }}

                        public {transformerName} Fit(IDataView input)
                        {{
                            return new {transformerName}(_host, input, _options);
                        }}

                        public SchemaShape GetOutputSchema(SchemaShape inputSchema)
                        {{
                            var columns = inputSchema.ToDictionary(x => x.Name);

                            foreach (var column in _options.Columns)
                            {{
                                var inputColumn = columns[column.Source];

                                if (!{transformerName}.TypedColumn.IsColumnTypeSupported(inputColumn.ItemType.RawType))
                                    throw new InvalidOperationException($"Type {{inputColumn.ItemType.RawType.ToString()}} for column {{column.Name}} not a supported type.");

                                /* Codegen: Do correct schema mapping here */

                            }}
                            return new SchemaShape(columns.Values);
                        }}
                    }}

                    public sealed class {transformerName} : RowToRowTransformerBase, IDisposable
                    {{
                        #region Class data members

                        internal const string Summary = ""; /* Insert summary here */
                        internal const string UserName = "{transformerName}";
                        internal const string ShortName = "{transformerName}";
                        internal const string LoadName = "{transformerName}";
                        internal const string LoaderSignature = "{transformerName}";

                        private TypedColumn[] _columns;
                        private {estimatorName}.Options _options;

                        #endregion

                        internal {transformerName}(IHostEnvironment host, IDataView input, {estimatorName}.Options options) :
                            base(host.Register(nameof({transformerName})))
                        {{
                            var schema = input.Schema;
                            _options = options;

                            _columns = options.Columns.Select(x => TypedColumn.CreateTypedColumn(x.Name, x.Source, schema[x.Source].Type.RawType.ToString(), this)).ToArray();
                            foreach (var column in _columns)
                            {{
                                column.CreateTransformerFromEstimator(input);
                            }}
                        }}

                        // Factory method for SignatureLoadModel.
                        internal {transformerName}(IHostEnvironment host, ModelLoadContext ctx) :
                            base(host.Register(nameof({transformerName})))
                        {{
                            Host.CheckValue(ctx, nameof(ctx));
                            ctx.CheckAtModel(GetVersionInfo());

                            /* Codegen: Edit this format as needed */
                            // *** Binary format ***
                            // int number of column pairs
                            // for each column pair:
                            //      string output column  name
                            //      string input column name
                            //      column type
                            //      int length of c++ byte array
                            //      byte array from c++

                            var columnCount = ctx.Reader.ReadInt32();

                            _options = new {estimatorName}.Options();
                            /* Codegen: Load any additional Options members here */

                            _columns = new TypedColumn[columnCount];
                            for (int i = 0; i < columnCount; i++)
                            {{
                                _columns[i] = TypedColumn.CreateTypedColumn(ctx.Reader.ReadString(), ctx.Reader.ReadString(), ctx.Reader.ReadString(), this);

                                // Load the C++ state and create the C++ transformer.
                                var dataLength = ctx.Reader.ReadInt32();
                                var data = ctx.Reader.ReadByteArray(dataLength);
                                _columns[i].CreateTransformerFromSavedData(data);
                            }}
                        }}

                        // Factory method for SignatureLoadRowMapper.
                        private static IRowMapper Create(IHostEnvironment env, ModelLoadContext ctx, DataViewSchema inputSchema)
                            => new {transformerName}(env, ctx).MakeRowMapper(inputSchema);

                        private protected override IRowMapper MakeRowMapper(DataViewSchema schema) => new Mapper(this, schema);

                        private static VersionInfo GetVersionInfo()
                        {{
                            /* Codegen: Change these as needed */
                            return new VersionInfo(
                                modelSignature: "Enter 8 character long name here", /* Codegen: Enter * character name here */
                                verWrittenCur: 0x00010001, /* Codegen: Update version numbers as necessary */
                                verReadableCur: 0x00010001,
                                verWeCanReadBack: 0x00010001,
                                loaderSignature: LoaderSignature,
                                loaderAssemblyName: typeof({transformerName}).Assembly.FullName);
                        }}

                        private protected override void SaveModel(ModelSaveContext ctx)
                        {{
                            Host.CheckValue(ctx, nameof(ctx));
                            ctx.CheckAtModel();
                            ctx.SetVersionInfo(GetVersionInfo());

                            /* Codegen: Edit this format as needed */
                            // *** Binary format ***
                            // int number of column pairs
                            // for each column pair:
                            //      string output column  name
                            //      string input column name
                            //      column type
                            //      int length of c++ byte array
                            //      byte array from c++

                            ctx.Writer.Write(_columns.Count());

                            /* Codegen: Write any _options members needed here */

                            foreach (var column in _columns)
                            {{
                                ctx.Writer.Write(column.Name);
                                ctx.Writer.Write(column.Source);
                                ctx.Writer.Write(column.Type);

                                // Save C++ state
                                var data = column.CreateTransformerSaveData();
                                ctx.Writer.Write(data.Length);
                                ctx.Writer.Write(data);
                            }}
                        }}

                        public void Dispose()
                        {{
                            foreach (var column in _columns)
                            {{
                                column.Dispose();
                            }}
                        }}

                        #region ColumnInfo

                        #region BaseClass

                        internal abstract class TypedColumn : IDisposable
                        {{
                            internal readonly string Name;
                            internal readonly string Source;
                            internal readonly string Type;

                            /* Codegen: Fill in supported types */
                            private static readonly Type[] _supportedTypes = new Type[] {{ {supportedTypes} }};

                            /* Codegen: Any other needed members */

                            internal TypedColumn(string name, string source, string type)
                            {{
                                Name = name;
                                Source = source;
                                Type = type;
                            }}

                            internal abstract void CreateTransformerFromEstimator(IDataView input);
                            private protected abstract unsafe void CreateTransformerFromSavedDataHelper(byte* rawData, IntPtr dataSize);
                            private protected abstract bool CreateTransformerSaveDataHelper(out IntPtr buffer, out IntPtr bufferSize, out IntPtr errorHandle);
                            public abstract void Dispose();

                            public abstract Type ReturnType();

                            internal byte[] CreateTransformerSaveData()
                            {{

                                var success = CreateTransformerSaveDataHelper(out IntPtr buffer, out IntPtr bufferSize, out IntPtr errorHandle);
                                if (!success)
                                    throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));

                                using (var savedDataHandle = new SaveDataSafeHandle(buffer, bufferSize))
                                {{
                                    byte[] savedData = new byte[bufferSize.ToInt32()];
                                    Marshal.Copy(buffer, savedData, 0, savedData.Length);
                                    return savedData;
                                }}
                            }}

                            internal unsafe void CreateTransformerFromSavedData(byte[] data)
                            {{
                                fixed (byte* rawData = data)
                                {{
                                    IntPtr dataSize = new IntPtr(data.Count());
                                    CreateTransformerFromSavedDataHelper(rawData, dataSize);
                                }}
                            }}

                            internal static bool IsColumnTypeSupported(Type type)
                            {{
                                return _supportedTypes.Contains(type);
                            }}

                            internal static TypedColumn CreateTypedColumn(string name, string source, string type, {transformerName} parent)
                            {{
                                {typeFactory}
                                throw new InvalidOperationException($"Column {{name}} has an unsupported type {{type}}.");
                            }}
                        }}

                        internal abstract class TypedColumn<TSourceType, TOutputType> : TypedColumn
                        {{
                            internal TypedColumn(string name, string source, string type) :
                                base(name, source, type)
                            {{
                            }}

                            internal abstract TOutputType Transform(TSourceType input);
                            private protected abstract bool CreateEstimatorHelper(out IntPtr estimator, out IntPtr errorHandle);
                            private protected abstract bool CreateTransformerFromEstimatorHelper(TransformerEstimatorSafeHandle estimator, out IntPtr transformer, out IntPtr errorHandle);
                            private protected abstract bool DestroyEstimatorHelper(IntPtr estimator, out IntPtr errorHandle);
                            private protected abstract bool DestroyTransformerHelper(IntPtr transformer, out IntPtr errorHandle);
                            private protected abstract bool FitHelper(TransformerEstimatorSafeHandle estimator, TSourceType input, out FitResult fitResult, out IntPtr errorHandle);
                            private protected abstract bool CompleteTrainingHelper(TransformerEstimatorSafeHandle estimator, out FitResult fitResult, out IntPtr errorHandle);
                            private protected abstract bool IsTrainingComplete(TransformerEstimatorSafeHandle estimatorHandle);
                            private protected TransformerEstimatorSafeHandle CreateTransformerFromEstimatorBase(IDataView input)
                            {{
                                var success = CreateEstimatorHelper(out IntPtr estimator, out IntPtr errorHandle);
                                if (!success)
                                    throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));

                                using (var estimatorHandle = new TransformerEstimatorSafeHandle(estimator, DestroyEstimatorHelper))
                                {{
                                    if (!IsTrainingComplete(estimatorHandle))
                                    {{
                                        var fitResult = FitResult.Continue;
                                        while (fitResult != FitResult.Complete)
                                        {{
                                            fitResult = FitResult.Continue;
                                            using (var data = input.GetColumn<TSourceType>(Source).GetEnumerator())
                                            {{
                                                while (fitResult == FitResult.Continue && data.MoveNext())
                                                {{
                                                    {{
                                                        success = FitHelper(estimatorHandle, data.Current, out fitResult, out errorHandle);
                                                        if (!success)
                                                            throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));
                                                    }}
                                                }}

                                                success = CompleteTrainingHelper(estimatorHandle, out fitResult, out errorHandle);
                                                if (!success)
                                                    throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));
                                            }}
                                        }}
                                    }}
                                    success = CreateTransformerFromEstimatorHelper(estimatorHandle, out IntPtr transformer, out errorHandle);
                                    if (!success)
                                        throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));

                                    return new TransformerEstimatorSafeHandle(transformer, DestroyTransformerHelper);
                                }}
                            }}
                        }}

                        #endregion
                        {columnInfo}
                        #endregion

                        private sealed class Mapper : MapperBase
                        {{
                            #region Class members

                            private readonly {transformerName} _parent;
                            /* Codegen: add any extra class members here */

                            #endregion

                            public Mapper({transformerName} parent, DataViewSchema inputSchema) :
                                base(parent.Host.Register(nameof(Mapper)), inputSchema, parent)
                            {{
                                _parent = parent;
                            }}

                            protected override DataViewSchema.DetachedColumn[] GetOutputColumnsCore()
                            {{
                                return _parent._columns.Select(x => new DataViewSchema.DetachedColumn(x.Name, ColumnTypeExtensions.PrimitiveTypeFromType(x.ReturnType()))).ToArray();
                            }}

                            private Delegate MakeGetter<TSourceType, TOutputType>(DataViewRow input, int iinfo)
                            {{
                                ValueGetter<TOutputType> result = (ref TOutputType dst) =>
                                {{
                                    var inputColumn = input.Schema[_parent._columns[iinfo].Source];
                                    var srcGetterScalar = input.GetGetter<TSourceType>(inputColumn);

                                    TSourceType value = default;
                                    srcGetterScalar(ref value);

                                    dst = ((TypedColumn<TSourceType, TOutputType>)_parent._columns[iinfo]).Transform(value);

                                }};

                                return result;
                            }}

                            protected override Delegate MakeGetter(DataViewRow input, int iinfo, Func<int, bool> activeOutput, out Action disposer)
                            {{
                                disposer = null;
                                Type inputType = input.Schema[_parent._columns[iinfo].Source].Type.RawType;
                                Type outputType = _parent._columns[iinfo].ReturnType();

                                return Utils.MarshalInvoke(MakeGetter<int, int>, new Type[] {{ inputType, outputType }}, input, iinfo);
                            }}

                            private protected override Func<int, bool> GetDependenciesCore(Func<int, bool> activeOutput)
                            {{
                                var active = new bool[InputSchema.Count];
                                for (int i = 0; i < InputSchema.Count; i++)
                                {{
                                    if (_parent._columns.Any(x => x.Source == InputSchema[i].Name))
                                    {{
                                        active[i] = true;
                                    }}
                                }}

                                return col => active[col];
                            }}

                            private protected override void SaveModel(ModelSaveContext ctx) => _parent.SaveModel(ctx);
                        }}
                    }}

                    internal static class {entrypointName}
                    {{
                        [TlcModule.EntryPoint(Name = "Transforms.{baseName}",
                            Desc = {transformerName}.Summary,
                            UserName = {transformerName}.UserName,
                            ShortName = {transformerName}.ShortName)]
                        public static CommonOutputs.TransformOutput {baseName}(IHostEnvironment env, {estimatorName}.Options input)
                        {{
                            var h = EntryPointUtils.CheckArgsAndCreateHost(env, {transformerName}.ShortName, input);
                            var xf = new {estimatorName}(h, input).Fit(input.Data).Transform(input.Data);
                            return new CommonOutputs.TransformOutput()
                            {{
                                Model = new TransformModelImpl(h, xf, input.Data),
                                OutputData = xf
                            }};
                        }}
                    }}
                }}
                """,
            ).format(
                baseName=baseName,
                transformerName=transformerName,
                estimatorName=estimatorName,
                entrypointName=entrypointName,
                columnInfo=_GenerateTypedColumns(
                    items,
                    csharp_data_items,
                    items[0].name,
                    transformerName,
                    output_stream,
                ),
                optionalInput=_GenerateOptionalInputDeclaration(items),
                optionalInputOptions=_GenerateOptionalInputOptionsConstructor(items),
                optionalInputOptionClass=_GenerateOptionalInputOptionClassValues(items),
                supportedTypes=_GenerateSupportedTypes(csharp_data_items),
                typeFactory=_GenerateTypeFactory(csharp_data_items),
            ),
        )


def _GenerateTypeFactory(csharp_data_items):
    code = []
    valid_types = [t for t in csharp_data_items if t != None]
    for index, item in enumerate(valid_types):
        code.append(
            textwrap.dedent(
                """\
                {}if (type == typeof({}).ToString())
                \t\t\t\t{{
                    \t\t\t\treturn new {}TypedColumn(name, source, parent);
                \t\t\t\t}}
                """.format(
                    "\t\t\t\telse " if index != 0 else "",
                    item.InputTypeInfo.CSharpType,
                    item.InputTypeInfo.CSharpTypeName,
                ),
            ),
        )

    return "".join(code)


def _GenerateSupportedTypes(csharp_data_items):
    return ", ".join(
        "typeof({})".format(item.InputTypeInfo.CSharpType)
        for item in csharp_data_items
        if item != None
    )


def _GenerateOptionalInputDeclaration(items):
    if items[0] != None and items[0].input_type.endswith("?"):
        return ", bool treatDefaultAsNull = false"
    else:
        return ""


def _GenerateOptionalInputOptionsConstructor(items):
    if items[0] != None and items[0].input_type.endswith("?"):
        return "TreatDefaultAsNull = treatDefaultAsNull,"
    else:
        return ""


def _GenerateOptionalInputOptionClassValues(items):
    if items[0] != None and items[0].input_type.endswith("?"):
        return textwrap.dedent(
            """\
            [Argument(ArgumentType.AtMostOnce, HelpText = "If default value for the variable should be treated as null",
                \t\t\tName = "TreatDefaultAsNull", ShortName = "DefaultNull", SortOrder = 2)]
            \t\t\tpublic bool TreatDefaultAsNull = false;""",
        )
    else:
        return ""


def _GenerateTypedColumns(
    items,
    csharp_data_items,
    featurizerName,
    transformerName,
    output_stream,
):
    code = []
    unsupported_types = set()
    for index, item in enumerate(csharp_data_items):
        if item == None:
            if items[index].output_type not in unsupported_types:
                output_stream.write(
                    "Unsupported type '{}' found, not generating interop code for it.\n".format(
                        items[index].output_type,
                    ),
                )
                unsupported_types.add(items[index].output_type)
            continue
        code.append(
            """
            #region {typeName}TypedColumn

            internal sealed class {typeName}TypedColumn : TypedColumn<{inputType}, {outputType}>
            {{
                private TransformerEstimatorSafeHandle _transformerHandler;
                private {transformerName} _parent;
                internal {typeName}TypedColumn(string name, string source, {transformerName} parent) :
                    base(name, source, typeof({inputType}).ToString())
                {{
                    _parent = parent;
                }}

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_CreateEstimator", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static extern bool CreateEstimatorNative(/* Codegen: Add additional parameters here */ out IntPtr estimator, out IntPtr errorHandle);

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_DestroyEstimator", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static extern bool DestroyEstimatorNative(IntPtr estimator, out IntPtr errorHandle); // Should ONLY be called by safe handle

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_CreateTransformerFromEstimator", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static extern bool CreateTransformerFromEstimatorNative(TransformerEstimatorSafeHandle estimator, out IntPtr transformer, out IntPtr errorHandle);
                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_DestroyTransformer", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static extern bool DestroyTransformerNative(IntPtr transformer, out IntPtr errorHandle);
                internal override void CreateTransformerFromEstimator(IDataView input)
                {{
                    _transformerHandler = CreateTransformerFromEstimatorBase(input);
                }}

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_CreateTransformerFromSavedData", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static unsafe extern bool CreateTransformerFromSavedDataNative(byte* rawData, IntPtr bufferSize, out IntPtr transformer, out IntPtr errorHandle);
                private protected override unsafe void CreateTransformerFromSavedDataHelper(byte* rawData, IntPtr dataSize)
                {{
                    var result = CreateTransformerFromSavedDataNative(rawData, dataSize, out IntPtr transformer, out IntPtr errorHandle);
                    if (!result)
                        throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));

                    _transformerHandler = new TransformerEstimatorSafeHandle(transformer, DestroyTransformerNative);
                }}

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_Transform", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static unsafe extern bool TransformDataNative(TransformerEstimatorSafeHandle transformer, {nativeInputDeclaration}, {nativeOutputDeclaration}, out IntPtr errorHandle);
                {deleteTransformedData}
                internal unsafe override {outputType} Transform({inputType} input)
                {{
                    {inputConversion}
                    var success = TransformDataNative(_transformerHandler, interopInput, {nativeOutputDeclaration}, out IntPtr errorHandle);
                    if (!success)
                        throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));

                    {outputConversion}
                    return output;
                    {conversionEnd}
                }}

                public override void Dispose()
                {{
                    if (!_transformerHandler.IsClosed)
                        _transformerHandler.Dispose();
                }}

                private protected override bool CreateEstimatorHelper(out IntPtr estimator, out IntPtr errorHandle)
                {{
                    /* Codegen: do any extra checks/paramters here */
                    return CreateEstimatorNative(out estimator, out errorHandle);
                }}

                private protected override bool CreateTransformerFromEstimatorHelper(TransformerEstimatorSafeHandle estimator, out IntPtr transformer, out IntPtr errorHandle) =>
                    CreateTransformerFromEstimatorNative(estimator, out transformer, out errorHandle);

                private protected override bool DestroyEstimatorHelper(IntPtr estimator, out IntPtr errorHandle) =>
                    DestroyEstimatorNative(estimator, out errorHandle);

                private protected override bool DestroyTransformerHelper(IntPtr transformer, out IntPtr errorHandle) =>
                    DestroyTransformerNative(transformer, out errorHandle);

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_Fit", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static unsafe extern bool FitNative(TransformerEstimatorSafeHandle estimator, {nativeInputDeclaration}, out FitResult fitResult, out IntPtr errorHandle);
                private protected unsafe override bool FitHelper(TransformerEstimatorSafeHandle estimator, {inputType} input, out FitResult fitResult, out IntPtr errorHandle)
                {{
                    {inputConversion}
                    return FitNative(estimator, interopInput, out fitResult, out errorHandle);
                    {conversionEnd}
                }}

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_CompleteTraining", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static extern bool CompleteTrainingNative(TransformerEstimatorSafeHandle estimator, out FitResult fitResult, out IntPtr errorHandle);
                private protected override bool CompleteTrainingHelper(TransformerEstimatorSafeHandle estimator, out FitResult fitResult, out IntPtr errorHandle) =>
                        CompleteTrainingNative(estimator, out fitResult, out errorHandle);

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_CreateTransformerSaveData", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static extern bool CreateTransformerSaveDataNative(TransformerEstimatorSafeHandle transformer, out IntPtr buffer, out IntPtr bufferSize, out IntPtr error);
                private protected override bool CreateTransformerSaveDataHelper(out IntPtr buffer, out IntPtr bufferSize, out IntPtr errorHandle) =>
                    CreateTransformerSaveDataNative(_transformerHandler, out buffer, out bufferSize, out errorHandle);

                [DllImport("Featurizers", EntryPoint = "{featurizerName}_{nativeFeaturizerType}_IsTrainingComplete", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
                private static extern bool IsTrainingCompleteNative(TransformerEstimatorSafeHandle transformer, out bool isTrainingComplete, out IntPtr errorHandle);
                private protected override bool IsTrainingComplete(TransformerEstimatorSafeHandle estimatorHandle)
                {{
                    var success = IsTrainingCompleteNative(estimatorHandle, out bool isTrainingComplete, out IntPtr errorHandle);
                    if (!success)
                        throw new Exception(GetErrorDetailsAndFreeNativeMemory(errorHandle));

                    return isTrainingComplete;
                }}

                public override Type ReturnType()
                {{
                    return typeof({outputType});
                }}
            }}

            #endregion
            """.format(
                typeName=item.InputTypeInfo.CSharpTypeName,
                inputType=item.InputTypeInfo.CSharpType,
                outputType=item.OutputTypeInfo.CSharpType,
                featurizerName=featurizerName,
                nativeFeaturizerType=item.InputTypeInfo.TypeName,
                nativeInputDeclaration=item.InputTypeInfo.GetNativeInputInfo().ParameterDecl,
                nativeOutputDeclaration=item.OutputTypeInfo.GetNativeOutputInfo().ParameterDecl,
                inputConversion=item.InputTypeInfo.GetNativeInputInfo().InvocationStatement,
                outputConversion=item.OutputTypeInfo.GetNativeOutputInfo().InvocationStatement,
                transformerName=transformerName,
                conversionEnd=item.InputTypeInfo.GetNativeInputInfo().ConversionEnd,
                deleteTransformedData=item.OutputTypeInfo.GetNativeOutputInfo(
                    featurizer_name=featurizerName,
                ).DeleteTransformedData,
            ),
        )

    return "".join(code)


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
class CSharpData(object):
    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(self, item, global_custom_structs, global_custom_enums):
        # Create the custom enums
        custom_enums = OrderedDict()

        for custom_enum in itertools.chain(global_custom_enums, getattr(item, "custom_enums", [])):
            if isinstance(custom_enum.underlying_type, six.string_types):
                type_info = self._CreateTypeInfo(custom_enum.underlying_type)
                assert type_info, custom_enum.underlying_type

                custom_enum.underlying_type_info = type_info

            custom_enums[custom_enum.name] = custom_enum

        # Create the custom structs
        custom_structs = OrderedDict()

        for custom_struct in itertools.chain(global_custom_structs, getattr(item, "custom_structs", [])):
            members = OrderedDict()

            for member in custom_struct.members:
                type_info = self._CreateTypeInfo(member.type)
                assert type_info, member.type

                assert member.name not in members, member.name
                members[member.name] = type_info

            custom_structs[custom_struct.name] = members

        # Create the configuration param type infos
        configuration_param_type_infos = []

        for configuration_param in getattr(item, "configuration_params", []):
            if configuration_param.type in custom_enums:
                type_info = custom_enums[configuration_param.type].underlying_type_info
                configuration_param.is_enum = True

            else:
                type_info = self._CreateTypeInfo(
                    configuration_param.type,
                    custom_structs=custom_structs,
                    custom_enums=custom_enums,
                )
                assert type_info, configuration_param.type

            configuration_param_type_infos.append(type_info)

        input_type_info = self._CreateTypeInfo(
            item.input_type,
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )
        assert input_type_info, item.input_type

        output_type_info = self._CreateTypeInfo(
            item.output_type,
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )
        if output_type_info is None:
            raise Exception("'{}' is not a supported type".format(item.output_type))

        # Commit the results
        self.CustomStructs                              = custom_structs
        self.CustomEnums                                = custom_enums
        self.ConfigurationParamTypeInfos                = configuration_param_type_infos
        self.InputTypeInfo                              = input_type_info
        self.OutputTypeInfo                             = output_type_info

    # ----------------------------------------------------------------------
    # |
    # |  Private Data
    # |
    # ----------------------------------------------------------------------
    _type_info_classes                      = None

    # ----------------------------------------------------------------------
    # |
    # |  Private Methods
    # |
    # ----------------------------------------------------------------------
    @classmethod
    def _CreateTypeInfo(cls, the_type, *args, **kwargs):
        if cls._type_info_classes is None:
            from Plugins.MLNetPluginImpl.DatetimeTypeInfo import DatetimeTypeInfo
            from Plugins.MLNetPluginImpl.MatrixTypeInfo import MatrixTypeInfo
            from Plugins.MLNetPluginImpl import ScalarTypeInfos
            from Plugins.MLNetPluginImpl.SingleValueSparseVectorTypeInfo import SingleValueSparseVectorTypeInfo
            from Plugins.MLNetPluginImpl.SparseVectorTypeInfo import SparseVectorTypeInfo
            from Plugins.MLNetPluginImpl.StringTypeInfo import StringTypeInfo
            from Plugins.MLNetPluginImpl import StructTypeInfos
            from Plugins.MLNetPluginImpl.TupleTypeInfo import TupleTypeInfo
            from Plugins.MLNetPluginImpl.UniqueIdTypeInfo import UniqueIdTypeInfo
            from Plugins.MLNetPluginImpl.VectorTypeInfo import VectorTypeInfo

            type_info_classes = [
                DatetimeTypeInfo,
                MatrixTypeInfo,
                SingleValueSparseVectorTypeInfo,
                SparseVectorTypeInfo,
                StringTypeInfo,
                TupleTypeInfo,
                UniqueIdTypeInfo,
                VectorTypeInfo,
            ]

            for compound_module in [ScalarTypeInfos, StructTypeInfos]:
                for obj_name in dir(compound_module):
                    if (
                        obj_name.startswith("_")
                        or not obj_name.endswith("TypeInfo")
                        or obj_name == "TypeInfo"
                    ):
                        continue

                    type_info_classes.append(getattr(compound_module, obj_name))

            # Associate the type infos with the class rather than the instance
            # so that we only need to perform this initialization once.
            cls._type_info_classes = type_info_classes

        is_optional = False

        if the_type.endswith("?"):
            the_type = the_type[:-1]
            is_optional = True

        type_info_class = None

        for this_type_info_class in cls._type_info_classes:
            if isinstance(this_type_info_class.TypeName, six.string_types):
                if this_type_info_class.TypeName == the_type:
                    type_info_class = this_type_info_class
                    break

            elif hasattr(this_type_info_class.TypeName, "match"):
                if this_type_info_class.TypeName.match(the_type):
                    type_info_class = this_type_info_class
                    break

        if type_info_class is None:
            return None

        return type_info_class(
            *args,
            member_type=the_type,
            is_optional=is_optional,
            create_type_info_func=cls._CreateTypeInfo,
            **kwargs
        )
