# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the DatetimeTypeInfo object"""

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
class DatetimeTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("datetime")
    CSharpType                              = Interface.DerivedProperty("TODO")
    CSharpTypeName                          = Interface.DerivedProperty("TODO")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @Interface.override
    def GetNativeInputInfo(self):
        return self.Result(
            "TODO: Parameter decl",
            "TODO: Validation statements or None",
            "TODO: invocation_statement",
            "TODO: conversion end",
            "TODO: delete transformed data statement or empty string",
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetNativeOutputInfo(
        self,
        is_struct=False,
        featurizer_name="",
    ):
        return cls.Result(
            "TODO: Parameter decl",
            "TODO: Validation statements or None",
            "TODO: invocation_statement",
            "TODO: conversion end",
            "TODO: delete transformed data statement or empty string",
        )
