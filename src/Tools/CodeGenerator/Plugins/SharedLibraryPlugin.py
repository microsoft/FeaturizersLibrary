# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

import copy
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
    Name                                    = Interface.DerivedProperty("SharedLibrary")
    Description                             = Interface.DerivedProperty(
        "Generates code used during the Shared Library import/export layer interfacing with the shared C++ functionality",
    )

    # ----------------------------------------------------------------------
    # |  Methods
    @staticmethod
    @Interface.override
    def Generate(
        open_file_func,
        global_custom_structs,
        global_custom_enums,
        data,
        output_dir,
        status_stream,
    ):
        result_code = 0

        status_stream.write("Preprocessing data...")
        with status_stream.DoneManager():
            # Convert the types into the corresponding C types that will be used
            # in the Shared Library interface.
            c_data = []

            for items in data:
                c_data.append([CData(item, global_custom_structs, global_custom_enums) for item in items])

        status_stream.write("Generating Common Files...")
        with status_stream.DoneManager() as this_dm:
            this_dm.result = _GenerateCommonFiles(open_file_func, output_dir, this_dm.stream)
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
                            open_file_func,
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
        cpp_template_suffix = "" if not item.featurizer_is_a_template else "<>"
    else:
        templates = []

        suffix = "_{}_".format(template)
        type_desc = " <{}>".format(template)

        cpp_templates = []

        if item.is_input_a_template:
            cpp_templates.append(
                c_data.InputTypeInfo.GetCppTemplateSuffix(
                    getattr(item, "input_type_template_mapping", {}),
                ),
            )

        if item.is_output_a_template:
            cpp_templates.append(
                c_data.OutputTypeInfo.GetCppTemplateSuffix(
                    getattr(item, "output_type_template_mapping", {}),
                ),
            )

        assert cpp_templates
        cpp_templates = ", ".join(cpp_templates)

        cpp_template_suffix = "<{}>".format(cpp_templates)

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
def _GenerateCommonFiles(open_file_func, output_dir, output_stream):
    with open_file_func(os.path.join(output_dir, "SharedLibrary_Common.h"), "w") as f:
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

                FEATURIZER_LIBRARY_API bool GetErrorInfoString(/*in*/ ErrorInfoHandle *pHandle, /*out*/ char const **output_ptr);
                FEATURIZER_LIBRARY_API bool DestroyErrorInfoString(/*in*/ char const *input_ptr);
                FEATURIZER_LIBRARY_API bool DestroyErrorInfo(/*in*/ ErrorInfoHandle *pHandle);
                FEATURIZER_LIBRARY_API bool DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

                FEATURIZER_LIBRARY_API_PACK_PREFIX;

                struct DateTimeParameter {
                    // ----------------------------------------------------------------------
                    // |  Public Types
                    enum DateTimeTypeValue {
                        DateTimeInt64 = 1,  // Posix time
                        DateTimeString      // ISO 8601
                    };

                    typedef unsigned char DateTimeType;

                    struct StringData {
                        char const *        pBuffer;
                        size_t              cBufferElements;
                    } FEATURIZER_LIBRARY_API_PACK_INLINE;

                    union DataType {
                        int64_t             posix;
                        StringData          isoStr;
                    };

                    // ----------------------------------------------------------------------
                    // |  Public Data
                    DateTimeType            dataType;
                    DataType                data;
                } FEATURIZER_LIBRARY_API_PACK_INLINE;

                FEATURIZER_LIBRARY_API_PACK_SUFFIX;

                // These values should match the values in Featurizer.h
                enum TrainingStateValue {
                    Pending = 1,
                    Training,
                    Finished,
                    Completed
                };

                typedef unsigned char TrainingState;

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

    with open_file_func(os.path.join(output_dir, "SharedLibrary_Common.cpp"), "w") as f:
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
                #include "Traits.h"

                // Forward declaration for DestroyTransformerSaveData
                ErrorInfoHandle* CreateErrorInfo(std::exception const &ex);

                extern "C" {

                FEATURIZER_LIBRARY_API bool GetErrorInfoString(/*in*/ ErrorInfoHandle *pHandle, /*out*/ char const **output_ptr) {
                    if(pHandle == nullptr || output_ptr == nullptr)
                        return false;

                    std::string const & str(*g_pointerTable.Get<std::string>(reinterpret_cast<size_t>(pHandle)));

                    char * string_buffer(new char[str.size() + 1]);

                    std::copy(str.begin(), str.end(), string_buffer);
                    string_buffer[str.size()] = 0;

                    *output_ptr = string_buffer;

                    return true;
                }

                FEATURIZER_LIBRARY_API bool DestroyErrorInfoString(/*in*/ char const *input_ptr) {
                    if(input_ptr != nullptr)
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

                FEATURIZER_LIBRARY_API bool DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
                    if(ppErrorInfo == nullptr)
                        return false;

                    try {
                        *ppErrorInfo = nullptr;

                        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
                        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");

                        delete [] pBuffer;

                        return true;
                    }
                    catch(std::exception const &ex) {
                        *ppErrorInfo = CreateErrorInfo(ex);
                        return false;
                    }
                }

                } // extern "C"

                // These methods are used internally but not exported
                ErrorInfoHandle * CreateErrorInfo(std::exception const &ex) {
                    std::unique_ptr<std::string> result(new std::string(ex.what()));

                    size_t index = g_pointerTable.Add(result.release());
                    return reinterpret_cast<ErrorInfoHandle *>(index);
                }

                std::chrono::system_clock::time_point CreateDateTime(DateTimeParameter const &param) {
                    if(param.dataType == DateTimeParameter::DateTimeTypeValue::DateTimeInt64)
                        return std::chrono::system_clock::from_time_t(param.data.posix);

                    if(param.dataType == DateTimeParameter::DateTimeTypeValue::DateTimeString)
                        return Microsoft::Featurizer::Traits<std::chrono::system_clock::time_point>::FromString(param.data.isoStr.pBuffer);

                    throw std::runtime_error("'type' is invalid");
                }
                """,
            ),
        )

    with open_file_func(os.path.join(output_dir, "SharedLibrary_Common.hpp"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                // ----------------------------------------------------------------------
                // Copyright (c) Microsoft Corporation. All rights reserved.
                // Licensed under the MIT License
                // ----------------------------------------------------------------------
                #pragma once

                #include "SharedLibrary_Common.h"

                DateTimeParameter CreateDateTimeParameter(int64_t const &value);
                DateTimeParameter CreateDateTimeParameter(std::string const &value);

                // ----------------------------------------------------------------------
                // ----------------------------------------------------------------------
                // ----------------------------------------------------------------------
                inline DateTimeParameter CreateDateTimeParameter(int64_t const &value) {
                    DateTimeParameter       result;

                    result.dataType = DateTimeParameter::DateTimeTypeValue::DateTimeInt64;
                    result.data.posix = value;

                    return result;
                }

                inline DateTimeParameter CreateDateTimeParameter(std::string const &value) {
                    DateTimeParameter       result;

                    result.dataType = DateTimeParameter::DateTimeTypeValue::DateTimeString;
                    result.data.isoStr.pBuffer = value.c_str();
                    result.data.isoStr.cBufferElements = value.size();

                    return result;
                }
                """,
            ),
        )

    with open_file_func(os.path.join(output_dir, "SharedLibrary_PointerTable.h"), "w") as f:
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

    with open_file_func(os.path.join(output_dir, "SharedLibrary_PointerTable.cpp"), "w") as f:
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

    return 0


# ----------------------------------------------------------------------
def _GenerateHeaderFile(open_file_func, output_dir, items, c_data_items, output_stream):
    with open_file_func(
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

        wrote_custom_data = False

        for item, c_data in zip(items, c_data_items):
            template = getattr(item, "template", None)

            d = _CreateInterfaceSubstitutionDict(item, c_data)

            construct_params = []

            if c_data.ConfigurationParamTypeInfos:
                for configuration_param, type_info in zip(
                    item.configuration_params,
                    c_data.ConfigurationParamTypeInfos,
                ):
                    info = type_info.GetInputInfo(configuration_param.name, "")
                    construct_params += ["/*in*/ {} {}".format(p.Type, p.Name) for p in info.Parameters]

            if item.has_dynamic_output:
                delete_transformed_info = c_data.DynamicOutputTypeInfo.GetDestroyOutputInfo()
            else:
                delete_transformed_info = c_data.OutputTypeInfo.GetDestroyOutputInfo()

            if delete_transformed_info is not None:
                delete_transformed_method = textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformedData({parameters}, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    """,
                ).format(
                    parameters=", ".join(["/*in*/ {} {}".format(p.Type, p.Name) for p in delete_transformed_info.Parameters]),
                    **d
                )
            else:
                delete_transformed_method = ""

            # Create the custom structs (if any)
            custom_structs = []

            for struct_name, struct_members in six.iteritems(c_data.CustomStructs):
                members = []

                for struct_member_name, struct_member in six.iteritems(struct_members):
                    members += [
                        "/*out*/ {} {}".format(p.Type, p.Name) for p in struct_member.GetOutputInfo(
                            struct_member_name,
                            suppress_pointer=True,
                        ).Parameters
                    ]

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

            # Create the custom enums (if any)
            custom_enums = []

            for enum_name, enum_info in six.iteritems(c_data.CustomEnums):
                custom_enums.append(
                    textwrap.dedent(
                        """\
                        enum {item_name}_{enum_name}Value {{
                            {values}
                        }};

                        typedef {type} {item_name}_{enum_name}Type;
                        """,
                    ).format(
                        item_name=item.name,
                        enum_name=enum_name,
                        values=StringHelpers.LeftJustify(
                            ",\n".join(
                                [
                                    "{}_{}_{}={}".format(
                                        item.name,
                                        enum_name,
                                        this_enum_value,
                                        this_enum_integer,
                                    )
                                    for this_enum_value, this_enum_integer in six.iteritems(enum_info.values)
                                ]
                            ),
                            4,
                        ),
                        type=enum_info.underlying_type_info.CType,
                    ),
                )

            custom_enums = "\n".join(custom_enums)

            if not wrote_custom_data:
                f.write(
                    textwrap.dedent(
                        """\
                        {first_sep}{custom_structs}{sep}{custom_enums}
                        """,
                    ).format(
                        first_sep="\n" if custom_structs or custom_enums else "",
                        custom_structs="" if not custom_structs else "{}\n\n".format(custom_structs.strip()),
                        sep="\n\n" if custom_structs and custom_enums else "",
                        custom_enums="" if not custom_enums else "{}\n\n".format(custom_enums.strip()),
                        **d
                    )
                )
                wrote_custom_data = True

            flush_output_param = ", ".join(["/*out*/ {} {}".format(p.Type, p.Name) for p in c_data.DynamicOutputTypeInfo.GetOutputInfo("output").Parameters])

            if item.has_dynamic_output:
                transform_output_param = flush_output_param
            else:
                transform_output_param = ", ".join(["/*out*/ {} {}".format(p.Type, p.Name) for p in c_data.OutputTypeInfo.GetOutputInfo("output").Parameters])

            f.write(
                textwrap.dedent(
                    """\
                    /* ---------------------------------------------------------------------- */
                    /* |  {name}{type_desc} */
                    struct {name}{suffix}EstimatorHandle {{}};
                    struct {name}{suffix}TransformerHandle {{}};

                    /* Training Methods */
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateEstimator({construct_params}/*out*/ {name}{suffix}EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyEstimator(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    FEATURIZER_LIBRARY_API bool {name}{suffix}GetState(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}IsTrainingComplete(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}Fit(/*in*/ {name}{suffix}EstimatorHandle *pHandle, {input_param}, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}FitBuffer(/*in*/ {name}{suffix}EstimatorHandle *pHandle, {input_buffer_param}, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}OnDataCompleted(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CompleteTraining(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    /* Inference Methods */
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerFromEstimator(/*in*/ {name}{suffix}EstimatorHandle *pEstimatorHandle, /*out*/ {name}{suffix}TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ {name}{suffix}TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}DestroyTransformer(/*in*/ {name}{suffix}TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerSaveData(/*in*/ {name}{suffix}TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

                    FEATURIZER_LIBRARY_API bool {name}{suffix}Transform(/*in*/ {name}{suffix}TransformerHandle *pHandle, {input_param}, {transform_output_param}, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    FEATURIZER_LIBRARY_API bool {name}{suffix}Flush(/*in*/ {name}{suffix}TransformerHandle *pHandle, {flush_output_param}, /*out*/ ErrorInfoHandle **ppErrorInfo);
                    {delete_transformed_method}
                    """,
                ).format(
                    construct_params="{},".format(
                        ", ".join(construct_params),
                    ) if construct_params else "",
                    input_param=", ".join(
                        ["/*in*/ {} {}".format(p.Type, p.Name) for p in c_data.InputTypeInfo.GetInputInfo("input", "").Parameters],
                    ),
                    input_buffer_param=", ".join(
                        ["/*in*/ {} {}".format(p.Type, p.Name) for p in c_data.InputTypeInfo.GetInputBufferInfo("input", "").Parameters],
                    ),
                    transform_output_param=transform_output_param,
                    flush_output_param=flush_output_param,
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
def _GenerateCppFile(open_file_func, output_dir, items, c_data_items, output_stream):
    with open_file_func(
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
                std::chrono::system_clock::time_point CreateDateTime(DateTimeParameter const &param);

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
            template = getattr(item, "template", None)

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
                    if getattr(configuration_param, "is_enum", False):
                        invocation_template = "static_cast<typename Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::{enum_name}>({{}})".format(
                            enum_name=configuration_param.type,
                            **d
                        )
                    else:
                        invocation_template = "{}"

                    info = type_info.GetInputInfo(configuration_param.name, invocation_template)

                    construct_params += ["/*in*/ {} {}".format(p.Type, p.Name) for p in info.Parameters]

                    if info.ValidationStatements:
                        construct_validation.append(info.ValidationStatements)

                    construct_args.append(info.InvocationStatements)

            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateEstimator({params}/*out*/ {name}{suffix}EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            {validation}
                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}* pEstimator = new Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}(std::make_shared<Microsoft::Featurizer::AnnotationMaps>({num_output_columns}){col_index} {args});

                            pEstimator->begin_training();

                            size_t index(g_pointerTable.Add(pEstimator));
                            *ppHandle = reinterpret_cast<{name}{suffix}EstimatorHandle*>(index);

                        {method_suffix}
                    }}

                    """,
                ).format(
                    params="{}, ".format(
                        ", ".join(construct_params),
                    ) if construct_params else "",
                    validation=StringHelpers.LeftJustify(
                        "// No validation" if not construct_validation else "\n".join(
                            construct_validation,
                        ).strip(),
                        8,
                    ),
                    col_index=", 0" if item.creates_annotations else "",
                    args=", {}".format(
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

            # GetState
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}GetState(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
                            if(pState == nullptr) throw std::invalid_argument("'pState' is null");

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pHandle)));

                            *pState = static_cast<TrainingState>(estimator.get_state());
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

                            *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # Fit
            input_info = c_data.InputTypeInfo.GetInputInfo("input","*pFitResult = static_cast<unsigned char>(estimator.fit({}));")

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
                    param=", ".join(["/*in*/ {} {}".format(p.Type, p.Name) for p in input_info.Parameters]),
                    validation="// No validation" if not input_info.ValidationStatements else StringHelpers.LeftJustify(
                        input_info.ValidationStatements.strip(),
                        8,
                    ),
                    statement=StringHelpers.LeftJustify(
                        input_info.InvocationStatements.strip(),
                        8,
                    ),
                    **d
                )
            )

            # FitBuffer
            input_info = c_data.InputTypeInfo.GetInputBufferInfo("input", "*pFitResult = static_cast<unsigned char>(estimator.fit({}));")

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
                    param=", ".join(["/*in*/ {} {}".format(p.Type, p.Name) for p in input_info.Parameters]),
                    validation="// No validation" if not input_info.ValidationStatements else StringHelpers.LeftJustify(
                        input_info.ValidationStatements.strip(),
                        8,
                    ),
                    statement=StringHelpers.LeftJustify(
                        input_info.InvocationStatements.strip(),
                        8,
                    ),
                    **d
                )
            )

            # OnDataCompleted
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}OnDataCompleted(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pHandle)));

                            estimator.on_data_completed();
                        {method_suffix}
                    }}

                    """,
                ).format(**d)
            )

            # CompleteTraining
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CompleteTraining(/*in*/ {name}{suffix}EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix} & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}>(reinterpret_cast<size_t>(pHandle)));

                            estimator.complete_training();
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
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ {name}{suffix}TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
                            if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
                            if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

                            Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType(archive));

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
                    FEATURIZER_LIBRARY_API bool {name}{suffix}CreateTransformerSaveData(/*in*/ {name}{suffix}TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
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

            # Transform and Flush logic
            dynamic_output_info = c_data.DynamicOutputTypeInfo.GetOutputInfo("output")

            # Older compilers don't support emplace_back for bool vector types
            callback_statement = textwrap.dedent(
                """\
                std::vector<TransformedType> result;

                auto const callback(
                    [&result](TransformedType value) {{
                        result.{emplace_method}(std::move(value));
                    }}
                );
                """,
            ).format(
                emplace_method="push_back" if c_data.OutputTypeInfo.TypeName == "bool" else "emplace_back",
            )

            if item.has_dynamic_output:
                transform_input_info = c_data.InputTypeInfo.GetInputInfo("input", "transformer.execute({}, callback);")
                transform_callback_statement = callback_statement

                output_info = dynamic_output_info

            else:
                transform_input_info = c_data.InputTypeInfo.GetInputInfo("input", "TransformedType result(transformer.execute({}));")
                transform_callback_statement = ""

                output_info = c_data.OutputTypeInfo.GetOutputInfo("output")

            # Transform
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}Transform(/*in*/ {name}{suffix}TransformerHandle *pHandle, {input_param}, {output_param}, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

                            {input_validation}
                            {output_validation}

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType>(reinterpret_cast<size_t>(pHandle)));

                            using TransformedType = typename Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformedType;

                            // Input
                            {transform_callback_statement}{input_statement}

                            // Output
                            {output_statement}
                        {method_suffix}
                    }}

                    """,
                ).format(
                    input_param=", ".join(["/*in*/ {} {}".format(p.Type, p.Name) for p in transform_input_info.Parameters]),
                    output_param=", ".join(["/*out*/ {} {}".format(p.Type, p.Name) for p in output_info.Parameters]),
                    input_validation="// No input validation" if not input_info.ValidationStatements else StringHelpers.LeftJustify(
                        (transform_input_info.ValidationStatements or "").strip(),
                        8,
                    ),
                    output_validation="// No output validation" if not output_info.ValidationStatements else StringHelpers.LeftJustify(
                        output_info.ValidationStatements.strip(),
                        8,
                    ),
                    transform_callback_statement="{}\n\n        ".format(StringHelpers.LeftJustify(transform_callback_statement.rstrip(), 8)) if transform_callback_statement else "",
                    input_statement=StringHelpers.LeftJustify(
                        transform_input_info.InvocationStatements.strip(),
                        8,
                    ),
                    output_statement=StringHelpers.LeftJustify(
                        output_info.InvocationStatements.strip(),
                        8,
                    ),
                    **d
                )
            )

            # Flush
            f.write(
                textwrap.dedent(
                    """\
                    FEATURIZER_LIBRARY_API bool {name}{suffix}Flush(/*in*/ {name}{suffix}TransformerHandle *pHandle, {output_param}, /*out*/ ErrorInfoHandle **ppErrorInfo) {{
                        {method_prefix}
                            if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

                            {output_validation}

                            Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformerType>(reinterpret_cast<size_t>(pHandle)));

                            using TransformedType = typename Microsoft::Featurizer::Featurizers::{estimator_name}{cpp_template_suffix}::TransformedType;

                            {callback_statement}

                            transformer.flush(callback);

                            // Output
                            {output_statement}
                        {method_suffix}
                    }}

                    """,
                ).format(
                    output_param=", ".join(["/*out*/ {} {}".format(p.Type, p.Name) for p in dynamic_output_info.Parameters]),
                    output_validation=StringHelpers.LeftJustify(dynamic_output_info.ValidationStatements.strip(), 8),
                    callback_statement=StringHelpers.LeftJustify(callback_statement.rstrip(), 8),
                    output_statement=StringHelpers.LeftJustify(dynamic_output_info.InvocationStatements.strip(), 8),
                    **d
                ),
            )

            # DestroyTransformedData (optional)
            if item.has_dynamic_output:
                output_info = c_data.DynamicOutputTypeInfo.GetDestroyOutputInfo()
            else:
                output_info = c_data.OutputTypeInfo.GetDestroyOutputInfo()

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
                        param=", ".join(["/*out*/ {} {}".format(p.Type, p.Name) for p in output_info.Parameters]),
                        validation="// No validation" if not output_info.ValidationStatements else StringHelpers.LeftJustify(
                            output_info.ValidationStatements.strip(),
                            8,
                        ),
                        statement=StringHelpers.LeftJustify(
                            output_info.InvocationStatements.strip(),
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
    def __init__(self, item, global_custom_structs, global_custom_enums):
        # Create the custom enums
        custom_enums = OrderedDict()

        for custom_enum in itertools.chain(global_custom_enums, getattr(item, "custom_enums", [])):
            if isinstance(custom_enum.underlying_type, six.string_types):
                type_info = self.CreateTypeInfo(custom_enum.underlying_type)
                assert type_info, custom_enum.underlying_type

                custom_enum.underlying_type_info = type_info

            custom_enums[custom_enum.name] = custom_enum

        # Create the custom structs
        custom_structs = OrderedDict()

        for custom_struct in itertools.chain(global_custom_structs, getattr(item, "custom_structs", [])):
            members = OrderedDict()

            for member in custom_struct.members:
                type_info = self.CreateTypeInfo(member.type)
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
                type_info = self.CreateTypeInfo(
                    configuration_param.type,
                    custom_structs=custom_structs,
                    custom_enums=custom_enums,
                )
                assert type_info, configuration_param.type

            configuration_param_type_infos.append(type_info)

        input_type_info = self.CreateTypeInfo(
            item.input_type,
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )
        assert input_type_info, item.input_type

        output_type_info = self.CreateTypeInfo(
            item.output_type,
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )
        assert output_type_info, item.output_type

        dynamic_output_type_info = self.CreateTypeInfo(
            "vector<{}>".format(item.output_type),
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )

        # Commit the results
        self.CustomStructs                  = custom_structs
        self.CustomEnums                    = custom_enums
        self.ConfigurationParamTypeInfos    = configuration_param_type_infos
        self.InputTypeInfo                  = input_type_info
        self.OutputTypeInfo                 = output_type_info
        self.DynamicOutputTypeInfo          = dynamic_output_type_info

    # ----------------------------------------------------------------------
    def __repr__(self):
        return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    @classmethod
    def CreateTypeInfo(cls, the_type, *args, **kwargs):
        if cls._type_info_classes is None:
            from Plugins.SharedLibraryPluginImpl.DatetimeTypeInfo import DateTimeTypeInfo
            from Plugins.SharedLibraryPluginImpl.MatrixTypeInfo import MatrixTypeInfo
            from Plugins.SharedLibraryPluginImpl import ScalarTypeInfos
            from Plugins.SharedLibraryPluginImpl.SingleValueSparseVectorTypeInfo import SingleValueSparseVectorTypeInfo
            from Plugins.SharedLibraryPluginImpl.SparseVectorTypeInfo import SparseVectorTypeInfo
            from Plugins.SharedLibraryPluginImpl.StringTypeInfo import StringTypeInfo
            from Plugins.SharedLibraryPluginImpl import StructTypeInfos
            from Plugins.SharedLibraryPluginImpl.TupleTypeInfo import TupleTypeInfo
            from Plugins.SharedLibraryPluginImpl.UniqueIdTypeInfo import UniqueIdTypeInfo
            from Plugins.SharedLibraryPluginImpl.VectorTypeInfo import VectorTypeInfo

            type_info_classes = [
                DateTimeTypeInfo,
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
            create_type_info_func=lambda this_type, these_args=args, these_kwargs=kwargs: cls.CreateTypeInfo(this_type, *these_args, **these_kwargs),
            **kwargs
        )

    # ----------------------------------------------------------------------
    # |
    # |  Private Data
    # |
    # ----------------------------------------------------------------------
    _type_info_classes                      = None
