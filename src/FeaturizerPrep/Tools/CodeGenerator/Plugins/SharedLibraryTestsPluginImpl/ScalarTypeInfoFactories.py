# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the scalar type info objects"""

import os

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfoFactory import TypeInfoFactory

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class _ScalarTypeInfoFactory(TypeInfoFactory):
    """Functionality common to all scalars"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def CppType(self):
        """C++ type"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        if is_input_optional:
            return "Microsoft::Featurizer::Traits<{cpp_type}>::IsNull({input_name}) ? nullptr : &Microsoft::Featurizer::Traits<{cpp_type}>::GetNullableValue({input_name})".format(
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
            "results.emplace_back(std::move({}));".format(result_name),
        )

# ----------------------------------------------------------------------
@Interface.staticderived
class Int8TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::int8_t")
    CppType                                 = Interface.DerivedProperty("int8_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class Int16TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::int16_t")
    CppType                                 = Interface.DerivedProperty("int16_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class Int32TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::int32_t")
    CppType                                 = Interface.DerivedProperty("int32_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class Int64TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::int64_t")
    CppType                                 = Interface.DerivedProperty("int64_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class UInt8TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::uint8_t")
    CppType                                 = Interface.DerivedProperty("uint8_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class UInt16TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::uint16_t")
    CppType                                 = Interface.DerivedProperty("uint16_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class UInt32TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::uint32_t")
    CppType                                 = Interface.DerivedProperty("uint32_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class UInt64TypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::uint64_t")
    CppType                                 = Interface.DerivedProperty("uint64_t")

# ----------------------------------------------------------------------
@Interface.staticderived
class FloatTypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::float_t")
    CppType                                 = Interface.DerivedProperty("float")

# ----------------------------------------------------------------------
@Interface.staticderived
class DoubleTypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("std::double_t")
    CppType                                 = Interface.DerivedProperty("double")

# ----------------------------------------------------------------------
@Interface.staticderived
class BoolTypeInfoFactory(_ScalarTypeInfoFactory):
    TypeName                                = Interface.DerivedProperty("bool")
    CppType                                 = Interface.DerivedProperty("bool")
