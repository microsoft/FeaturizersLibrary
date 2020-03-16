# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

import copy
import os
import re
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
    from Plugin import Plugin as PluginBase

# ----------------------------------------------------------------------
@Interface.staticderived
class Plugin(PluginBase):
    # ----------------------------------------------------------------------
    # |  Properties
    Name                                    = Interface.DerivedProperty("OnnxRuntime")
    Description                             = Interface.DerivedProperty(
        "Generates code used to implement ONNX Runtime Kernels",
    )

    # ----------------------------------------------------------------------
    # |  Methods
    @staticmethod
    @Interface.override
    def Generate(open_file_func, global_custom_structs, global_custom_enums, data, output_dir, status_stream):
        result_code = 0

        status_stream.write("Preprocessing data...")
        with status_stream.DoneManager():
            supported_optional_types = set(["string", "float", "double"])

            type_mappings = []
            custom_struct_data = []

            # For each item, group the types according to input and output type
            for items in data:
                assert items

                for item in items:
                    if item.input_type.endswith("?"):
                        item.input_type = item.input_type[:-1]
                        item.is_input_optional = True
                    else:
                        item.is_input_optional = False

                    if item.output_type.endswith("?"):
                        item.output_type = item.output_type[:-1]
                        item.is_output_optional = True
                    else:
                        item.is_output_optional = False

                # Ensure that the optional settings for input and output are consistent for all resolved items
                assert all(
                    item.is_input_optional == items[0].is_input_optional for item in items
                )
                assert all(
                    item.is_output_optional == items[0].is_output_optional
                    for item in items
                )

                # Create the type_mapping for these items
                input_types = OrderedDict()
                output_types = OrderedDict()

                for item in items:
                    if (
                        item.is_input_optional
                        and item.input_type not in supported_optional_types
                    ):
                        continue

                    if (
                        item.is_output_optional
                        and item.output_type not in supported_optional_types
                    ):
                        continue

                    input_types.setdefault(item.input_type, []).append(item.output_type)
                    output_types.setdefault(item.output_type, []).append(item.input_type)

                type_mappings.append((input_types, output_types))

                # Create custom struct data (if any)
                if hasattr(items[0], "custom_structs"):
                    # ----------------------------------------------------------------------
                    def CustomStructNames(item):
                        return [
                            custom_struct.name for custom_struct in item.custom_structs
                        ]

                    # ----------------------------------------------------------------------

                    initial_item_custom_struct_names = CustomStructNames(items[0])
                    assert all(
                        CustomStructNames(item) == initial_item_custom_struct_names
                        for item in items
                    )

                    custom_struct_data.append(
                        OrderedDict(
                            [
                                (
                                    custom_struct.name,
                                    _GetCustomStructTypeInfo(custom_struct),
                                )
                                for custom_struct in items[0].custom_structs
                            ],
                        ),
                    )
                else:
                    custom_struct_data.append(None)

        status_stream.write("Generating Common Files...")
        with status_stream.DoneManager() as this_dm:
            for desc, func in [
                ("Generating Global Kernel Files..", _GenerateGlobalKernels),
                ("Generating Global Def Files...", _GenerateGlobalDefs),
            ]:
                this_dm.stream.write(desc)
                with this_dm.stream.DoneManager() as dm:
                    dm.result = func(
                        open_file_func,
                        output_dir,
                        data,
                        type_mappings,
                        custom_struct_data,
                        dm.stream,
                    )

                    if dm.result < 0:
                        return dm.result

                result_code = result_code or this_dm.result

        for desc, func in [("Generating kernels...", _GenerateKernel)]:
            status_stream.write(desc)
            with status_stream.DoneManager(
                suffix="\n",
            ) as dm:
                for index, (items, type_mapping, csd) in enumerate(
                    zip(data, type_mappings, custom_struct_data),
                ):
                    dm.stream.write(
                        "Processing '{}' ({} of {})...".format(
                            items[0].name,
                            index + 1,
                            len(data),
                        ),
                    )
                    with dm.stream.DoneManager() as this_dm:
                        input_type_mapping, output_type_mapping = type_mapping

                        this_dm.result = func(
                            open_file_func,
                            output_dir,
                            items,
                            input_type_mapping,
                            output_type_mapping,
                            csd,
                            this_dm.stream,
                        )

                if dm.result < 0:
                    return dm.result

                result_code = result_code or dm.result

        return result_code


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
_cpp_type_mapping                           = {
    "int8": "int8_t",
    "int16": "int16_t",
    "int32": "int32_t",
    "int64": "int64_t",
    "uint8": "uint8_t",
    "uint16": "uint16_t",
    "uint32": "uint32_t",
    "uint64": "uint64_t",
    "float": "float",
    "double": "double",
    "string": "std::string",
    "bool": "bool",
    "datetime": "int64",
}


_cpp_input_type_transformations             = {
    # Datetimes are always int64_t in ORT, which is the posix time
    "datetime": lambda var_name: "std::chrono::system_clock::from_time_t({})".format(var_name),
}


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def _GetCppTypeMapping(
    the_type,
    recurse=True,
):
    while the_type in _cpp_type_mapping:
        the_new_type = _cpp_type_mapping[the_type]
        if the_new_type == the_type:
            break

        the_type = the_new_type

        if not recurse:
            break

    return the_type


# ----------------------------------------------------------------------
def _GenerateGlobalKernels(
    open_file_func,
    output_dir,
    all_items,
    all_type_mappings,
    all_custom_struct_data,
    output_stream,
):
    output_dir = os.path.join(output_dir, "featurizers_ops")
    FileSystem.MakeDirs(output_dir)

    with open_file_func(os.path.join(output_dir, "cpu_featurizers_kernels.h"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                // Copyright (c) Microsoft Corporation. All rights reserved.
                // Licensed under the MIT License.

                #pragma once

                #include "core/framework/op_kernel.h"
                #include "core/framework/kernel_registry.h"

                namespace onnxruntime {
                namespace featurizers {

                Status RegisterCpuMSFeaturizersKernels(KernelRegistry& kernel_registry);

                }  // namespace featurizers
                }  // namespace onnxruntime
                """,
            ),
        )

    macros = []

    for items, type_mappings in zip(all_items, all_type_mappings):
        item = items[0]
        input_type_mappings, output_type_mappings = type_mappings

        transformer_name = item.name.replace("Featurizer", "Transformer")

        macros.append(
            "ONNX_OPERATOR_KERNEL_CLASS_NAME(kCpuExecutionProvider, kMSFeaturizersDomain, 1, {})".format(
                transformer_name,
            ),
        )
        continue

    with open_file_func(os.path.join(output_dir, "cpu_featurizers_kernels.cc"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                // Copyright (c) Microsoft Corporation. All rights reserved.
                // Licensed under the MIT License.

                #include "featurizers_ops/cpu_featurizers_kernels.h"

                #include "core/graph/constants.h"
                #include "core/framework/data_types.h"

                namespace onnxruntime {{
                namespace featurizers {{

                // Forward declarations
                {kernel_classes}

                Status RegisterCpuMSFeaturizersKernels(KernelRegistry& kernel_registry) {{
                  static const BuildKernelCreateInfoFn function_table[] = {{
                    {kernel_statements}
                  }};

                  for (auto& function_table_entry : function_table) {{
                    ORT_RETURN_IF_ERROR(kernel_registry.Register(function_table_entry()));
                  }}

                  return Status::OK();
                }}

                }}  // namespace featurizers
                }}  // namespace onnxruntime
                """,
            ).format(
                kernel_classes="\n".join(["class {};".format(macro) for macro in macros]),
                kernel_statements=StringHelpers.LeftJustify(
                    ",\n".join(
                        ["BuildKernelCreateInfo<{}>".format(macro) for macro in macros],
                    ),
                    4,
                ),
            ),
        )

    return 0


# ----------------------------------------------------------------------
def _GenerateGlobalDefs(
    open_file_func,
    output_dir,
    all_items,
    all_type_mappings,
    all_custom_struct_data,
    output_stream,
):
    output_dir = os.path.join(output_dir, "core", "graph", "featurizers_ops")
    FileSystem.MakeDirs(output_dir)

    with open_file_func(os.path.join(output_dir, "featurizers_defs.h"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                // Copyright (c) Microsoft Corporation. All rights reserved.
                // Licensed under the MIT License.

                #pragma once

                namespace onnxruntime {
                namespace featurizers {

                void RegisterMSFeaturizersSchemas(void);

                }  // namespace featurizers
                }  // namespace onnxruntime
                """,
            ),
        )

    func_definitions = []

    # ----------------------------------------------------------------------
    def CreateOutputStatement(
        output_type,
        output_documentation,
        index=0,
        output_name="Output",
    ):
        return textwrap.dedent(
            """\
            .Output(
                {},
                "{}",
                "{}",
                "{}")
            """,
        ).format(index, output_name, output_documentation or "No information is available", output_type)

    # ----------------------------------------------------------------------
    def CreateTypeInferenceConstraints(output_type_mappings):
        code = []
        constraint_format = (
            "input_elem_type == ONNX_NAMESPACE::TensorProto_DataType_{input_type_upper}"
        )

        constraint_whitespace_prefix = "                        "

        for index, (output_type, input_types) in enumerate(output_type_mappings.items()):
            constraints = []
            for input_type in input_types:
                constraints.append(
                    constraint_format.format(
                        input_type_upper=input_type.upper(),
                    ),
                )

            code.append(
                textwrap.dedent(
                    """\
                    {end}if ({constraints}) {{
                      propagateElemTypeFromDtypeToOutput(ctx, ONNX_NAMESPACE::TensorProto_DataType_{output_type_upper}, 0);
                    }}""".format(
                        end="" if index == 0 else " else ",
                        output_type_upper=output_type.upper(),
                        constraints=(" ||\n{}".format(constraint_whitespace_prefix)).join(constraints),
                    ),
                ),
            )

            if index == 0:
                constraint_whitespace_prefix += "       "

        code.append(
            textwrap.dedent(
                """\
                 else {
                  fail_type_inference("input 1 is expected to have an accepted type");
                }

                if (hasInputShape(ctx, 1)) {
                  propagateShapeFromInputToOutput(ctx, 1, 0);
                }
                """,
            ),
        )

        return "".join(code)

    # ----------------------------------------------------------------------
    def CreateMacro(
        input_type,
        input_documentation,
        output_statements,
        all_constraints,
        suffix=None,
    ):
        return textwrap.dedent(
            """\
            MS_FEATURIZERS_OPERATOR_SCHEMA({transformer_name})
                .SinceVersion(1)
                .SetDomain(kMSFeaturizersDomain)
                .SetDoc(doc)
                .Input(
                    0,
                    "State",
                    "State generated during training that is used for prediction",
                    "T0")
                .Input(
                    1,
                    "Input",
                    "{input_documentation}",
                    "{input_type}")
                {output_statements}
                .TypeConstraint(
                    "T0",
                    {{"tensor(uint8)"}},
                    "No information is available"){type_constraints}{suffix};
            """,
        ).format(
            transformer_name=transformer_name,
            input_documentation=StringHelpers.LeftJustify(
                input_documentation or "No information is available",
                8,
            ),
            input_type=input_type,
            output_statements=StringHelpers.LeftJustify(
                "\n".join(output_statements).rstrip(),
                4,
            ),
            type_constraints="\n    {}".format(
                StringHelpers.LeftJustify(
                    "".join(
                        [
                            textwrap.dedent(
                                """\
                                .TypeConstraint(
                                    "{type_name}",
                                    {{{constraints}}},
                                    "No information is available")
                                """,
                            ).format(
                                type_name=type_name,
                                constraints=", ".join(
                                    [
                                        '"tensor({})"'.format(constraint)
                                        for constraint in constraints
                                    ],
                                ),
                            ) for type_name,
                            constraints in six.iteritems(all_constraints)
                        ],
                    ).rstrip(),
                    4,
                ),
            ) if all_constraints else "",
            suffix="\n    {}".format(
                StringHelpers.LeftJustify(suffix.rstrip(), 4),
            ) if suffix else "",
        )

    # ----------------------------------------------------------------------

    for items, type_mappings, custom_struct_data in zip(
        all_items,
        all_type_mappings,
        all_custom_struct_data,
    ):
        item = items[0]
        input_type_mappings, output_type_mappings = type_mappings

        transformer_name = item.name.replace("Featurizer", "Transformer")

        preprocessor_macros = []

        if _IsIdentityTypeMapping(input_type_mappings):
            preprocessor_macros.append(
                CreateMacro(
                    "T",
                    item.input_description,
                    [CreateOutputStatement("T", item.output_description)],
                    {"T": list(six.iterkeys(input_type_mappings))},
                    suffix=textwrap.dedent(
                        """\
                        .TypeAndShapeInferenceFunction(
                            [](ONNX_NAMESPACE::InferenceContext& ctx) {
                              propagateElemTypeFromInputToOutput(ctx, 1, 0);
                              if (hasInputShape(ctx, 1)) {
                                propagateShapeFromInputToOutput(ctx, 1, 0);
                              }
                            })
                        """,
                    ),
                ),
            )

        else:
            # We need to create one combined function for all output types
            all_output_types = []
            all_input_types = []

            for output_type, input_types in six.iteritems(output_type_mappings):
                all_output_types.append(output_type)
                all_input_types += input_types

            type_constraints = OrderedDict()

            if len(all_input_types) == 1:
                input_type = "tensor({})".format(
                    _GetCppTypeMapping(
                        all_input_types[0],
                        recurse=False,
                    ),
                )
            else:
                input_type = "InputT"
                type_constraints[input_type] = all_input_types

            if (
                custom_struct_data is None
                or all_output_types[0] not in custom_struct_data
            ):
                if len(all_output_types) == 1:
                    output_type = all_output_types[0]
                    output_statements = [
                        CreateOutputStatement(
                            "tensor({})".format(output_type),
                            item.output_description,
                        ),
                    ]
                    suffix = textwrap.dedent(
                        """\
                        .TypeAndShapeInferenceFunction(
                            [](ONNX_NAMESPACE::InferenceContext& ctx) {{
                              propagateElemTypeFromDtypeToOutput(ctx, ONNX_NAMESPACE::TensorProto_DataType_{output_type_upper}, 0);
                              if (hasInputShape(ctx, 1)) {{
                                propagateShapeFromInputToOutput(ctx, 1, 0);
                              }}
                            }})
                        """,
                    ).format(
                        output_type_upper=output_type.upper(),
                    )
                else:
                    output_type = "OutputT"
                    type_constraints[output_type] = all_output_types
                    output_statements = [
                        CreateOutputStatement("OutputT", item.output_description),
                    ]
                    suffix = textwrap.dedent(
                        """\
                        .TypeAndShapeInferenceFunction(
                            [](ONNX_NAMESPACE::InferenceContext& ctx) {{
                              auto input_elem_type = ctx.getInputType(1)->tensor_type().elem_type();
                              {constraints}
                            }})
                        """,
                    ).format(
                        output_type_upper=output_type.upper(),
                        constraints=StringHelpers.LeftJustify(CreateTypeInferenceConstraints(output_type_mappings), 6),
                    )
            else:
                assert custom_struct_data
                assert len(custom_struct_data) == 1, custom_struct_data

                (output_statements, custom_type_constraints, suffix) = custom_struct_data[
                    output_type
                ].GetDefOutputStatementsConstraintsAndSuffix()

                for k, v in six.iteritems(custom_type_constraints):
                    type_constraints[k] = v

            # Populate the content
            preprocessor_macros.append(
                CreateMacro(
                    input_type,
                    item.input_description,
                    output_statements,
                    type_constraints,
                    suffix=suffix,
                ),
            )

        func_definitions.append(
            textwrap.dedent(
                """\
                void Register{featurizer_name}Ver1() {{
                  static const char* doc = R"DOC(
                        {documentation}
                  )DOC";

                  {macros}
                }}
                """,
            ).format(
                featurizer_name=items[0].name,
                documentation=StringHelpers.LeftJustify(
                    item.description or "No information is available",
                    8,
                ),
                macros=StringHelpers.LeftJustify(
                    "\n".join(preprocessor_macros).rstrip(),
                    2,
                ),
            ),
        )

    with open_file_func(os.path.join(output_dir, "featurizers_defs.cc"), "w") as f:
        f.write(
            textwrap.dedent(
                """\
                // Copyright (c) Microsoft Corporation. All rights reserved.
                // Licensed under the MIT License.

                #include "core/graph/constants.h"
                #include "core/graph/featurizers_ops/featurizers_defs.h"
                #include "core/graph/op.h"

                #include "onnx/defs/schema.h"
                #include "onnx/defs/shape_inference.h"

                #define MS_FEATURIZERS_OPERATOR_SCHEMA(name) MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ_HELPER(__COUNTER__, name)
                #define MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ_HELPER(Counter, name) MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ(Counter, name)

                #define MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ(Counter, name)       \\
                  static ONNX_NAMESPACE::OpSchemaRegistry::OpSchemaRegisterOnce( \\
                      op_schema_register_once##name##Counter) ONNX_UNUSED =      \\
                      ONNX_NAMESPACE::OpSchema(#name, __FILE__, __LINE__)

                #define MS_FEATURIZERS_OPERATOR_SCHEMA_ELSEWHERE(name, schema_func) MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ_HELPER_ELSEWHERE(__COUNTER__, name, schema_func)
                #define MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ_HELPER_ELSEWHERE(Counter, name, schema_func) MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ_ELSEWHERE(Counter, name, schema_func)

                #define MS_FEATURIZERS_OPERATOR_SCHEMA_UNIQ_ELSEWHERE(Counter, name, schema_func) \\
                  static ONNX_NAMESPACE::OpSchemaRegistry::OpSchemaRegisterOnce(                  \\
                      op_schema_register_once##name##Counter) ONNX_UNUSED =                       \\
                      schema_func(ONNX_NAMESPACE::OpSchema(#name, __FILE__, __LINE__))

                namespace onnxruntime {{
                namespace featurizers {{

                using ONNX_NAMESPACE::AttributeProto;
                using ONNX_NAMESPACE::OpSchema;
                using ONNX_NAMESPACE::OPTIONAL;

                // Forward declarations
                {forward_declarations}

                // ----------------------------------------------------------------------
                // ----------------------------------------------------------------------
                // ----------------------------------------------------------------------
                void RegisterMSFeaturizersSchemas() {{
                  {func_calls}
                }}

                // ----------------------------------------------------------------------
                // ----------------------------------------------------------------------
                // ----------------------------------------------------------------------
                {func_definitions}

                }}  // namespace featurizers
                }}  // namespace onnxruntime
                """,
            ).format(
                forward_declarations="\n".join(
                    [
                        "static void Register{}Ver1();".format(items[0].name)
                        for items in all_items
                    ],
                ),
                func_calls=StringHelpers.LeftJustify(
                    "\n".join(
                        ["Register{}Ver1();".format(items[0].name) for items in all_items],
                    ),
                    2,
                ),
                func_definitions="\n".join(func_definitions).rstrip(),
            ),
        )

    return 0


# ----------------------------------------------------------------------
def _GenerateKernel(
    open_file_func,
    output_dir,
    items,
    input_type_mappings,
    output_type_mappings,
    custom_struct_data,
    status_stream,
):
    output_dir = os.path.join(output_dir, "featurizers_ops", "cpu")
    FileSystem.MakeDirs(output_dir)

    assert all(
        item.is_output_a_template == items[0].is_output_a_template for item in items
    )

    item = items[0]
    transformer_name = item.name.replace("Featurizer", "Transformer")

    prefix_statements = ""
    template_parameters = ""
    template_suffix = []

    if len(input_type_mappings) == 1:
        if len(output_type_mappings) != 1:
            # TODO: Implement this!
            status_stream.write("Multiple output types is not supported yet ({}) - restricting output to the first type (this is not a good long term solution and should be addressed as soon as possible)\n".format(item.name))

            key = next(six.iterkeys(output_type_mappings))
            output_type_mappings = {key : output_type_mappings[key]}

        input_type = _GetCppTypeMapping(next(six.iterkeys(input_type_mappings)))
        input_types = []

        # We don't need to define an Impl class Since there is only 1 input type
        class_content_template = textwrap.dedent(
            """\
            class {transformer_name} final : public OpKernel {{
             public:
              explicit {transformer_name}(const OpKernelInfo& info) : OpKernel(info) {{
              }}

              Status Compute(OpKernelContext* ctx) const override {{
                {content}

                return Status::OK();
              }}
            }};
            """,
        )

        additional_constraints = '.TypeConstraint("T1", DataTypeImpl::GetTensorType<{}>())'.format(input_type)

    else:
        input_type = "T" if _IsIdentityTypeMapping(input_type_mappings) else "InputT"
        input_types = [_GetCppTypeMapping(input_type) for input_type in six.iterkeys(input_type_mappings)]

        template_parameters = "template <typename {}>\n".format(input_type)
        template_suffix.append(input_type)

        class_content_template = textwrap.dedent(
            """\
            {template_parameters}struct {transformer_name}Impl {{
              void operator()(OpKernelContext* ctx) const {{
                {content}
              }}
            }};

            class {transformer_name} final : public OpKernel {{
             public:
              explicit {transformer_name}(const OpKernelInfo& info) : OpKernel(info) {{
              }}

              Status Compute(OpKernelContext* ctx) const override {{
                utils::MLTypeCallDispatcher<{transformer_name}Impl, {input_types}> t_disp(ctx->Input<Tensor>(1)->GetElementType());
                t_disp.Invoke(ctx);
                return Status::OK();
              }}
            }};
            """,
        )

        additional_constraints = textwrap.dedent(
            """\
            .TypeConstraint("{input_type}", {{{constraints}}})
            """,
        ).format(
            input_type=input_type,
            constraints=StringHelpers.LeftJustify(
                ",\n".join(["DataTypeImpl::GetTensorType<{}>()".format(it) for it in input_types]),
                len('.TypeConstraint("{}", {{'.format(input_type)),
            ),
        ).rstrip()

    if len(output_type_mappings) == 1:
        output_type = next(six.iterkeys(output_type_mappings))
        output_type = _GetCppTypeMapping(output_type)
    else:
        overrides = []

        for output_type, mapped_input_types in six.iteritems(output_type_mappings):
            output_type = _GetCppTypeMapping(output_type)

            for mapped_input_type in mapped_input_types:
                mapped_input_type = _GetCppTypeMapping(mapped_input_type)

                overrides.append(
                    textwrap.dedent(
                        """\
                        template <>
                        struct OutputTypeMapper<{input_type}> {{ using type = {output_type}; }};
                        """,
                    ).format(
                        input_type=mapped_input_type,
                        output_type=output_type,
                    ),
                )

        prefix_statements = textwrap.dedent(
            """\
            template <typename T>
            struct OutputTypeMapper {{}};
            {}
            """,
        ).format("".join(overrides))

        output_type = "typename OutputTypeMapper<{}>::type".format(input_type)

        if item.is_output_a_template:
            template_suffix.append(output_type)

    if template_suffix:
        template_suffix = "<{}>".format(", ".join(template_suffix))
    else:
        template_suffix = ""

    input_transformation_statement = "input_data[i]"

    if item.input_type in _cpp_input_type_transformations:
        input_transformation_statement = _cpp_input_type_transformations[item.input_type](input_transformation_statement)

    if item.is_input_optional:
        prefix_statements += textwrap.dedent(
            """\
            inline float const& PreprocessOptional(float const& value) { return value; }
            inline double const& PreprocessOptional(double const& value) { return value; }
            inline nonstd::optional<std::string> PreprocessOptional(std::string value) {
              return value.empty() ? nonstd::optional<std::string>() : nonstd::optional<std::string>(std::move(value));
            }
            """,
        )

        # We do not want a move here, as the floats and doubles don't gain anything from a move,
        # and the string will be copied to optional anyway.
        input_transformation_statement = "PreprocessOptional({})".format(input_transformation_statement)

    if custom_struct_data is None or output_type not in custom_struct_data:
        prepare_output_statements = [
            textwrap.dedent(
                """\
                Tensor* output_tensor(ctx->Output(0, input_tensor->Shape()));
                {output_type}* output_data(output_tensor->MutableData<{output_type}>());
                """,
            ).format(
                output_type=_GetCppTypeMapping(output_type),
            ),
        ]

        output_statements = [
            "output_data[i] = transformer.execute({});".format(
                input_transformation_statement,
            )
        ]

    else:
        # If the output is a custom struct, we assume that all outputs will be that custom struct
        assert len(output_type_mappings) == 1, output_type_mappings
        assert custom_struct_data
        assert len(custom_struct_data) == 1, custom_struct_data

        (
            prepare_output_statements,
            output_statements,
        ) = next(
            six.itervalues(custom_struct_data),
        ).GetKernelInitializeAssignAndPreprocessorStatements(
            transformer_name,
            input_transformation_statement,
        )

    class_content = class_content_template.format(
        transformer_name=transformer_name,
        template_parameters=template_parameters,
        input_types=", ".join(input_types),
        content=StringHelpers.LeftJustify(
            textwrap.dedent(
                """\
                // Create the transformer
                Microsoft::Featurizer::Featurizers::{transformer_name}{template_suffix} transformer(
                  [ctx](void) {{
                    const auto* state_tensor(ctx->Input<Tensor>(0));
                    const uint8_t* const state_data(state_tensor->Data<uint8_t>());

                    Microsoft::Featurizer::Archive archive(state_data, state_tensor->Shape().GetDims()[0]);
                    return Microsoft::Featurizer::Featurizers::{transformer_name}{template_suffix}(archive);
                  }}());

                // Get the input
                const auto* input_tensor(ctx->Input<Tensor>(1));
                const {input_type}* input_data(input_tensor->Data<{input_type}>());

                // Prepare the output
                {prepare_output_statements}

                // Execute
                const int64_t length(input_tensor->Shape().Size());

                for (int64_t i = 0; i < length; ++i) {{
                  {output_statements}
                }}
                """,
            ).format(
                transformer_name=transformer_name,
                template_suffix=template_suffix,
                input_type=input_type,
                prepare_output_statements="\n".join(prepare_output_statements).rstrip(),
                output_statements=StringHelpers.LeftJustify("\n".join(output_statements).rstrip(), 2),
            ).rstrip(),
            4,
        ),
    )

    with open_file_func(
        os.path.join(
            output_dir,
            "{}.cc".format(
                "_".join(re.findall("[a-zA-Z][^A-Z]*", transformer_name)).lower(),
            ),
        ),
        "w",
    ) as f:
        f.write(
            textwrap.dedent(
                """\
                // Copyright (c) Microsoft Corporation. All rights reserved.
                // Licensed under the MIT License.

                #include "core/common/common.h"
                #include "core/framework/data_types.h"
                #include "core/framework/data_types_internal.h"
                #include "core/framework/op_kernel.h"

                #include "Featurizers/{featurizer_name}.h"
                #include "Archive.h"

                namespace onnxruntime {{
                namespace featurizers {{

                {prefix_statements}{class_content}

                ONNX_OPERATOR_KERNEL_EX(
                    {transformer_name},
                    kMSFeaturizersDomain,
                    1,
                    kCpuExecutionProvider,
                    KernelDefBuilder()
                        .TypeConstraint("T0", DataTypeImpl::GetTensorType<uint8_t>())
                        {additional_constraints},
                    {transformer_name});

                }}  // namespace featurizers
                }}  // namespace onnxruntime
                """,
            ).format(
                featurizer_name=items[0].name,
                transformer_name=transformer_name,
                prefix_statements="{}\n\n".format(prefix_statements.rstrip()) if prefix_statements else "",
                class_content=class_content.rstrip(),
                additional_constraints=StringHelpers.LeftJustify(additional_constraints, 8),
            ),
        )

    return 0


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def _GetCustomStructTypeInfo(custom_struct):
    from Plugins.OnnxRuntimePluginImpl.StandardCustomStructInfo import (
        StandardCustomStructInfo,
    )

    custom_struct = copy.deepcopy(custom_struct)

    for member in custom_struct.members:
        member.type = _GetCppTypeMapping(member.type)

    return StandardCustomStructInfo(custom_struct)


# ----------------------------------------------------------------------
def _IsIdentityTypeMapping(type_mappings):
    """\
    An identity type mapping is a special case where each of the input types
    matches the output type.
    """

    for input_type, output_types in six.iteritems(type_mappings):
        if output_types != [input_type]:
            return False

    return True
