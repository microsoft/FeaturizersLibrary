# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the StandardCustomStructInfo object"""

import os
import re
import textwrap
from collections import OrderedDict

import six

import CommonEnvironment
from CommonEnvironment import Interface
from CommonEnvironment import StringHelpers

from Plugins.OnnxRuntimePluginImpl.CustomStructInfo import CustomStructInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class StandardCustomStructInfo(CustomStructInfo):
    """\
    Standard implementation that doesn't transform the structure, but rather
    writes each element to an output tensor.
    """

    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    StructName                              = Interface.DerivedProperty("")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(self, custom_struct):
        type_to_template_lookup = OrderedDict()

        for member in custom_struct.members:
            if member.type not in type_to_template_lookup:
                type_to_template_lookup[member.type] = "OutputT{}".format(
                    len(type_to_template_lookup),
                )

        template_to_types = OrderedDict()

        for k, v in six.iteritems(type_to_template_lookup):
            template_to_types[v] = k

        # Commit
        self._custom_struct                 = custom_struct
        self._type_to_template_lookup       = type_to_template_lookup
        self._template_to_types             = template_to_types

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDefOutputStatementsConstraintsAndSuffix(self):
        # ----------------------------------------------------------------------
        def ToOrtTypeString(value):
            return value.replace("std::", "").replace("_t", "")

        # ----------------------------------------------------------------------

        output_statements = []

        for index, member in enumerate(self._custom_struct.members):
            output_statements.append(
                '.Output({index}, "{name}", "{desc}", "{type}")'.format(
                    index=index,
                    name=member.name,
                    desc=member.description or "No information available",
                    type=self._type_to_template_lookup[member.type],
                ),
            )

        return (
            output_statements,
            OrderedDict(
                [
                    (k, [ToOrtTypeString(v)])
                    for k,
                    v in six.iteritems(self._template_to_types)
                ],
            ),
            textwrap.dedent(
                """\
                .TypeAndShapeInferenceFunction(
                    [](ONNX_NAMESPACE::InferenceContext& ctx) {{
                      const bool has_shape = hasInputShape(ctx, 1);

                      {statements}
                    }}
                )
                """,
            ).format(
                statements=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            textwrap.dedent(
                                """\
                                propagateElemTypeFromDtypeToOutput(ctx, ONNX_NAMESPACE::TensorProto_DataType_{type}, {index});
                                if(has_shape) {{
                                  propagateShapeFromInputToOutput(ctx, 1, {index});
                                }}
                                """,
                            ).format(
                                index=index,
                                type=ToOrtTypeString(member.type).upper(),
                            )
                            for index, member in enumerate(self._custom_struct.members)
                        ],
                    ),
                    6,
                ),
            )
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetKernelInitializeAssignAndPreprocessorStatements(self, transformer_name, input_transformation_statement):
        initialize_statements_part1 = []
        initialize_statements_part2 = []
        assign_statements = ["auto result(transformer.execute({}));\n".format(input_transformation_statement)]

        for index, member in enumerate(self._custom_struct.members):
            initialize_statements_part1.append(
                "Tensor* {name}_tensor(ctx->Output({index}, input_tensor->Shape()));".format(
                    name=member.name,
                    index=index,
                ),
            )

            initialize_statements_part2.append(
                "{type}* {name}_data({name}_tensor->MutableData<{type}>());".format(
                    name=member.name,
                    type=member.type,
                ),
            )

            assign_statements.append(
                "{name}_data[i] = std::move(result.{name});".format(
                    name=member.name,
                ),
            )

        return (
            initialize_statements_part1 + [""] + initialize_statements_part2,
            assign_statements,
        )
