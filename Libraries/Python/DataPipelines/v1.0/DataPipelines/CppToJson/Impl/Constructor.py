# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Constructor object"""

import os

import CommonEnvironment

from DataPipelines.CppToJson.Impl.ArgumentInfo import ArgumentInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class Constructor(ArgumentInfo):
    """Captures information about a C++ constructor"""

    # ----------------------------------------------------------------------
    def __init__(
        self,
        definition_line,
        variable_info,
    ):
        self.DefinitionLine               = definition_line
        super(Constructor, self).__init__(
            variable_info=variable_info,
        )

    # ----------------------------------------------------------------------
    def __hash__(self):
        return hash((self.DefinitionLine, super(Constructor, self).__hash__()))

    # ----------------------------------------------------------------------
    def ToDict(self):
        new_dict = super(Constructor, self).ToDict()

        # If the var name is "", it means that this is a default constructor.
        if len(new_dict["var_names"]) == 1 and not new_dict["var_names"][0]:
            new_dict["var_names"] = ["other"]

        new_dict["definition_line"] = self.DefinitionLine

        return new_dict
