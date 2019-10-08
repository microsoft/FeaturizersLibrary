# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

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
class TypeInfo(Interface.Interface):
    """Information about a specific named type"""

    # ----------------------------------------------------------------------
    # |  Public Types
    class Info(object):
        """Information about the type when it is used in various scenarios"""

        def __init__(self, parameter_decl, validation_statements, invocation_statement):
            self.ParameterDecl              = parameter_decl
            self.ValidationStatements       = validation_statements
            self.InvocationStatement        = invocation_statement

    # ----------------------------------------------------------------------
    # |  Public Methods
    @staticmethod
    @Interface.abstractmethod
    def GetInputInfo(arg_name, is_optional, invocation_template):
        """Return `Info` when the type is used as an input argument.

           `invocation_template` is a string template string that should
           be formatted with the arguments.
        """
        raise Exception("Abstract Method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetInputBufferInfo(arg_name, is_optional, invocation_template):
        """Return `Info` when the type is used as an input argument for a buffer.

           `invocation_template` is a string template string that should
           be formatted with the arguments.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetOutputInfo(
        arg_name,
        result_name="result",
        is_struct=False,
    ):
        """Return `Info` when the type is used an an output argument. `result_name` is the name of the
           result returned by the shared library code.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------\
    @staticmethod
    @Interface.abstractmethod
    def GetDestroyOutputInfo(
        arg_name="result",
    ):
        """Return `Info` when the type requires explicit destruction or `None` if no explicit destruction functionality is required"""
        raise Exception("Abstract method")


_SUPPORTED_CUSTOM_TYPES                     = {
    "TimePoint": (lambda custom_structs: _TimePointTypeInfo(custom_structs)),
}

# ----------------------------------------------------------------------
@Interface.staticderived
class Plugin(PluginBase):
    # ----------------------------------------------------------------------
    # |  Properties
    Name                                    = Interface.DerivedProperty("SharedLibrary")
    Description                             = Interface.DerivedProperty(
        "Generates code used during the Shared Library import/export layer interfacing with the shared C++ functionality",
    )

    # ----------------------------------------------------------------------
    # |  Methods
    @staticmethod
    @Interface.override
    def Generate(data, output_dir, status_stream):
        result_code = 0

        status_stream.write("Preprocessing data...")
        with status_stream.DoneManager():
            # Convert the types into the corresponding C types that will be used
            # in the Shared Library interface.
            c_data = []

            for items in data:
                c_data.append([CData(item) for item in items])

        status_stream.write("Generating Common Files...")
        with status_stream.DoneManager() as this_dm:
            this_dm.result = _GenerateCommonFiles(output_dir, this_dm.stream)
            if this_dm.result != 0:
                return this_dm.result

        for desc, func in [
            ("Generating .h files...", _GenerateHeaderFile),
            ("Generating .cpp files...", _GenerateCppFile),
            # TODO: ("Generating .cpp wrappers...", _GenerateCppFile),
        ]:
            status_stream.write(desc)
            with status_stream.DoneManager(
                suffix="\n",
            ) as dm:
                for index, (items, items_c_data) in enumerate(zip(data, c_data)):
                    dm.stream.write(
                        "Processing '{}' ({} of {})...".format(
                            items[0].name,
                            index + 1,
                            len(data),
                        ),
                    )
                    with dm.stream.DoneManager() as this_dm:
                        this_dm.result = func(
                            output_dir,
                            items,
                            items_c_data,
                            this_dm.stream,
                        )

                if dm.result < 0:
                    return dm.result

                result_code = result_code or dm.result

        return result_code


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def _CreateInterfaceSubstitutionDict(item, c_data):
    template = getattr(item, "template", None)
    if template is None:
        suffix = "_"
        type_desc = ""
        cpp_template_suffix = ""
    else:
        template_desc = template.replace("std::", "")

        suffix = "_{}_".format(template_desc)
        type_desc = " <{}>".format(template_desc)
        cpp_template_suffix = "<{}>".format(template)

    # ----------------------------------------------------------------------
    def ToParamsString(params, arg_desc):
        return ", ".join(
            ["/*{}*/ {} {}".format(arg_desc, param.Type, param.Name) for param in params],
        )

    # ----------------------------------------------------------------------

    return {
        "name": item.name,
        "estimator_name": item.estimator_name,
        "suffix": suffix,
        "type_desc": type_desc,
        "cpp_template_suffix": cpp_template_suffix,
    }


# ----------------------------------------------------------------------
def _GenerateCommonFiles(output_dir, output_stream):
    with open(os.path.join(output_dir, "SharedLibrary_Common.h"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                /* ---------------------------------------------------------------------- */
                /* Copyright (c) Microsoft Corporation. All rights reserved.              */
                /* Licensed under the MIT License                                         */
                /* ---------------------------------------------------------------------- */
                #pragma once

                #include <cstddef>
                #include <stdint.h>

                #if (defined _MSC_VER)
                #   if (defined DLL_EXPORT_COMPILE)
                #       define FEATURIZER_LIBRARY_API __declspec(dllexport)
                #   else
                #       define FEATURIZER_LIBRARY_API __declspec(dllimport)
                #   endif

                #   define FEATURIZER_LIBRARY_API_PACK_PREFIX               \\
                    __pragma(pack(push))                                    \\
                    __pragma(pack(1))

                #   define FEATURIZER_LIBRARY_API_PACK_SUFFIX               __pragma(pack(pop))
                #   define FEATURIZER_LIBRARY_API_PACK_INLINE

                #elif (defined __GNUC__ || defined __clang__)
                #   if (defined DLL_EXPORT_COMPILE)
                #       define FEATURIZER_LIBRARY_API __attribute__((visibility("default")))
                #   else
                #       define FEATURIZER_LIBRARY_API
                #   endif

                #   define FEATURIZER_LIBRARY_API_PACK_PREFIX
                #   define FEATURIZER_LIBRARY_API_PACK_SUFFIX
                #   define FEATURIZER_LIBRARY_API_PACK_INLINE               __attribute__((packed))

                #else
                #   error Unrecognized compiler!
                #endif

                #if (defined __clang__)
                #   pragma clang diagnostic push
                #   pragma clang diagnostic ignored "-Wextern-c-compat" // empty struct has size 0 in C, size 1 in C++
                #endif

                extern "C" {

                struct ErrorInfoHandle {};

                FEATURIZER_LIBRARY_API bool GetErrorInfoString(/*in*/ ErrorInfoHandle *pHandle, /*out*/ char const **output_ptr, /*out*/ std::size_t *output_items);
                FEATURIZER_LIBRARY_API bool DestroyErrorInfoString(/*in*/ char const *input_ptr, /*in*/ std::size_t input_items);
                FEATURIZER_LIBRARY_API bool DestroyErrorInfo(/*in*/ ErrorInfoHandle *pHandle);

                // These values should match the values in Featurizer.h
                enum FitResultValue {
                    Complete = 1,
                    Continue,
                    ResetAndContinue
                };

                typedef unsigned char FitResult;

                // These values should match the values in Traits.h
                enum TypeIdValue {
                    StringId = 0x00000001,
                    Int8Id,
                    Int16Id,
                    Int32Id,
                    Int64Id,
                    UInt8Id,
                    UInt16Id,
                    UInt32Id,
                    UInt64Id,
                    Float16Id,
                    Float32Id,
                    Float64Id,
                    Complex64Id,
                    Complex128Id,
                    BFloat16Id,
                    BoolId,
                    TimepointId,
                    DurationId,

                    LastStaticValueId,

                    TensorId = 0x1001 | (LastStaticValueId + 1),
                    SparseTensorId = 0x1001 | (LastStaticValueId + 2),
                    TabularId = 0x1001 | (LastStaticValueId + 3),

                    NullableId = 0x1001 | (LastStaticValueId + 4),
                    VectorId = 0x1001 | (LastStaticValueId + 5),
                    MapId = 0x1002 | (LastStaticValueId + 6)
                };

                typedef uint32_t TypeId;

                } // extern "C"

                """,
            ),
        )

    with open(os.path.join(output_dir, "SharedLibrary_PointerTable.h"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                /* ---------------------------------------------------------------------- */
                /* Copyright (c) Microsoft Corporation. All rights reserved.              */
                /* Licensed under the MIT License                                         */
                /* ---------------------------------------------------------------------- */
                #pragma once

                #include "../PointerTable.h"

                extern Microsoft::Featurizer::PointerTable g_pointerTable;
                """,
            ),
        )

    with open(os.path.join(output_dir, "SharedLibrary_PointerTable.cpp"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                /* ---------------------------------------------------------------------- */
                /* Copyright (c) Microsoft Corporation. All rights reserved.              */
                /* Licensed under the MIT License                                         */
                /* ---------------------------------------------------------------------- */
                #include "SharedLibrary_PointerTable.h"

                #if (defined __clang__)
                #   pragma clang diagnostic push
                #   pragma clang diagnostic ignored "-Wexit-time-destructors"
                #endif

                Microsoft::Featurizer::PointerTable g_pointerTable;

                #if (defined __clang__)
                #   pragma clang diagnostic pop
                #endif
                """,
            ),
        )

    with open(os.path.join(output_dir, "SharedLibrary_Common.cpp"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                /* ---------------------------------------------------------------------- */
                /* Copyright (c) Microsoft Corporation. All rights reserved.              */
                /* Licensed under the MIT License                                         */
                /* ---------------------------------------------------------------------- */
                #define DLL_EXPORT_COMPILE

                #include <memory>
                #include <string>

                #include "SharedLibrary_Common.h"
                #include "SharedLibrary_PointerTable.h"

                extern "C" {

                FEATURIZER_LIBRARY_API bool GetErrorInfoString(/*in*/ ErrorInfoHandle *pHandle, /*out*/ char const **output_ptr, /*out*/ std::size_t *output_items) {
                    if(pHandle == nullptr || output_ptr == nullptr || output_items == nullptr)
                        return false;

                    std::string const & str(*g_pointerTable.Get<std::string>(reinterpret_cast<size_t>(pHandle)));

                    char * string_buffer(new char[str.size() + 1]);

                    std::copy(str.begin(), str.end(), string_buffer);
                    string_buffer[str.size()] = 0;

                    *output_ptr = string_buffer;
                    *output_items = str.size();

                    return true;
                }

                FEATURIZER_LIBRARY_API bool DestroyErrorInfoString(/*in*/ char const *input_ptr, /*in*/ std::size_t input_items) {
                    if(input_ptr == nullptr || input_items == 0)
                        return false;

                    delete [] input_ptr;

                    return true;
                }

                FEATURIZER_LIBRARY_API bool DestroyErrorInfo(/*in*/ ErrorInfoHandle *pHandle) {
                    if(pHandle == nullptr)
                        return false;

                    size_t index = reinterpret_cast<size_t>(pHandle);

                    std::string & str(*g_pointerTable.Get<std::string>(index));

                    g_pointerTable.Remove(index);

                    delete &str;

                    return true;
                }

                } // extern "C"

                // These methods are used internally but not exported
                ErrorInfoHandle * CreateErrorInfo(std::exception const &ex) {
                    std::unique_ptr<std::string> result(std::make_unique<std::string>(ex.what()));

                    size_t index = g_pointerTable.Add(result.release());
                    return reinterpret_cast<ErrorInfoHandle *>(index);
                }

                """,
            ),
        )

    return 0


# ----------------------------------------------------------------------
def _GenerateHeaderFile(output_dir, items, c_data_items, output_stream):
    with open(
        os.path.join(output_dir, "SharedLibrary_{}.h".format(items[0].name)),
        "w",
    ) as f:
        f.write(
            textwrap.dedent(
                """\
                /* ---------------------------------------------------------------------- */
                /* Copyright (c) Microsoft Corporation. All rights reserved.              */
                /* Licensed under the MIT License                                         */
                /* ---------------------------------------------------------------------- */
                #pragma once

                #include "SharedLibrary_Common.h"

                extern "C" {

                """,
            ),
        )

        for item, c_data in zip(items, c_data_items):
            template = (
                item.template.replace("std::", "") if hasattr(item, "template") else None
            )

            d = _CreateInterfaceSubstitutionDict(item, c_data)

            construct_params = []

            if c_data.ConfigurationParamTypeInfos:
                for configuration_param, type_info in zip(
                    item.configuration_params,
                    c_data.ConfigurationParamTypeInfos,
                ):
                    info = type_info.GetInputInfo(
                        configuration_param.name,
                        getattr(configuration_param, "is_optional", False),
                        "",
                    )

                    construct_params += info.ParameterDecl

            delete_transformed_info = c_data.TransformedTypeInfo.GetDestroyOutputInfo()
            if delete_transformed_info is not None:
                delete_transformed_method = textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformedData({parameters}, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    """,
                ).format(
                    parameters=", ".join(delete_transformed_info.ParameterDecl),
                    **d
                )
            else:
                delete_transformed_method = ""

            # Create the custom structs (if any)
            custom_structs = []

            for struct_name, struct_members in six.iteritems(c_data.CustomStructs):
                members = []

                for struct_member_name, struct_member in six.iteritems(struct_members):
                    members += struct_member.GetOutputInfo(
                        struct_member_name,
                        is_struct=True,
                    ).ParameterDecl

                custom_structs.append(
                    textwrap.dedent(
                        """\
                        FEATURIZER_LIBRARY_API_PACK_PREFIX

                        struct {} {{
                            {}
                        }} FEATURIZER_LIBRARY_API_PACK_INLINE;

                        FEATURIZER_LIBRARY_API_PACK_SUFFIX

                        """,
                    ).format(
                        struct_name,
                        StringHelpers.LeftJustify(
                            "\n".join(["{};".format(member) for member in members]),
                            4,
                        ).strip(),
                    ),
                )

            custom_structs = "\n".join(custom_structs)

            f.write(
                textwrap.dedent(
                    """\
                    /* ---------------------------------------------------------------------- */
                    /* |  {name}{type_desc} */
                    {custom_structs}struct {name}{suffix}EstimatorHandle {{}};
                    struct {name}{suffix}TransformerHandle {{}};

                    /* Training Methods */
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateEstimator({construct_params}/*out*/ {name}{suffix}EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyEstimator(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    FEATURIZER_LIBRARY_API bool {name}{suffix}IsTrainingComplete(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}Fit(/*in*/ {name}{suffix}EstimatorHandle *pHandle, {input_param}, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}FitBuffer(/*in*/ {name}{suffix}EstimatorHandle *pHandle, {input_buffer_param}, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CompleteTraining(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    /* Inference Methods */
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerFromEstimator(/*in*/ {name}{suffix}EstimatorHandle *pEstimatorHandle, /*out*/ {name}{suffix}TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ {name}{suffix}TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformer(/*in*/ {name}{suffix}TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerSaveData(/*in*/ {name}{suffix}TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    FEATURIZER_LIBRARY_API bool {name}{suffix}Transform(/*in*/ {name}{suffix}TransformerHandle *pHandle, {input_param}, {transform_output_param}, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    {delete_transformed_method}
                    """,
                ).format(
                    custom_structs="" if not custom_structs else "{}\n\n".format(
                        custom_structs.strip(),
                    ),
                    construct_params="{}, ".format(
                        ", ".join(construct_params),
                    ) if construct_params else "",
                    input_param=", ".join(
                        c_data.InputTypeInfo.GetInputInfo(
                            "input",
                            getattr(item, "is_input_optional", False),
                            "",
                        ).ParameterDecl,
                    ),
                    input_buffer_param=", ".join(
                        c_data.InputTypeInfo.GetInputBufferInfo(
                            "input",
                            getattr(item, "is_input_optional", False),
                            "",
                        ).ParameterDecl,
                    ),
                    transform_output_param=", ".join(
                        c_data.TransformedTypeInfo.GetOutputInfo("output").ParameterDecl,
                    ),
                    delete_transformed_method=delete_transformed_method,
                    **d
                )
            )

        f.write(
            textwrap.dedent(
                """\
                } // extern "C"
                """,
            ),
        )


# ----------------------------------------------------------------------
def _GenerateCppFile(output_dir, items, c_data_items, output_stream):
    with open(
        os.path.join(output_dir, "SharedLibrary_{}.cpp".format(items[0].name)),
        "w",
    ) as f:
        f.write(
            textwrap.dedent(
                """\
                /* ---------------------------------------------------------------------- */
                /* Copyright (c) Microsoft Corporation. All rights reserved.              */
                /* Licensed under the MIT License                                         */
                /* ---------------------------------------------------------------------- */
                #define DLL_EXPORT_COMPILE

                #include "SharedLibrary_{name}.h"
                #include "SharedLibrary_PointerTable.h"

                #include "Archive.h"
                #include "{name}.h"

                // These method(s) are defined in SharedLibrary_Common.cpp
                ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);

                extern "C" {{

                // I don't know why MSVC thinks that there is unreachable
                // code in these methods during release builds.
                #if (defined _MSC_VER)
                #   pragma warning(push)
                #   pragma warning(disable: 4702) // Unreachable code
                #endif

                """,
            ).format(
                name=items[0].name,
            ),
        )

        for item, c_data in zip(items, c_data_items):
            template = (
                item.template.replace("std::", "") if hasattr(item, "template") else None
            )

            d = _CreateInterfaceSubstitutionDict(item, c_data)

            d["method_prefix"] = StringHelpers.LeftJustify(
                textwrap.dedent(
                    """\
                    if(ppErrorInfo == nullptr)
                        return false;

                    try {
                        *ppErrorInfo = nullptr;
                    """,
                ),
                4,
            )

            d["method_suffix"] = StringHelpers.LeftJustify(
                textwrap.dedent(
                    """\

                        return true;
                    }
                    catch(std::exception const &ex) {
                        *ppErrorInfo = CreateErrorInfo(ex);
                        return false;
                    }
                    """,
                ).rstrip(),
                4,
            )

            f.write(
                textwrap.dedent(
                    """\
                    /* ---------------------------------------------------------------------- */
                    /* |                                                                      */
                    /* |  {name}{type_desc} */
                    /* |                                                                      */
                    /* ---------------------------------------------------------------------- */
                    """,
                ).format(**d)
            )

            # CreateEstimator
            construct_params = []
            construct_validation = []
            construct_args = []

            if c_data.ConfigurationParamTypeInfos:
                for configuration_param, type_info in zip(
                    item.configuration_params,
                    c_data.ConfigurationParamTypeInfos,
                ):
                    info = type_info.GetInputInfo(
                        configuration_param.name,
                        getattr(configuration_param, "is_optional", False),
                        "{}",
                    )

                    construct_params += info.ParameterDecl

                    if info.ValidationStatements:
                        construct_validation.append(info.ValidationStatements)

                    construct_args.append(info.InvocationStatement)

            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateEstimator({params}/*out*/ {name}{suffix}EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            {validation}
                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}* pEstimator = new Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}({args}std::make_shared<Microsoft::Featurizer::AnnotationMaps>({num_output_columns}));
                            size_t index(g_pointerTable.Add(pEstimator));
                            *ppHandle = reinterpret_cast<{name}{suffix}EstimatorHandle*>(index);


                        {method_suffix}
                    }}

                    """,
                ).format(
                    params="{}, ".format(
                        ", ".join(construct_params),
                    ) if construct_params else "",
                    validation="// No validation" if not construct_validation else "\n".join(
                        construct_validation,
                    ).strip(),
                    args="{}, ".format(
                        ", ".join(construct_args),
                    ) if construct_args else "",
                    num_output_columns=item.num_output_columns,
                    **d
                )
            )

            # DestroyEstimator
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyEstimator(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

                            size_t index = reinterpret_cast<size_t>(pHandle);
                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(index);
                            g_pointerTable.Remove(index);

                            delete pEstimator;
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # IsTrainingComplete
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}IsTrainingComplete(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
                            if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pHandle)));


                            *pIsTrainingComplete = estimator.is_training_complete();
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # Fit
            input_info = c_data.InputTypeInfo.GetInputInfo(
                "input",
                getattr(item, "is_input_optional", False),
                "*pFitResult = static_cast<unsigned char>(estimator.fit({}));",
            )

            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}Fit(/*in*/ {name}{suffix}EstimatorHandle *pHandle, {param}, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
                            if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


                            {validation}

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pHandle)));


                            {statement}
                        {method_suffix}
                    }}

                    """,
                ).format(
                    param=", ".join(input_info.ParameterDecl),
                    validation="// No validation" if not input_info.ValidationStatements else StringHelpers.LeftJustify(
                        input_info.ValidationStatements.strip(),
                        8,
                    ),
                    statement=StringHelpers.LeftJustify(
                        input_info.InvocationStatement.strip(),
                        8,
                    ),
                    **d
                )
            )

            # FitBuffer
            input_info = c_data.InputTypeInfo.GetInputBufferInfo(
                "input",
                getattr(item, "is_input_optional", False),
                "*pFitResult = static_cast<unsigned char>(estimator.fit({}));",
            )

            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}FitBuffer(/*in*/ {name}{suffix}EstimatorHandle *pHandle, {param}, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
                            if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



                            {validation}

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pHandle)));

                            {statement}
                        {method_suffix}
                    }}

                    """,
                ).format(
                    param=", ".join(input_info.ParameterDecl),
                    validation="// No validation" if not input_info.ValidationStatements else StringHelpers.LeftJustify(
                        input_info.ValidationStatements.strip(),
                        8,
                    ),
                    statement=StringHelpers.LeftJustify(
                        input_info.InvocationStatement.strip(),
                        8,
                    ),
                    **d
                )
            )

            # CompleteTraining
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CompleteTraining(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
                            if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pHandle)));

                            *pFitResult = static_cast<unsigned char>(estimator.complete_training());
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # CreateTransformerFromEstimator
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerFromEstimator(/*in*/ {name}{suffix}EstimatorHandle *pEstimatorHandle, /*out*/ {name}{suffix}TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
                            if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pEstimatorHandle)));

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType*>(estimator.create_transformer().release());


                            size_t index = g_pointerTable.Add(pTransformer);
                            *ppTransformerHandle = reinterpret_cast<{name}{suffix}TransformerHandle*>(index);
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # CreateTransformerFromSavedData
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ {name}{suffix}TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
                            if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
                            if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

                            Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType>(archive).release());

                            size_t index = g_pointerTable.Add(pTransformer);
                            *ppTransformerHandle = reinterpret_cast<{name}{suffix}TransformerHandle*>(index);
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # DestroyTransformer
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformer(/*in*/ {name}{suffix}TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

                            size_t index = reinterpret_cast<size_t>(pHandle);
                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType>(index);
                            g_pointerTable.Remove(index);


                            delete pTransformer;
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # CreateTransformerSaveData
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerSaveData(/*in*/ {name}{suffix}TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
                            if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
                            if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType>(reinterpret_cast<size_t>(pHandle)));
                            Microsoft::Featurizer::Archive archive;

                            transformer.save(archive);

                            Microsoft::Featurizer::Archive::ByteArray const buffer(archive.commit());

                            unsigned char * new_buffer(new unsigned char[buffer.size()]);

                            std::copy(buffer.begin(), buffer.end(), new_buffer);

                            *ppBuffer = new_buffer;
                            *pBufferSize = buffer.size();
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # DestroyTranformerSaveData
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
                            if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");

                            delete [] pBuffer;
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # Transform
            input_info = c_data.InputTypeInfo.GetInputInfo(
                "input",
                getattr(item, "is_input_optional", False),
                "auto result(transformer.execute({}));",
            )

            output_info = c_data.TransformedTypeInfo.GetOutputInfo("output")

            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}Transform(/*in*/ {name}{suffix}TransformerHandle *pHandle, {input_param}, {output_param}, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


                            {input_validation}
                            {output_validation}

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType>(reinterpret_cast<size_t>(pHandle)));

                            // Input
                            {input_statement}

                            // Output
                            {output_statement}
                        {method_suffix}
                    }}

                    """,
                ).format(
                    input_param=", ".join(input_info.ParameterDecl),
                    output_param=", ".join(output_info.ParameterDecl),
                    input_validation="// No input validation" if not input_info.ValidationStatements else StringHelpers.LeftJustify(
                        input_info.ValidationStatements.strip(),
                        8,
                    ),
                    output_validation="// No output validation" if not output_info.ValidationStatements else StringHelpers.LeftJustify(
                        output_info.ValidationStatements.strip(),
                        8,
                    ),
                    input_statement=StringHelpers.LeftJustify(
                        input_info.InvocationStatement.strip(),
                        8,
                    ),
                    output_statement=StringHelpers.LeftJustify(
                        output_info.InvocationStatement.strip(),
                        8,
                    ),
                    **d
                )
            )

            # DestroyTransformedData (optional)
            output_info = c_data.TransformedTypeInfo.GetDestroyOutputInfo()
            if output_info is not None:
                f.write(
                    textwrap.dedent(
                        """\
                        FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformedData({param}, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                            {method_prefix}
                                {validation}

                                {statement}
                            {method_suffix}
                        }}

                        """,
                    ).format(
                        param=", ".join(output_info.ParameterDecl),
                        validation="// No validation" if not output_info.ValidationStatements else StringHelpers.LeftJustify(
                            output_info.ValidationStatements.strip(),
                            8,
                        ),
                        statement=StringHelpers.LeftJustify(
                            output_info.InvocationStatement.strip(),
                            8,
                        ),
                        **d
                    )
                )

        f.write(
            textwrap.dedent(
                """\

                #if (defined _MSC_VER)
                #   pragma warning(pop)
                #endif

                } // extern "C"
                """,
            ),
        )


# ----------------------------------------------------------------------
# TODO: def _GenerateCppFile(output_dir, items, c_data, output_stream):
# TODO:     # Write files that provide RAII wrappers around the export C functions.
# TODO:     pass


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
class CData(object):
    # ----------------------------------------------------------------------
    # |
    # |  Public Data
    # |
    # ----------------------------------------------------------------------
    INPUT_VAR_NAME                          = "input"
    INPUT_BUFFER_VAR_NAME                   = "input_buffer"
    OUTPUT_VAR_NAME                         = "output"
    DELETE_TRANSFORMED_VAR_NAME             = "pTransformedData"

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(self, item):
        type_info_visitor = _TypeInfoVisitor()
        supported_custom_types = set(six.iterkeys(_SUPPORTED_CUSTOM_TYPES))

        # Create the custom structs
        custom_structs = OrderedDict()

        for custom_struct in getattr(item, "custom_structs", []):
            members = OrderedDict()

            for member in custom_struct.members:
                members[member.name] = type_info_visitor.Accept(
                    member.type,
                    supported_custom_types=supported_custom_types,
                    custom_structs=custom_structs,
                )

            custom_structs[custom_struct.name] = members

        # Create the configuration params
        configuration_param_type_infos = []

        for configuration_param in getattr(item, "configuration_params", []):
            configuration_param_type_infos.append(
                type_info_visitor.Accept(
                    configuration_param.type,
                    supported_custom_types=supported_custom_types,
                    custom_structs=custom_structs,
                ),
            )

        # Input
        input_type_info = type_info_visitor.Accept(
            item.input_type,
            supported_custom_types=supported_custom_types,
            custom_structs=custom_structs,
        )

        # Output
        transformed_type_info = type_info_visitor.Accept(
            item.transformed_type,
            supported_custom_types=supported_custom_types,
            custom_structs=custom_structs,
        )

        # Commit the results
        self.CustomStructs                  = custom_structs
        self.ConfigurationParamTypeInfos    = configuration_param_type_infos
        self.InputTypeInfo                  = input_type_info
        self.TransformedTypeInfo            = transformed_type_info


# ----------------------------------------------------------------------
# |
# |  Private Types
# |
# ----------------------------------------------------------------------
@Interface.staticderived
class _TypeInfoVisitor(TypeVisitorBase):
    # ----------------------------------------------------------------------
    # |  Public Methods
    @classmethod
    @Interface.override
    def OnInt8(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int8_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnInt16(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int16_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnInt32(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int32_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnInt64(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int64_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt8(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint8_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt16(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint16_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt32(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint32_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt64(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint64_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnFloat32(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::float_t", "float")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnFloat64(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::double_t", "double")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnBool(cls, *args, **kwargs):
        return _ScalarTypeInfo("bool")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnString(cls, *args, **kwargs):
        return _StringTypeInfo()

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnArray(cls, template_args, arg_name, is_input_optional):
        raise Exception("TODO: Not implemented")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def OnVector(*args, **kwargs):
        raise Exception("TODO: Not implemented")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def OnMap(*args, **kwargs):
        raise Exception("TODO: Not implemented")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def OnCustomType(type, *args, **kwargs):
        return _SUPPORTED_CUSTOM_TYPES[type](*args, **kwargs)


# ----------------------------------------------------------------------
class _ScalarTypeInfo(TypeInfo):
    """Functionality for scalar types"""

    # ----------------------------------------------------------------------
    def __init__(
        self,
        cpp_type,
        interface_type=None,
    ):
        if interface_type is None:
            interface_type = cpp_type.replace("std::", "")

        self._cpp_type                      = cpp_type
        self._interface_type                = interface_type

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, is_optional, invocation_template):
        if is_optional:
            input_type = "{} const *".format(self._interface_type)
            invocation_statement = invocation_template.format(
                "{name} != nullptr ? *{name} : Microsoft::Featurizer::Traits<{cpp_type}>::CreateNullValue()".format(
                    name=arg_name,
                    cpp_type=self._cpp_type,
                ),
            )
        else:
            input_type = self._interface_type
            invocation_statement = invocation_template.format(arg_name)

        return self.Info(
            ["/*in*/ {} {}".format(input_type, arg_name)],
            None,                           # No validation
            invocation_statement,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, is_optional, invocation_template):
        if is_optional:
            input_type = "{} const * const *".format(self._interface_type)

            validation_suffix = textwrap.dedent(
                """\
                std::vector<Microsoft::Featurizer::Traits<{cpp_type}>::nullable_type> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                {cpp_type} const * const * const {name}_end({name}_ptr + {name}_items);

                while({name}_ptr != {name}_end) {{
                    {name}_buffer.emplace_back(*{name}_ptr ? **{name}_ptr : Microsoft::Featurizer::Traits<{cpp_type}>::CreateNullValue());
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                cpp_type=self._interface_type,
            )

            invocation_statement = invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
                ),
            )
        else:
            input_type = "{} const *".format(self._interface_type)
            validation_suffix = None
            invocation_statement = invocation_template.format(
                "{name}_ptr, {name}_items".format(
                    name=arg_name,
                ),
            )

        return self.Info(
            [
                "/*in*/ {type} {name}_ptr".format(
                    type=input_type,
                    name=arg_name,
                ),
                "/*in*/ std::size_t {name}_items".format(
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");
                {validation_suffix}
                """,
            ).format(
                name=arg_name,
                validation_suffix="\n{}\n".format(
                    validation_suffix,
                ) if validation_suffix else "",
            ),
            invocation_statement,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        is_struct=False,
    ):
        return self.Info(
            [
                "/*out*/ {}{} {}".format(
                    self._interface_type,
                    "" if is_struct else " *",
                    arg_name,
                ),
            ],
            """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                name=arg_name,
            ),
            "{}{} = {};".format("" if is_struct else "*", arg_name, result_name),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        return None


# ----------------------------------------------------------------------
@Interface.staticderived
class _StringTypeInfo(TypeInfo):
    """Functionality for strings"""

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetInputInfo(cls, arg_name, is_optional, invocation_template):
        if is_optional:
            validation = ""
            invocation = invocation_template.format(
                "{name} ? std::string({name}) : nonstd::optional<std::string>()".format(
                    name=arg_name,
                ),
            )
        else:
            validation = """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                name=arg_name,
            )
            invocation = invocation_template.format(arg_name)

        return cls.Info(
            ["/*in*/ char const *{}".format(arg_name)],
            validation,
            invocation,
        )

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetInputBufferInfo(cls, arg_name, is_optional, invocation_template):
        if is_optional:
            validation_suffix = textwrap.dedent(
                """\
                std::vector<nonstd::optional<std::string>> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                char const * const * const {name}_end({name}_ptr + {name}_items);

                while({name}_ptr != {name}_end) {{
                    {name}_buffer.emplace_back(*{name}_ptr ? *{name}_ptr : nonstd::optional<std::string>());
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
            )
        else:
            validation_suffix = textwrap.dedent(
                """\
                std::vector<std::string> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                char const * const * const {name}_end({name}_ptr + {name}_items);

                while({name}_ptr != {name}_end) {{
                    {name}_buffer.emplace_back(*{name}_ptr);
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
            )

        return cls.Info(
            [
                "/*in*/ char const * const * {name}_ptr".format(
                    name=arg_name,
                ),
                "std::size_t {name}_items".format(
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");
                {validation_suffix}
                """,
            ).format(
                name=arg_name,
                validation_suffix="\n{}\n".format(
                    validation_suffix,
                ) if validation_suffix else "",
            ),
            invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetOutputInfo(
        cls,
        arg_name,
        result_name="result",
        is_struct=False,
    ):
        return cls.Info(
            [
                "/*out*/ char const *{pointer} {name}_ptr".format(
                    name=arg_name,
                    pointer="" if is_struct else "*",
                ),
                "/*out*/ std::size_t{pointer} {name}_items".format(
                    name=arg_name,
                    pointer="" if is_struct else " *",
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == nullptr) throw std::invalid_argument("'{name}_items' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                if({result_name}.empty()) {{
                    {pointer}{name}_ptr = nullptr;
                    {pointer}{name}_items = 0;
                }} else {{
                    char * string_buffer(new char[{result_name}.size() + 1]);

                    std::copy({result_name}.begin(), {result_name}.end(), string_buffer);
                    string_buffer[{result_name}.size()] = 0;

                    {pointer}{name}_ptr = string_buffer;
                    {pointer}{name}_items = {result_name}.size();
                }}
                """,
            ).format(
                name=arg_name,
                result_name=result_name,
                pointer="" if is_struct else "*",
            ),
        )

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetDestroyOutputInfo(
        cls,
        arg_name="result",
    ):
        return cls.Info(
            [
                "/*in*/ char const *{name}_ptr".format(
                    name=arg_name,
                ),
                "/*in*/ std::size_t {name}_items".format(
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr && {name}_items != 0) throw std::invalid_argument("Invalid buffer");
                if({name}_ptr != nullptr && {name}_items == 0) throw std::invalid_argument("Invalid buffer");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                if({name}_ptr)
                    delete [] {name}_ptr;
                """,
            ).format(
                name=arg_name,
            ),
        )


# ----------------------------------------------------------------------
class _TimePointTypeInfo(TypeInfo):
    """Functionality for TimePoints, used in the DateTimeFeaturizer"""

    # ----------------------------------------------------------------------
    def __init__(self, custom_structs):
        assert "TimePoint" in custom_structs, custom_structs
        self._member_info                   = custom_structs["TimePoint"]

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetInputInfo(arg_name, is_optional, invocation_template):
        raise Exception("'TimePoint' is only used as a TransformedType")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetInputBufferInfo(arg_name, is_optional, invocation_template):
        raise Exception("'TimePoint' is only used as a TransformedType")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        is_struct=False,
    ):
        result_time_point_name = "{}_item".format(arg_name)

        member_statements = []

        for member_name, member_info in six.iteritems(self._member_info):
            member_statements.append(
                member_info.GetOutputInfo(
                    "{}.{}".format(result_time_point_name, member_name),
                    "{}.{}".format(result_name, member_name),
                    is_struct=True,
                ).InvocationStatement,
            )

        return self.Info(
            ["/*out*/ TimePoint *{} {}".format("" if is_struct else "*", arg_name)],
            """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                TimePoint {result_time_point_name};

                {member_statements}

                *{name} = std::make_unique<TimePoint>(std::move({result_time_point_name})).release();
                """,
            ).format(
                name=arg_name,
                result=result_name,
                result_time_point_name=result_time_point_name,
                member_statements="\n".join(member_statements),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        member_validation = []
        member_statements = []

        for member_name, member_info in six.iteritems(self._member_info):
            output_info = member_info.GetDestroyOutputInfo(
                "{}->{}".format(arg_name, member_name),
            )
            if output_info is None:
                continue

            member_validation.append(output_info.ValidationStatements)
            member_statements.append(output_info.InvocationStatement)

        return self.Info(
            ["/*in*/ TimePoint * {}".format(arg_name)],
            "\n".join(member_validation),
            textwrap.dedent(
                """\
                {statements}

                delete {name};
                """,
            ).format(
                statements="\n".join(member_statements).strip(),
                name=arg_name,
            ),
        )


# ----------------------------------------------------------------------
# |
# |  Private Methods
# |
# ----------------------------------------------------------------------
def _IsScalarType(cpp_type):
    cpp_type = cpp_type.replace("std::", "")

    return cpp_type in [
        "int8_t",
        "int16_t",
        "int32_t",
        "int64_t",
        "uint8_t",
        "uint16_t",
        "uint32_t",
        "uint64_t",
        "float",
        "double",
        "bool",
    ]
