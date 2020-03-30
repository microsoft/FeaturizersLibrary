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

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class _StructTypeInfo(TypeInfo):
    """Functionality common to all output structs"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        *args,
        custom_structs=None,
        **kwargs
    ):
        if custom_structs:
            super(_StructTypeInfo, self).__init__(
                *args,
                custom_structs=custom_structs,
                **kwargs
            )

            assert self.TypeName in custom_structs, custom_structs
            self._member_info               = custom_structs[self.TypeName]

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
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
            [self.Type(self.TypeName, result_name)],
            "&{}".format(result_name),
            textwrap.dedent(
                """\
                results.emplace_back({result});
                """,
            ).format(
                result=result_name,
            ),
            "&{}".format(result_name),
            destroy_inline=False,
        )


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
@Interface.staticderived
class TimePointTypeInfo(_StructTypeInfo):
    TypeName                                = Interface.DerivedProperty("TimePoint")
    CppType                                 = Interface.DerivedProperty("TimePoint")
