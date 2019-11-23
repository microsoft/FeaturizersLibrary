# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains structures that are used as return values"""

import os
import textwrap

import six

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfoFactory import TypeInfoFactory

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class _StructTypeInfoFactory(TypeInfoFactory):
    """Functionality common to all output structs"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        custom_structs=None,
    ):
        if custom_structs:
            assert self.TypeName in custom_structs, custom_structs
            self._member_info               = custom_structs[self.TypeName]

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        raise Exception("'{}' is only used as a OutputType".format(self.TypeName))

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            self.TypeName,
            "{} {};".format(self.TypeName, result_name),
            "&{}".format(result_name),
            "results.emplace_back({});".format(result_name),
            "&{}".format(result_name),
            destroy_inline=False,
        )


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
@Interface.staticderived
class TimePointTypeInfoFactory(_StructTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("TimePoint")


# ----------------------------------------------------------------------
@Interface.staticderived
class OneHotStructTypeInfoFactory(_StructTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("OneHotStruct")


# ----------------------------------------------------------------------
@Interface.staticderived
class HashOneHotVectorizerStructTypeInfoFactory(_StructTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("HashOneHotVectorizerStruct")
