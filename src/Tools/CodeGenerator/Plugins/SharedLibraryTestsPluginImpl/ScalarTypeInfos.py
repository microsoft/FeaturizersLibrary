# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the scalar type info objects"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

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
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        if self.IsOptional:
            return "Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<{cpp_type}>::nullable_type>::IsNull({input_name}) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<{cpp_type}>::nullable_type>::GetNullableValue({input_name})".format(
                cpp_type=self.CppType,
                input_name=input_name,
            )

        return input_name

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            self.CppType,
            "{} {};".format(self.CppType, result_name),
            "&{}".format(result_name),
            textwrap.dedent(
                """\
                #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
                results.push_back(std::move({result}));
                #else
                results.emplace_back(std::move({result}));
                #endif
                """,
            ).format(
                result=result_name,
            ),
        )


# ----------------------------------------------------------------------
@Interface.staticderived
class Int8TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int8")
    CppType                                 = Interface.DerivedProperty("std::int8_t")
    CType                                   = Interface.DerivedProperty("int8_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int16TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int16")
    CppType                                 = Interface.DerivedProperty("std::int16_t")
    CType                                   = Interface.DerivedProperty("int16_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int32TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int32")
    CppType                                 = Interface.DerivedProperty("std::int32_t")
    CType                                   = Interface.DerivedProperty("int32_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int64TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int64")
    CppType                                 = Interface.DerivedProperty("std::int64_t")
    CType                                   = Interface.DerivedProperty("int64_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt8TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint8")
    CppType                                 = Interface.DerivedProperty("std::uint8_t")
    CType                                   = Interface.DerivedProperty("uint8_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt16TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint16")
    CppType                                 = Interface.DerivedProperty("std::uint16_t")
    CType                                   = Interface.DerivedProperty("uint16_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt32TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint32")
    CppType                                 = Interface.DerivedProperty("std::uint32_t")
    CType                                   = Interface.DerivedProperty("uint32_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt64TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint64")
    CppType                                 = Interface.DerivedProperty("std::uint64_t")
    CType                                   = Interface.DerivedProperty("uint64_t")


# ----------------------------------------------------------------------
@Interface.staticderived
class FloatTypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("float")
    CppType                                 = Interface.DerivedProperty("std::float_t")
    CType                                   = Interface.DerivedProperty("float")


# ----------------------------------------------------------------------
@Interface.staticderived
class DoubleTypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("double")
    CppType                                 = Interface.DerivedProperty("std::double_t")
    CType                                   = Interface.DerivedProperty("double")


# ----------------------------------------------------------------------
@Interface.staticderived
class BoolTypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("bool")
    CppType                                 = Interface.DerivedProperty("bool")
    CType                                   = Interface.DerivedProperty("bool")
