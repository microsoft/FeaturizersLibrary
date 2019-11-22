# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the CustomStructInfo object"""

import os

import CommonEnvironment
from CommonEnvironment import Interface

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class CustomStructInfo(Interface.Interface):
    """Abstract base class for the integration of custom structs into the OnnxRuntime code generator"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def StructName(self):
        """Name of the struct"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetDefOutputStatementsConstraintsAndSuffix():
        """\
        Returns '.Output' statements required when invoking MS_AUTOML_OPERATOR_SCHEMA.

        Example result:
            [
                '.Output(0, "Year", "Calendar Year", "T1")',
                '.Output(1, "Month", "Calendar Month", "T2"),
                ...
            ],
            {
                "T1" : '.TypeConstraint("T1", {"tensor(int32)"}, "")',
                "T2" : '.TypeConstraint("T2", {"tensor(uint8)"}, "")',
            },
            ".TypeAndShapeInferenceFunction(...)"
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetKernelInitializeAssignAndPreprocessorStatements(transformer_name):
        """\
        Returns statements required when implementing the kernal.

        Example result:
            [
                'Tensor * year_tensor(ctx->Output(0, input_tensor->Shape()));'
                'Tensor * month_tensor(ctx->Output(1, input_tensor->Shape()));',
                'int32_t * year_data(year_tensor->MutableData<int32_t>());'
                'uint8_t * month_data(month_tensor->MutableData<uint8_t>());'
            ],
            [
                'auto time_point(transformer.execute(input_data[i]));',
                'year_data[i] = time_point.year;'
                'month_data[i] = time_point.month;',
            ],
            [
                textwrap.dedent(
                    '''\
                    ONNX_OPERATOR_KERNEL_EX(
                        DateTimeTransformer,
                        kMSUatoMLDomain,
                        1,
                        kCpuExecutionProvider,
                        KernelDefBuilder()
                            .TypeConstraint("OutputT0", DataTypeImpl::GetTensorType<int64_t>())
                            .TypeConstraint("OutputT1", DataTypeImpl::GetTensorType<uint8_t>())
                    );
                    ''',
                ),
            ]
        """
        raise Exception("Abstract method")