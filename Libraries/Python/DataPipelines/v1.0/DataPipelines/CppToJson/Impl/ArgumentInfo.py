# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the ArgumentInfo object"""

import os

import CommonEnvironment

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class ArgumentInfo(object):
    """Contains information about a method or constructor's arguments"""

    # ----------------------------------------------------------------------
    def __init__(self, variable_info):
        # `variable_info` is a list of tuples, where each tuple is in the form:
        #   (
        #       <var_name>,
        #       <raw_var_type>,             # "int const &"
        #       <simple_var_type>,          # "int"
        #   )

        self.VariableInfo                   = variable_info

    # ----------------------------------------------------------------------
    def __repr__(self):
        return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    def __hash__(self):
        return hash(tuple(self.VariableInfo))

    # ----------------------------------------------------------------------
    def EnumerateVarNames(self):
        for name, _, _ in self.VariableInfo:
            yield name

    # ----------------------------------------------------------------------
    def EnumerateRawVarTypes(self):
        for _, raw_var_type, _ in self.VariableInfo:
            yield raw_var_type

    # ----------------------------------------------------------------------
    def EnumerateSimpleVarTypes(self):
        for _, _, simple_var_type in self.VariableInfo:
            yield simple_var_type

    # ----------------------------------------------------------------------
    def ToDict(self):
        return {
            "var_names" : list(self.EnumerateVarNames()),
            "raw_var_types" : list(self.EnumerateRawVarTypes()),
            "simple_var_types" : list(self.EnumerateSimpleVarTypes()),
        }
