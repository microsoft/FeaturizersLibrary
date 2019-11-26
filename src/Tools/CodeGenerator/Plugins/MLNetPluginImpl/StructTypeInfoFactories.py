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

from Plugins.MLNetPluginImpl.TypeInfoFactory import TypeInfoFactory

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
    @classmethod
    @Interface.override
    def GetNativeInputInfo(self, is_optional):
        raise Exception("'TimePoint' is only used as a OutputType")


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------

# TODO: This is not supported yet

# @Interface.staticderived
# class TimePointTypeInfoFactory(_StructTypeInfoFactory):
#     TypeName                                = Interface.DerivedProperty("TimePoint")
#
#     # ----------------------------------------------------------------------
#     @Interface.override
#     def GetNativeOutputInfo(
#         self,
#         is_struct=False,
#         featurizer_name = "",
#     ):
#         result_time_point_name = "{}_item".format(arg_name)
#
#         member_statements = []
#
#         for member_name, member_info in six.iteritems(self._member_info):
#             member_statements.append(
#                 member_info.GetNativeOutputInfo(
#                     "{}.{}".format(result_time_point_name, member_name),
#                     "{}.{}".format(result_name, member_name),
#                     is_struct=True,
#                     featurizer_name = featurizer_name,
#                 ).InvocationStatement,
#             )
#
#         return self.Result(
#             ["/*out*/ TimePoint *{} {}".format("" if is_struct else "*", arg_name)],
#             """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
#                 name=arg_name,
#             ),
#             textwrap.dedent(
#                 """\
#                 TimePoint {result_time_point_name};
#
#                 {member_statements}
#
#                 *{name} = std::make_unique<TimePoint>(std::move({result_time_point_name})).release();
#                 """,
#             ).format(
#                 name=arg_name,
#                 result=result_name,
#                 result_time_point_name=result_time_point_name,
#                 member_statements="\n".join(member_statements),
#             ),
#         )
