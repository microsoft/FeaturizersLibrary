# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Function object"""

import os

import CommonEnvironment

from DataPipelines.CppToJson.Impl.ArgumentInfo import ArgumentInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class Function(ArgumentInfo):
    """\
    This class will hold a function's information, it provides __hash__ and __eq__ functions.
    It is needed so that its possible to have a dictionary using this class as a key, to keep
    track of the declaration and implementation lines and have fast lookup.
    """

    # ----------------------------------------------------------------------
    def __init__(
        self,
        func_name,
        raw_return_type,
        simple_return_type,
        variable_info,
        declaration_line,
        definition_line=None,
    ):
        super(Function, self).__init__(
            variable_info=variable_info,
        )

        self.Name                       = func_name
        self.RawReturnType              = raw_return_type
        self.SimpleReturnType           = simple_return_type
        self.DeclarationLine            = declaration_line

        self._definition_line            = definition_line


    # ----------------------------------------------------------------------
    def __hash__(self):
        return hash((self.Name, self.RawReturnType, self.SimpleReturnType, super(Function, self).__hash__()))

    # ----------------------------------------------------------------------
    @property
    def definition_line(self):
        return self._definition_line

    # ----------------------------------------------------------------------
    @definition_line.setter
    def definition_line(self, line):
        self._definition_line = line

    # ----------------------------------------------------------------------
    def ToDict(self):
        new_dict = {}

        new_dict["name"] = self.Name
        new_dict["raw_return_type"] = self.RawReturnType
        new_dict["simple_return_type"] = self.SimpleReturnType

        for k, v in super(Function, self).ToDict().items():
            new_dict[k] = v

        new_dict['declaration_line'] = self.DeclarationLine
        new_dict['definition_line'] = self.definition_line

        return new_dict
