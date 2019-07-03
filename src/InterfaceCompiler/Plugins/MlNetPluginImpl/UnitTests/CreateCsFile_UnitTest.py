# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for CreateCsFile.py"""

import os
import sys
import textwrap
import unittest
import unittest.mock

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, "..", ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from MlNetPluginImpl import CreateCsFile

# ----------------------------------------------------------------------
class StandardSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def test_FullTwoParametersFile(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCsFile.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function = self._CreateFunctionTwoInputParameters()

            result = CreateCsFile.CreateCsFile(function, "ignored", "Add", lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                textwrap.dedent(sink),
                textwrap.dedent(
                    """\
                    // The file header!
                    using Microsoft.ML;
                    using Microsoft.ML.Data;
                    using Microsoft.ML.Runtime;
                    using System;
                    using System.Linq;
                    using System.Runtime.InteropServices;
                    
                    
                    namespace Microsoft.ML.Autogen
                    {
                        
                        public static class AddExtensionClass
                        {
                            
                            public class TransformParameter<T>
                            {
                                private readonly T _rawValue;
                                public readonly DataViewSchema.Column? Column;
                                
                                public T GetValue(DataViewRow row)
                                {
                                    if (Column.HasValue)
                                    {
                                        var column = row.Schema[Column.Value.Name];
                                        var getter = row.GetGetter<T>(column);
                                        T value = default;
                                        getter(ref value);
                                        return value;
                                    }
                                    else
                                    {
                                        return _rawValue;
                                    }
                                }
                                
                                public TransformParameter(T value)
                                {
                                    _rawValue = value;
                                    Column = null;
                                }
                                
                                public TransformParameter(DataViewSchema.Column column)
                                {
                                    _rawValue = default;
                                    Column = column;
                                }
                                
                            }
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, int a, int b, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, int a, DataViewSchema.Column b, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, DataViewSchema.Column a, int b, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, DataViewSchema.Column a, DataViewSchema.Column b, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, outputColumn);
                        }
                        
                        public class AddEstimator : IEstimator<AddTransformer>
                        {
                            private AddExtensionClass.TransformParameter<int>  _a = default;
                            private AddExtensionClass.TransformParameter<int>  _b = default;
                            private string _outputColumn = default;
                            
                            private readonly IHost _host;
                            private static Type GetParameterType(object obj)
                            {
                                if (obj.GetType() == typeof(DataViewSchema.Column))
                                {
                                    return ((DataViewSchema.Column)obj).Type.RawType;
                                }
                                else
                                {
                                    return obj.GetType();
                                }
                            }
                            
                            private static Type GetParameterClassType(object obj)
                            {
                                var type = GetParameterType(obj);
                                return typeof(AddExtensionClass.TransformParameter<>).MakeGenericType(type);
                            }
                            
                            public static AddEstimator Create(IHostEnvironment env, object a, object b, string outputColumn)
                            {
                                
                                var aParam = new object[] { a };
                                var aType = GetParameterClassType(a);
                                var aInstance = Activator.CreateInstance(aType, aParam);
                                
                                var bParam = new object[] { b };
                                var bType = GetParameterClassType(b);
                                var bInstance = Activator.CreateInstance(bType, bParam);
                                
                                var param = new object[] { env, aInstance, bInstance, outputColumn };
                                var estimator = Activator.CreateInstance(typeof(AddEstimator), param);
                                
                                return (AddEstimator)estimator;
                            }
                            
                            public AddEstimator(IHostEnvironment env, AddExtensionClass.TransformParameter<int> a, AddExtensionClass.TransformParameter<int> b, string outputColumn)
                            {
                                _a = a;
                                _b = b;
                                _outputColumn = outputColumn;
                                _host = env.Register(nameof(AddEstimator));
                            }
                            
                            public AddTransformer Fit(IDataView input)
                            {
                                return new AddTransformer(_host, _a, _b, _outputColumn);
                            }
                            
                            public SchemaShape GetOutputSchema(SchemaShape inputSchema)
                            {
                                var columns = inputSchema.ToDictionary(x => x.Name);
                                SchemaShape.Column col;
                                
                                col = new SchemaShape.Column(_outputColumn, SchemaShape.Column.VectorKind.Scalar,
                                ColumnTypeExtensions.PrimitiveTypeFromType(typeof(int)), false, null);
                                
                                columns[_outputColumn] = col;
                                return new SchemaShape(columns.Values);
                            }
                            
                        }
                        
                        public class AddTransformer : RowToRowTransformerBase
                        {
                            private AddExtensionClass.TransformParameter<int> _a = default;
                            private AddExtensionClass.TransformParameter<int> _b = default;
                            private string _outputColumn = default;
                            
                            public AddTransformer(IHost host, AddExtensionClass.TransformParameter<int> a, AddExtensionClass.TransformParameter<int> b, string outputColumn) :
                                base(host.Register(nameof(AddTransformer)))
                            {
                                _a = a;
                                _b = b;
                                _outputColumn = outputColumn;
                            }
                            
                            protected class Mapper : MapperBase
                            {
                                private readonly AddTransformer _parent;
                                
                                [DllImport("Add.dll", EntryPoint = "AddProxy")]
                                extern static int Add(int a, int b);
                                
                                public Mapper(AddTransformer parent, DataViewSchema inputSchema) :
                                    base(parent.Host.Register(nameof(Mapper)), inputSchema, parent)
                                {
                                    _parent = parent;
                                }
                                
                                protected override DataViewSchema.DetachedColumn[] GetOutputColumnsCore()
                                {
                                    var output = new DataViewSchema.DetachedColumn(_parent._outputColumn,
                                    ColumnTypeExtensions.PrimitiveTypeFromType(typeof(int)));
                                    return new DataViewSchema.DetachedColumn[] { output };
                                }
                                
                                private Delegate MakeGetter(DataViewRow input, int iinfo)
                                {
                                    ValueGetter<int> result = (ref int dst) =>
                                    {
                                        var aVal =  _parent._a.GetValue(input);
                                        var bVal =  _parent._b.GetValue(input);
                                        dst = Add(aVal, bVal);
                                    };
                                    
                                    return result;
                                }
                                
                                protected override Delegate MakeGetter(DataViewRow input, int iinfo, Func<int, bool> activeOutput, out Action disposer)
                                {
                                    disposer = null;
                                    return MakeGetter(input, iinfo);
                                }
                                
                                protected override Func<int, bool> GetDependenciesCore(Func<int, bool> activeOutput)
                                {
                                    var active = new bool[InputSchema.Count];
                                    for (int i = 0; i < InputSchema.Count; i++)
                                    {
                                        if (_parent._a.Column.HasValue && InputSchema[i].Name.Equals(_parent._a.Column.Value.Name))
                                        {
                                            active[i] = true;
                                        }
                                        if (_parent._b.Column.HasValue && InputSchema[i].Name.Equals(_parent._b.Column.Value.Name))
                                        {
                                            active[i] = true;
                                        }
                                    }
                                    
                                    return col => active[col];
                                }
                                
                                protected override void SaveModel(ModelSaveContext ctx)
                                {
                                    throw new NotImplementedException();
                                }
                            }
                            
                            protected override IRowMapper MakeRowMapper(DataViewSchema schema) => new Mapper(this, schema);
                            
                            protected override void SaveModel(ModelSaveContext ctx)
                            {
                                throw new NotImplementedException();
                            }
                        }
                    }
                    """,
                ),
            )

    def test_FullOneParametersFile(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCsFile.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function = self._CreateFunctionOneInputParameter()

            result = CreateCsFile.CreateCsFile(function, "ignored", "Add", lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                textwrap.dedent(sink),
                textwrap.dedent(
                    """\
                    // The file header!
                    using Microsoft.ML;
                    using Microsoft.ML.Data;
                    using Microsoft.ML.Runtime;
                    using System;
                    using System.Linq;
                    using System.Runtime.InteropServices;


                    namespace Microsoft.ML.Autogen
                    {
                        
                        public static class AddExtensionClass
                        {
                            
                            public class TransformParameter<T>
                            {
                                private readonly T _rawValue;
                                public readonly DataViewSchema.Column? Column;
                                
                                public T GetValue(DataViewRow row)
                                {
                                    if (Column.HasValue)
                                    {
                                        var column = row.Schema[Column.Value.Name];
                                        var getter = row.GetGetter<T>(column);
                                        T value = default;
                                        getter(ref value);
                                        return value;
                                    }
                                    else
                                    {
                                        return _rawValue;
                                    }
                                }
                                
                                public TransformParameter(T value)
                                {
                                    _rawValue = value;
                                    Column = null;
                                }
                                
                                public TransformParameter(DataViewSchema.Column column)
                                {
                                    _rawValue = default;
                                    Column = column;
                                }
                                
                            }
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, int a, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, DataViewSchema.Column a, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, outputColumn);
                        }
                        
                        public class AddEstimator : IEstimator<AddTransformer>
                        {
                            private AddExtensionClass.TransformParameter<int>  _a = default;
                            private string _outputColumn = default;
                            
                            private readonly IHost _host;
                            private static Type GetParameterType(object obj)
                            {
                                if (obj.GetType() == typeof(DataViewSchema.Column))
                                {
                                    return ((DataViewSchema.Column)obj).Type.RawType;
                                }
                                else
                                {
                                    return obj.GetType();
                                }
                            }
                            
                            private static Type GetParameterClassType(object obj)
                            {
                                var type = GetParameterType(obj);
                                return typeof(AddExtensionClass.TransformParameter<>).MakeGenericType(type);
                            }
                            
                            public static AddEstimator Create(IHostEnvironment env, object a, string outputColumn)
                            {
                                
                                var aParam = new object[] { a };
                                var aType = GetParameterClassType(a);
                                var aInstance = Activator.CreateInstance(aType, aParam);
                                
                                var param = new object[] { env, aInstance, outputColumn };
                                var estimator = Activator.CreateInstance(typeof(AddEstimator), param);
                                
                                return (AddEstimator)estimator;
                            }
                            
                            public AddEstimator(IHostEnvironment env, AddExtensionClass.TransformParameter<int> a, string outputColumn)
                            {
                                _a = a;
                                _outputColumn = outputColumn;
                                _host = env.Register(nameof(AddEstimator));
                            }
                            
                            public AddTransformer Fit(IDataView input)
                            {
                                return new AddTransformer(_host, _a, _outputColumn);
                            }
                            
                            public SchemaShape GetOutputSchema(SchemaShape inputSchema)
                            {
                                var columns = inputSchema.ToDictionary(x => x.Name);
                                SchemaShape.Column col;
                                
                                col = new SchemaShape.Column(_outputColumn, SchemaShape.Column.VectorKind.Scalar,
                                ColumnTypeExtensions.PrimitiveTypeFromType(typeof(int)), false, null);
                                
                                columns[_outputColumn] = col;
                                return new SchemaShape(columns.Values);
                            }
                            
                        }
                        
                        public class AddTransformer : RowToRowTransformerBase
                        {
                            private AddExtensionClass.TransformParameter<int> _a = default;
                            private string _outputColumn = default;
                            
                            public AddTransformer(IHost host, AddExtensionClass.TransformParameter<int> a, string outputColumn) :
                                base(host.Register(nameof(AddTransformer)))
                            {
                                _a = a;
                                _outputColumn = outputColumn;
                            }
                            
                            protected class Mapper : MapperBase
                            {
                                private readonly AddTransformer _parent;
                                
                                [DllImport("Add.dll", EntryPoint = "AddProxy")]
                                extern static int Add(int a);
                                
                                public Mapper(AddTransformer parent, DataViewSchema inputSchema) :
                                    base(parent.Host.Register(nameof(Mapper)), inputSchema, parent)
                                {
                                    _parent = parent;
                                }
                                
                                protected override DataViewSchema.DetachedColumn[] GetOutputColumnsCore()
                                {
                                    var output = new DataViewSchema.DetachedColumn(_parent._outputColumn,
                                    ColumnTypeExtensions.PrimitiveTypeFromType(typeof(int)));
                                    return new DataViewSchema.DetachedColumn[] { output };
                                }
                                
                                private Delegate MakeGetter(DataViewRow input, int iinfo)
                                {
                                    ValueGetter<int> result = (ref int dst) =>
                                    {
                                        var aVal =  _parent._a.GetValue(input);
                                        dst = Add(aVal);
                                    };
                                    
                                    return result;
                                }
                                
                                protected override Delegate MakeGetter(DataViewRow input, int iinfo, Func<int, bool> activeOutput, out Action disposer)
                                {
                                    disposer = null;
                                    return MakeGetter(input, iinfo);
                                }
                                
                                protected override Func<int, bool> GetDependenciesCore(Func<int, bool> activeOutput)
                                {
                                    var active = new bool[InputSchema.Count];
                                    for (int i = 0; i < InputSchema.Count; i++)
                                    {
                                        if (_parent._a.Column.HasValue && InputSchema[i].Name.Equals(_parent._a.Column.Value.Name))
                                        {
                                            active[i] = true;
                                        }
                                    }
                                    
                                    return col => active[col];
                                }
                                
                                protected override void SaveModel(ModelSaveContext ctx)
                                {
                                    throw new NotImplementedException();
                                }
                            }
                            
                            protected override IRowMapper MakeRowMapper(DataViewSchema schema) => new Mapper(this, schema);
                            
                            protected override void SaveModel(ModelSaveContext ctx)
                            {
                                throw new NotImplementedException();
                            }
                        }
                    }
                    """,
                ),
            )

    def test_FullNoParametersFile(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCsFile.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function = self._CreateFunctionNoInputParameters()

            result = CreateCsFile.CreateCsFile(function, "ignored", "Add", lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                textwrap.dedent(sink),
                textwrap.dedent(
                    """\
                    // The file header!
                    using Microsoft.ML;
                    using Microsoft.ML.Data;
                    using Microsoft.ML.Runtime;
                    using System;
                    using System.Linq;
                    using System.Runtime.InteropServices;


                    namespace Microsoft.ML.Autogen
                    {
                        
                        public static class AddExtensionClass
                        {
                            
                            public class TransformParameter<T>
                            {
                                private readonly T _rawValue;
                                public readonly DataViewSchema.Column? Column;
                                
                                public T GetValue(DataViewRow row)
                                {
                                    if (Column.HasValue)
                                    {
                                        var column = row.Schema[Column.Value.Name];
                                        var getter = row.GetGetter<T>(column);
                                        T value = default;
                                        getter(ref value);
                                        return value;
                                    }
                                    else
                                    {
                                        return _rawValue;
                                    }
                                }
                                
                                public TransformParameter(T value)
                                {
                                    _rawValue = value;
                                    Column = null;
                                }
                                
                                public TransformParameter(DataViewSchema.Column column)
                                {
                                    _rawValue = default;
                                    Column = column;
                                }
                                
                            }
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), outputColumn);
                        }
                        
                        public class AddEstimator : IEstimator<AddTransformer>
                        {
                            private string _outputColumn = default;
                            
                            private readonly IHost _host;
                            private static Type GetParameterType(object obj)
                            {
                                if (obj.GetType() == typeof(DataViewSchema.Column))
                                {
                                    return ((DataViewSchema.Column)obj).Type.RawType;
                                }
                                else
                                {
                                    return obj.GetType();
                                }
                            }
                            
                            private static Type GetParameterClassType(object obj)
                            {
                                var type = GetParameterType(obj);
                                return typeof(AddExtensionClass.TransformParameter<>).MakeGenericType(type);
                            }
                            
                            public static AddEstimator Create(IHostEnvironment env, string outputColumn)
                            {
                                
                                var param = new object[] { env, outputColumn };
                                var estimator = Activator.CreateInstance(typeof(AddEstimator), param);
                                
                                return (AddEstimator)estimator;
                            }
                            
                            public AddEstimator(IHostEnvironment env, string outputColumn)
                            {
                                _outputColumn = outputColumn;
                                _host = env.Register(nameof(AddEstimator));
                            }
                            
                            public AddTransformer Fit(IDataView input)
                            {
                                return new AddTransformer(_host, _outputColumn);
                            }
                            
                            public SchemaShape GetOutputSchema(SchemaShape inputSchema)
                            {
                                var columns = inputSchema.ToDictionary(x => x.Name);
                                SchemaShape.Column col;
                                
                                col = new SchemaShape.Column(_outputColumn, SchemaShape.Column.VectorKind.Scalar,
                                ColumnTypeExtensions.PrimitiveTypeFromType(typeof(int)), false, null);
                                
                                columns[_outputColumn] = col;
                                return new SchemaShape(columns.Values);
                            }
                            
                        }
                        
                        public class AddTransformer : RowToRowTransformerBase
                        {
                            private string _outputColumn = default;
                            
                            public AddTransformer(IHost host, string outputColumn) :
                                base(host.Register(nameof(AddTransformer)))
                            {
                                _outputColumn = outputColumn;
                            }
                            
                            protected class Mapper : MapperBase
                            {
                                private readonly AddTransformer _parent;
                                
                                [DllImport("Add.dll", EntryPoint = "AddProxy")]
                                extern static int Add();
                                
                                public Mapper(AddTransformer parent, DataViewSchema inputSchema) :
                                    base(parent.Host.Register(nameof(Mapper)), inputSchema, parent)
                                {
                                    _parent = parent;
                                }
                                
                                protected override DataViewSchema.DetachedColumn[] GetOutputColumnsCore()
                                {
                                    var output = new DataViewSchema.DetachedColumn(_parent._outputColumn,
                                    ColumnTypeExtensions.PrimitiveTypeFromType(typeof(int)));
                                    return new DataViewSchema.DetachedColumn[] { output };
                                }
                                
                                private Delegate MakeGetter(DataViewRow input, int iinfo)
                                {
                                    ValueGetter<int> result = (ref int dst) =>
                                    {
                                        dst = Add();
                                    };
                                    
                                    return result;
                                }
                                
                                protected override Delegate MakeGetter(DataViewRow input, int iinfo, Func<int, bool> activeOutput, out Action disposer)
                                {
                                    disposer = null;
                                    return MakeGetter(input, iinfo);
                                }
                                
                                protected override Func<int, bool> GetDependenciesCore(Func<int, bool> activeOutput)
                                {
                                    var active = new bool[InputSchema.Count];
                                    for (int i = 0; i < InputSchema.Count; i++)
                                    {
                                    }
                                    
                                    return col => active[col];
                                }
                                
                                protected override void SaveModel(ModelSaveContext ctx)
                                {
                                    throw new NotImplementedException();
                                }
                            }
                            
                            protected override IRowMapper MakeRowMapper(DataViewSchema schema) => new Mapper(this, schema);
                            
                            protected override void SaveModel(ModelSaveContext ctx)
                            {
                                throw new NotImplementedException();
                            }
                        }
                    }
                    """,
                ),
            )
    
    def test_FullDifferentTypesParametersFile(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCsFile.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function = self._CreateFunctionDifferentTypesInputParameters()

            result = CreateCsFile.CreateCsFile(function, "ignored", "Add", lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                textwrap.dedent(sink),
                textwrap.dedent(
                    """\
                    // The file header!
                    using Microsoft.ML;
                    using Microsoft.ML.Data;
                    using Microsoft.ML.Runtime;
                    using System;
                    using System.Linq;
                    using System.Runtime.InteropServices;


                    namespace Microsoft.ML.Autogen
                    {
                        
                        public static class AddExtensionClass
                        {
                            
                            public class TransformParameter<T>
                            {
                                private readonly T _rawValue;
                                public readonly DataViewSchema.Column? Column;
                                
                                public T GetValue(DataViewRow row)
                                {
                                    if (Column.HasValue)
                                    {
                                        var column = row.Schema[Column.Value.Name];
                                        var getter = row.GetGetter<T>(column);
                                        T value = default;
                                        getter(ref value);
                                        return value;
                                    }
                                    else
                                    {
                                        return _rawValue;
                                    }
                                }
                                
                                public TransformParameter(T value)
                                {
                                    _rawValue = value;
                                    Column = null;
                                }
                                
                                public TransformParameter(DataViewSchema.Column column)
                                {
                                    _rawValue = default;
                                    Column = column;
                                }
                                
                            }
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, uint a, double b, char c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, uint a, double b, DataViewSchema.Column c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, uint a, DataViewSchema.Column b, char c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, uint a, DataViewSchema.Column b, DataViewSchema.Column c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, DataViewSchema.Column a, double b, char c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, DataViewSchema.Column a, double b, DataViewSchema.Column c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, DataViewSchema.Column a, DataViewSchema.Column b, char c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                            
                            public static AddEstimator Add(this TransformsCatalog catalog, DataViewSchema.Column a, DataViewSchema.Column b, DataViewSchema.Column c, string outputColumn)
                                => AddEstimator.Create(CatalogUtils.GetEnvironment(catalog), a, b, c, outputColumn);
                        }
                        
                        public class AddEstimator : IEstimator<AddTransformer>
                        {
                            private AddExtensionClass.TransformParameter<uint>  _a = default;
                            private AddExtensionClass.TransformParameter<double>  _b = default;
                            private AddExtensionClass.TransformParameter<char>  _c = default;
                            private string _outputColumn = default;
                            
                            private readonly IHost _host;
                            private static Type GetParameterType(object obj)
                            {
                                if (obj.GetType() == typeof(DataViewSchema.Column))
                                {
                                    return ((DataViewSchema.Column)obj).Type.RawType;
                                }
                                else
                                {
                                    return obj.GetType();
                                }
                            }
                            
                            private static Type GetParameterClassType(object obj)
                            {
                                var type = GetParameterType(obj);
                                return typeof(AddExtensionClass.TransformParameter<>).MakeGenericType(type);
                            }
                            
                            public static AddEstimator Create(IHostEnvironment env, object a, object b, object c, string outputColumn)
                            {
                                
                                var aParam = new object[] { a };
                                var aType = GetParameterClassType(a);
                                var aInstance = Activator.CreateInstance(aType, aParam);
                                
                                var bParam = new object[] { b };
                                var bType = GetParameterClassType(b);
                                var bInstance = Activator.CreateInstance(bType, bParam);
                                
                                var cParam = new object[] { c };
                                var cType = GetParameterClassType(c);
                                var cInstance = Activator.CreateInstance(cType, cParam);
                                
                                var param = new object[] { env, aInstance, bInstance, cInstance, outputColumn };
                                var estimator = Activator.CreateInstance(typeof(AddEstimator), param);
                                
                                return (AddEstimator)estimator;
                            }
                            
                            public AddEstimator(IHostEnvironment env, AddExtensionClass.TransformParameter<uint> a, AddExtensionClass.TransformParameter<double> b, AddExtensionClass.TransformParameter<char> c, string outputColumn)
                            {
                                _a = a;
                                _b = b;
                                _c = c;
                                _outputColumn = outputColumn;
                                _host = env.Register(nameof(AddEstimator));
                            }
                            
                            public AddTransformer Fit(IDataView input)
                            {
                                return new AddTransformer(_host, _a, _b, _c, _outputColumn);
                            }
                            
                            public SchemaShape GetOutputSchema(SchemaShape inputSchema)
                            {
                                var columns = inputSchema.ToDictionary(x => x.Name);
                                SchemaShape.Column col;
                                
                                col = new SchemaShape.Column(_outputColumn, SchemaShape.Column.VectorKind.Scalar,
                                ColumnTypeExtensions.PrimitiveTypeFromType(typeof(long)), false, null);
                                
                                columns[_outputColumn] = col;
                                return new SchemaShape(columns.Values);
                            }
                            
                        }
                        
                        public class AddTransformer : RowToRowTransformerBase
                        {
                            private AddExtensionClass.TransformParameter<uint> _a = default;
                            private AddExtensionClass.TransformParameter<double> _b = default;
                            private AddExtensionClass.TransformParameter<char> _c = default;
                            private string _outputColumn = default;
                            
                            public AddTransformer(IHost host, AddExtensionClass.TransformParameter<uint> a, AddExtensionClass.TransformParameter<double> b, AddExtensionClass.TransformParameter<char> c, string outputColumn) :
                                base(host.Register(nameof(AddTransformer)))
                            {
                                _a = a;
                                _b = b;
                                _c = c;
                                _outputColumn = outputColumn;
                            }
                            
                            protected class Mapper : MapperBase
                            {
                                private readonly AddTransformer _parent;
                                
                                [DllImport("Add.dll", EntryPoint = "AddProxy")]
                                extern static long Add(uint a, double b, char c);
                                
                                public Mapper(AddTransformer parent, DataViewSchema inputSchema) :
                                    base(parent.Host.Register(nameof(Mapper)), inputSchema, parent)
                                {
                                    _parent = parent;
                                }
                                
                                protected override DataViewSchema.DetachedColumn[] GetOutputColumnsCore()
                                {
                                    var output = new DataViewSchema.DetachedColumn(_parent._outputColumn,
                                    ColumnTypeExtensions.PrimitiveTypeFromType(typeof(long)));
                                    return new DataViewSchema.DetachedColumn[] { output };
                                }
                                
                                private Delegate MakeGetter(DataViewRow input, int iinfo)
                                {
                                    ValueGetter<long> result = (ref long dst) =>
                                    {
                                        var aVal =  _parent._a.GetValue(input);
                                        var bVal =  _parent._b.GetValue(input);
                                        var cVal =  _parent._c.GetValue(input);
                                        dst = Add(aVal, bVal, cVal);
                                    };
                                    
                                    return result;
                                }
                                
                                protected override Delegate MakeGetter(DataViewRow input, int iinfo, Func<int, bool> activeOutput, out Action disposer)
                                {
                                    disposer = null;
                                    return MakeGetter(input, iinfo);
                                }
                                
                                protected override Func<int, bool> GetDependenciesCore(Func<int, bool> activeOutput)
                                {
                                    var active = new bool[InputSchema.Count];
                                    for (int i = 0; i < InputSchema.Count; i++)
                                    {
                                        if (_parent._a.Column.HasValue && InputSchema[i].Name.Equals(_parent._a.Column.Value.Name))
                                        {
                                            active[i] = true;
                                        }
                                        if (_parent._b.Column.HasValue && InputSchema[i].Name.Equals(_parent._b.Column.Value.Name))
                                        {
                                            active[i] = true;
                                        }
                                        if (_parent._c.Column.HasValue && InputSchema[i].Name.Equals(_parent._c.Column.Value.Name))
                                        {
                                            active[i] = true;
                                        }
                                    }
                                    
                                    return col => active[col];
                                }
                                
                                protected override void SaveModel(ModelSaveContext ctx)
                                {
                                    throw new NotImplementedException();
                                }
                            }
                            
                            protected override IRowMapper MakeRowMapper(DataViewSchema schema) => new Mapper(this, schema);
                            
                            protected override void SaveModel(ModelSaveContext ctx)
                            {
                                throw new NotImplementedException();
                            }
                        }
                    }
                    """,
                ),
            )

    """
    TESTING HELPER METHODS
    """
    def _BuildAllParamterPermutationsWrapper(self, variable_names):
        variables_tuples = []
        for va in variable_names:
            variables_tuples.append(("val-{0}".format(va), "col-{0}".format(va)))

        all_combos = list(CreateCsFile._BuildAllPossibleFunctionParameterPermutations(variables_tuples, 0, []))
        return all_combos

    def _CreateFunctionOneInputParameter(self):
        function = self.CreateFunction("Add", 
            ["a"],
            "int",
            ["int"],
            ["int"],
            "int"
        )

        return function

    def _CreateFunctionNoInputParameters(self):
        function = self.CreateFunction("Add", 
            [],
            "int",
            [],
            [],
            "int"
        )

        return function

    def _CreateFunctionTwoInputParameters(self):
        function = self.CreateFunction("Add", 
            ["a", "b"],
            "int",
            ["int", "int"],
            ["int", "int"],
            "int"
        )

        return function

    def _CreateFunctionDifferentTypesInputParameters(self):
        function = self.CreateFunction("Add", 
            ["a", "b", "c"],
            "std::int64_t",
            ["std::uint32_t", "double", "char"],
            ["std::uint32_t", "double", "char"],
            "std::int64_t"
        )

        return function

    def CreateFunction(self, func_name, var_names, simple_return_type, raw_var_type, simple_var_types, raw_return_type):
        function = {}
        function["func_name"] = func_name
        function["var_names"] = var_names
        function["raw_var_types"] = raw_var_type
        function["simple_return_type"] = simple_return_type
        function["simple_var_types"] = simple_var_types
        function["raw_return_type"] = raw_return_type

        return function

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(unittest.main(verbosity=2))
    except KeyboardInterrupt:
        pass
