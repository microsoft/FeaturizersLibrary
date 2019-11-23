# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Struct object"""

import os

import CommonEnvironment

from DataPipelines.CppToJson.Impl.ArgumentInfo import ArgumentInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class Struct(ArgumentInfo):
    """Captures information about a C++ class or struct"""

    # ----------------------------------------------------------------------
    def __init__(
        self,
        name,
        definition_line,
        filename,
        variable_info,
        base_structs=None,
        constructor_list=None,
        has_move_constructor=None,
        has_copy_constructor=None,
        has_private=None,
        has_other=None
    ):
        super(Struct, self).__init__(
            variable_info=variable_info,
        )

        self.Name                           = name
        self.DefinitionLine                 = definition_line
        self.Filename                       = filename

        self.constructor_list               = constructor_list or []
        self.base_structs                   = base_structs or []

        self.has_move_constructor           = has_move_constructor or False
        self.has_copy_constructor           = has_copy_constructor or False
        self.has_private                    = has_private or False
        self.has_other                      = has_other or False

    # ----------------------------------------------------------------------
    def __repr__(self):
        return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    def ToDict(self):
        results = {}

        results["name"]                     = self.Name
        results["definition_line"]          = self.DefinitionLine

        for k, v in super(Struct, self).ToDict().items():
            results[k] = v

        results["constructor_list"]         = [constructor.ToDict() for constructor in self.constructor_list]
        results["base_structs"]             = self.base_structs

        return results
