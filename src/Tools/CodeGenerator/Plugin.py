# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin and TypeVisitor objects"""

import os
import re

import CommonEnvironment
from CommonEnvironment import Interface

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class Plugin(Interface.Interface):
    """Abstract base class for Plugins"""

    # ----------------------------------------------------------------------
    # |
    # |  Properties
    # |
    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def Name(self):
        """Name of the plugin - this must be unique across all plugins"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def Description(self):
        """Short description of the plugin"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    # |
    # |  Methods
    # |
    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def IsValidEnvironment():
        """Returns a error string if the current environment is not valid to execute the plugin"""

        # This default behavior indicates that the Plugin is valid in all environments
        return None

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def Generate(data, output_dir, status_stream):
        """Generates content based on the provided data. Returns a result code."""
        raise Exception("Abstract method")

# ----------------------------------------------------------------------
class TypeVisitor(Interface.Interface):
    """Visitor for types supported by the Featurization library"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    _Accept_Regex                           = None

    @classmethod
    def Accept(
        cls,
        type_string,
        *args,
        supported_custom_types=None,
        **kwargs
    ):
        simple_type_map = {
            "int8_t": cls.OnInt8,
            "int16_t": cls.OnInt16,
            "int32_t": cls.OnInt32,
            "int64_t": cls.OnInt64,
            "uint8_t": cls.OnUInt8,
            "uint16_t": cls.OnUInt16,
            "uint32_t": cls.OnUInt32,
            "uint64_t": cls.OnUInt64,
            "float32_t": cls.OnFloat32,
            "float_t": cls.OnFloat32,
            "double_t": cls.OnFloat64,
            "bool": cls.OnBool,
            "string": cls.OnString,
        }

        search_string = type_string.replace("std::", "")

        func = simple_type_map.get(search_string, None)
        if func is not None:
            return func(type_string, *args, **kwargs)

        if cls._Accept_Regex is None:
            cls._Accept_Regex = re.compile(r"^(?P<type>\S+)<(?P<template>.+)>$")

        match = cls._Accept_Regex.match(search_string)
        if not match:
            if supported_custom_types and search_string in supported_custom_types:
                return cls.OnCustomType(type_string, *args, **kwargs)

            raise Exception("'{}' is not a supported type".format(type_string))

        template_type_map = {
            # "<type_name>": (<func>, <expected_num_template_args>)
            "vector": (cls.OnVector, 1),
            "array": (cls.OnArray, 2),
            "map": (cls.OnMap, 2),
        }

        template_type = match.group("type")

        container_info = template_type_map.get(template_type, None)
        if container_info is None:
            raise Exception("'{}' is not a supported container type".format(type_string))

        func, expected_num_template_args = container_info

        template_args = cls._GetTemplateArgs(match.group("template"))
        if len(template_args) != expected_num_template_args:
            raise Exception("'{}' was expected to have {} template arg(s)".format(type_string, expected_num_template_args))

        return func(template_args, *args, **kwargs)

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnInt8(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnInt16(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnInt32(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnInt64(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnUInt8(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnUInt16(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnUInt32(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnUInt64(*args, **kwargs):
        raise Exception("Abstract method")

    # TODO: float16

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnFloat32(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnFloat64(*args, **kwargs):
        raise Exception("Abstract method")

    # TODO: complex64
    # TODO: complex128
    # TODO: bfloat16

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnBool(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnString(*args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnArray(template_args, *args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnVector(template_args, *args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def OnMap(template_args, *args, **kwargs):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def OnCustomType(type, *args, **kwargs):
        raise Exception("Abstract method")

    # TODO: Tensor

    # ----------------------------------------------------------------------
    # ----------------------------------------------------------------------
    # ----------------------------------------------------------------------
    @staticmethod
    def _GetTemplateArgs(template):
        # Get the template args delimited by comma. Take into account nested pairing tokens.
        bracket_count = 0
        brace_count = 0
        paren_count = 0
        template_count = 0

        template_args = []
        prev_index = 0

        for index, char in enumerate(template):
            if char == "[":
                bracket_count += 1
            elif char == "]":
                assert bracket_count
                bracket_count -= 1
            elif char == "{":
                brace_count += 1
            elif char == "}":
                assert brace_count
                brace_count -= 1
            elif char == "(":
                paren_count += 1
            elif char == ")":
                assert paren_count
                paren_count -= 1
            elif char == "<":
                template_count += 1
            elif char == ">":
                assert template_count
                template_count -= 1
            elif char == ",":
                if bracket_count or brace_count or paren_count or template_count:
                    continue

                template_args.append(template[prev_index : index].strip())
                prev_index = index + 1

        if prev_index < len(template):
            template_args.append(template[prev_index:])

        return template_args
