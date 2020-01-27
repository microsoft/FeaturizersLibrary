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

from Plugins.SharedLibraryPluginImpl.TypeInfoFactory import TypeInfoFactory

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
        custom_enums=None,
        member_type=None,
        create_type_info_factory_func=None,
    ):
        if custom_structs:
            assert self.TypeName in custom_structs, custom_structs
            self._member_info               = custom_structs[self.TypeName]

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, is_optional, invocation_template):
        raise Exception("'{}' is only used as a OutputType".format(self.TypeName))

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, is_optional, invocation_template):
        raise Exception("'{}' is only used as a OutputType".format(self.TypeName))

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        is_struct_member=False,
    ):
        member_statements = []

        for member_name, member_tif in six.iteritems(self._member_info):
            member_statements.append(
                member_tif.GetOutputInfo(
                    "{}{}{}".format(
                        arg_name,
                        "." if is_struct_member else "->",
                        member_name,
                    ),
                    "{}.{}".format(result_name, member_name),
                    is_struct_member=True,
                ).InvocationStatements,
            )

        return self.Result(
            [
                "/*out via struct*/ {}{} {}".format(
                    self.TypeName,
                    "" if is_struct_member else " *",
                    arg_name,
                )
            ],
            """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                name=arg_name,
            ),
            "\n".join(member_statements),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        member_validation = []
        member_statements = []

        for member_name, member_tif in six.iteritems(self._member_info):
            output_info = member_tif.GetDestroyOutputInfo(
                "{}->{}".format(arg_name, member_name),
            )
            if output_info is None:
                continue

            member_validation.append(output_info.ValidationStatements)
            member_statements.append(output_info.InvocationStatements)

        # To make things simpler for the user, always create a delete method, even if there
        # isn't anything dynamic to delete.
        if not member_statements:
            member_statements.append(
                "// There aren't any members to delete, but we are including this method for consistency",
            )

        return self.Result(
            ["/*in*/ {} * {}".format(self.TypeName, arg_name)],
            textwrap.dedent(
                """\
                if({name} == nullptr) throw std::invalid_argument("'{name}' is null");
                {validation}
                """,
            ).format(
                name=arg_name,
                validation="\n".join(member_validation),
            ),
            "\n".join(member_statements),
        )


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
@Interface.staticderived
class TimePointTypeInfoFactory(_StructTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("TimePoint")
    CppType                                 = Interface.DerivedProperty("TimePoint")


# ----------------------------------------------------------------------
@Interface.staticderived
class HashOneHotEncodingTypeInfoFactory(_StructTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("HashOneHotEncoding")
    CppType                                 = Interface.DerivedProperty("HashOneHotEncoding")


# ----------------------------------------------------------------------
@Interface.staticderived
class OneHotEncodingTypeInfoFactory(_StructTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("OneHotEncoding")
    CppType                                 = Interface.DerivedProperty("OneHotEncoding")
