# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the UniqueIdTypeInfo object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class UniqueIdTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("unique_id")
    CppType                                 = Interface.DerivedProperty("std::vector<std::string>")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        return (
            "{name}_buffer.data(), {name}_buffer.size()".format(
                name=input_name,
            ),
            textwrap.dedent(
                """\
                std::vector<char const *> {name}_buffer;

                {name}_buffer.reserve({name}.size());

                for(std::string const &value : {name})
                    {name}_buffer.emplace_back(value.c_str());

                """,
            ).format(
                name=input_name,
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            "BugBug100",
            [self.Type("BugBug200.0", "BugBug200.1")],
            "BugBug300",
            "BugBug400",
            "BugBug500",
            destroy_inline=True,
        )
