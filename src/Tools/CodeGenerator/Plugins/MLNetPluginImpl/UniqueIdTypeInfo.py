# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the UniqueIdTypeInfo object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.MLNetPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class UniqueIdTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("unique_id")
    CSharpType                              = Interface.DerivedProperty("TODO1")
    CSharpTypeName                          = Interface.DerivedProperty("TODO2")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        *args,
        member_type=None,
        create_type_info_func=None,
        **kwargs
    ):
        if member_type is None:
            return

        assert create_type_info_func is not None

        super(UniqueIdTypeInfo, self).__init__(*args, **kwargs)

        if self.IsOptional:
            raise Exception("UniqueId types cannot be optional")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetNativeInputInfo(self):
        return self.Result(
            "TODO3: Parameter decl",
            "TODO4: Validation statements",
            "TODO5: Invocation statements",
            "TODO6: Conversion end",
            "TODO7: Delete transformed data",
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetNativeOutputInfo(
        self,
        is_struct=False,
        featurizer_name="",
    ):
        return self.Result(
            "TODO8: Parameter decl",
            "TODO9: Validation statements",
            "TODO10: Invocation statements",
            "TODO11: Conversion end",
            "TODO12: Delete transformed data",
        )
