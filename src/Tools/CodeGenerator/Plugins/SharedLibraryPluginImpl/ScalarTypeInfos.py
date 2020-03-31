# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the scalar type info objects"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class _ScalarTypeInfo(TypeInfo):
    """Functionality common to all scalars"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def CType(self):
        """C type"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        *args,
        member_type=None,
        create_type_info_func=None,
        **kwargs
    ):
        if member_type is None:
            return

        super(_ScalarTypeInfo, self).__init__(*args, **kwargs)

        self.RequiresOptionalType           = self.IsOptional and self.TypeName not in ["float", "double"]

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        if self.RequiresOptionalType:
            input_type = "{} const *".format(self.CType)
            invocation_statement = invocation_template.format(
                "{name} != nullptr ? *{name} : Microsoft::Featurizer::Traits<{cpp_type}>::CreateNullValue()".format(
                    name=arg_name,
                    cpp_type=self.CppType,
                ),
            )

        else:
            input_type = self.CType
            invocation_statement = invocation_template.format(arg_name)

        return self.Result(
            [self.Type(input_type, arg_name)],
            None,                           # No validation
            invocation_statement,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, invocation_template):
        if self.RequiresOptionalType:
            input_type = "{} const * const *".format(self.CType)

            validation_suffix = textwrap.dedent(
                """\
                std::vector<Microsoft::Featurizer::Traits<{cpp_type}>::nullable_type> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                while({name}_buffer.size() < {name}_items) {{
                    {name}_buffer.emplace_back(*{name}_ptr ? **{name}_ptr : Microsoft::Featurizer::Traits<{cpp_type}>::CreateNullValue());
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                cpp_type=self.CppType,
            )

            invocation_statement = invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
                ),
            )

            buffer_type = self.Type(
                "std::vector<Microsoft::Featurizer::Traits<{}>::nullable_type>".format(self.CppType),
                "{}_buffer".format(arg_name),
            )

        else:
            input_type = "{} const *".format(self.CType)
            validation_suffix = None
            invocation_statement = invocation_template.format(
                "{name}_ptr, {name}_items".format(
                    name=arg_name,
                ),
            )

            buffer_type = self.Type(
                "{} const *".format(self.CType),
                "{}_ptr".format(arg_name),
            )

        return self.Result(
            [
                self.Type(input_type, "{}_ptr".format(arg_name)),
                self.Type("size_t", "{}_items".format(arg_name)),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");
                {validation_suffix}
                """,
            ).format(
                name=arg_name,
                validation_suffix="\n{}\n".format(
                    validation_suffix,
                ) if validation_suffix else "",
            ),
            invocation_statement,
            input_buffer_type=buffer_type,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        suppress_pointer=False,
    ):
        if self.RequiresOptionalType:
            statement_rhs = "{name} ? new {type}(*{name}) : nullptr".format(
                name=result_name,
                type=self.CType,
            )
        else:
            statement_rhs = result_name

        return self.Result(
            [
                self.Type(
                    "{}{}{}".format(
                        self.CType,
                        "" if not self.RequiresOptionalType else "*",
                        "" if suppress_pointer else " *",
                    ),
                    arg_name,
                ),
            ],
            """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                name=arg_name,
            ),
            "{}{} = {};".format(
                "" if suppress_pointer else "*",
                arg_name,
                statement_rhs,
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        if not self.RequiresOptionalType:
            return None

        return self.Result(
            [self.Type("{} const *".format(self.CType), arg_name)],
            "",
            textwrap.dedent(
                """\
                if({name} != nullptr)
                    delete {name};
                """,
            ).format(
                name=arg_name,
            ),
        )


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
@Interface.staticderived
class Int8TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int8")
    CType                                   = Interface.DerivedProperty("int8_t")
    CppType                                 = Interface.DerivedProperty("std::int8_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int16TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int16")
    CType                                   = Interface.DerivedProperty("int16_t")
    CppType                                 = Interface.DerivedProperty("std::int16_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int32TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int32")
    CType                                   = Interface.DerivedProperty("int32_t")
    CppType                                 = Interface.DerivedProperty("std::int32_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int64TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int64")
    CType                                   = Interface.DerivedProperty("int64_t")
    CppType                                 = Interface.DerivedProperty("std::int64_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt8TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint8")
    CType                                   = Interface.DerivedProperty("uint8_t")
    CppType                                 = Interface.DerivedProperty("std::uint8_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt16TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint16")
    CType                                   = Interface.DerivedProperty("uint16_t")
    CppType                                 = Interface.DerivedProperty("std::uint16_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt32TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint32")
    CType                                   = Interface.DerivedProperty("uint32_t")
    CppType                                 = Interface.DerivedProperty("std::uint32_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt64TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint64")
    CType                                   = Interface.DerivedProperty("uint64_t")
    CppType                                 = Interface.DerivedProperty("std::uint64_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class FloatTypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("float")
    CType                                   = Interface.DerivedProperty("float")
    CppType                                 = Interface.DerivedProperty("std::float_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class DoubleTypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("double")
    CType                                   = Interface.DerivedProperty("double")
    CppType                                 = Interface.DerivedProperty("std::double_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class BoolTypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("bool")
    CType                                   = Interface.DerivedProperty("bool")
    CppType                                 = Interface.DerivedProperty("bool")
