# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the DatetimeTypeInfo object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class DatetimeTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("datetime")
    CppType                                 = Interface.DerivedProperty("std::chrono::system_clock::time_point")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        if self.IsOptional:
            return "Microsoft::Featurizer::Traits<decltype({input_name})>::IsNull({input_name}) ? nullptr : CreateDateTimeParameter(*{input_name})".format(
                input_name=input_name,
            )

        return "CreateDateTimeParameter({input_name})".format(
            input_name=input_name,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputBufferArgs(
        self,
        input_name='input',
    ):
        raise NotImplementedError("Not implemented yet")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        invocation_template,
        result_name="result",
    ):
        raise NotImplementedError("Not implemented yet")
