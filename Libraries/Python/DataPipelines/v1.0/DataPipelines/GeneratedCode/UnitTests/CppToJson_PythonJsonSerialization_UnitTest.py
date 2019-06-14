# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for CppToJson_PythonJsonSerialization.py"""

import os
import sys
import unittest

import CommonEnvironment
from DataPipelines.GeneratedCode.CppToJson_PythonJsonSerialization import *

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class TestSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def test_Empty(self):
        self.assertEqual(Deserialize([]), [])

    # ----------------------------------------------------------------------
    def test_NoArgs(self):
        result = Deserialize(
            [
                {
                    "func_name": "Name",
                    "raw_return_type": "int1",
                    "simple_return_type": "int2",
                },
            ],
        )

        self.assertEqual(len(result), 1)
        self.assertEqual(result[0].func_name, "Name")
        self.assertEqual(result[0].raw_return_type, "int1")
        self.assertEqual(result[0].simple_return_type, "int2")
        self.assertTrue(not hasattr(result[0], "var_names"))
        self.assertTrue(not hasattr(result[0], "raw_var_types"))
        self.assertTrue(not hasattr(result[0], "simple_var_types"))
        self.assertTrue(not hasattr(result[0], "declaration_line"))
        self.assertTrue(not hasattr(result[0], "definition_line"))

    # ----------------------------------------------------------------------
    def test_WithArgs(self):
        result = Deserialize(
            [
                {
                    "func_name": "Name",
                    "raw_return_type": "int1",
                    "simple_return_type": "int2",
                    "var_names": ["a", "b",],
                    "raw_var_types": ["c", "d",],
                    "simple_var_types": ["e", "f",],
                    "declaration_line": 3,
                    "definition_line": 7,
                },
            ],
        )

        self.assertEqual(len(result), 1)
        self.assertEqual(result[0].func_name, "Name")
        self.assertEqual(result[0].raw_return_type, "int1")
        self.assertEqual(result[0].simple_return_type, "int2")
        self.assertEqual(result[0].var_names, ["a", "b",])
        self.assertEqual(result[0].raw_var_types, ["c", "d",])
        self.assertEqual(result[0].simple_var_types, ["e", "f",])
        self.assertEqual(result[0].declaration_line, 3)
        self.assertEqual(result[0].definition_line, 7)

    # ----------------------------------------------------------------------
    def test_Multiple(self):
        result = Deserialize(
            [
                {
                    "func_name": "Name1",
                    "raw_return_type": "int1",
                    "simple_return_type": "int2",
                    "definition_line": 12,
                },
                {
                    "func_name": "Name2",
                    "raw_return_type": "int3",
                    "simple_return_type": "int4",
                    "definition_line": 34,
                },
            ],
        )

        self.assertEqual(len(result), 2)

        self.assertEqual(result[0].func_name, "Name1")
        self.assertEqual(result[0].raw_return_type, "int1")
        self.assertEqual(result[0].simple_return_type, "int2")
        self.assertEqual(result[0].definition_line, 12)
        self.assertTrue(not hasattr(result[0], "var_names"))
        self.assertTrue(not hasattr(result[0], "raw_var_types"))
        self.assertTrue(not hasattr(result[0], "simple_var_types"))
        self.assertTrue(not hasattr(result[0], "declaration_line"))

        self.assertEqual(result[1].func_name, "Name2")
        self.assertEqual(result[1].raw_return_type, "int3")
        self.assertEqual(result[1].simple_return_type, "int4")
        self.assertEqual(result[1].definition_line, 34)
        self.assertTrue(not hasattr(result[1], "var_names"))
        self.assertTrue(not hasattr(result[1], "raw_var_types"))
        self.assertTrue(not hasattr(result[1], "simple_var_types"))
        self.assertTrue(not hasattr(result[1], "declaration_line"))

    # ----------------------------------------------------------------------
    def test_InvalidName(self):
        self.assertRaisesRegex(
            Exception,
            "An item was expected",
            lambda: Deserialize(
                [
                    {
                        "func_name": None,
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                    },
                ],
            ),
        )

        self.assertRaisesRegex(
            Exception,
            "'' is not a valid 'String' string - Value must have at least 1 character",
            lambda: Deserialize(
                [
                    {
                        "func_name": "",
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                    },
                ],
            ),
        )

    # ----------------------------------------------------------------------
    def test_InvalidRawReturnType(self):
        self.assertRaisesRegex(
            Exception,
            "An item was expected",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": None,
                        "simple_return_type": "int2",
                    },
                ],
            ),
        )

        self.assertRaisesRegex(
            Exception,
            "'' is not a valid 'String' string - Value must have at least 1 character",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "",
                        "simple_return_type": "int2",
                    },
                ],
            ),
        )

    # ----------------------------------------------------------------------
    def test_InvalidSimpleReturnType(self):
        self.assertRaisesRegex(
            Exception,
            "An item was expected",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": None,
                    },
                ],
            ),
        )

        self.assertRaisesRegex(
            Exception,
            "'' is not a valid 'String' string - Value must have at least 1 character",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "",
                    },
                ],
            ),
        )

    # ----------------------------------------------------------------------
    def test_InvalidVarName(self):
        self.assertRaisesRegex(
            Exception,
            "expected string or bytes-like object", # TODO
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                        "var_names": [None, "b",],
                        "raw_var_types": ["c", "d",],
                        "simple_var_types": ["e", "f",],
                    },
                ],
            ),
        )

        self.assertRaisesRegex(
            Exception,
            "'' is not a valid 'String' string - Value must have at least 1 character",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                        "var_names": ["", "b",],
                        "raw_var_types": ["c", "d",],
                        "simple_var_types": ["e", "f",],
                    },
                ],
            ),
        )

    # ----------------------------------------------------------------------
    def test_InvalidRawVarType(self):
        self.assertRaisesRegex(
            Exception,
            "expected string or bytes-like object", # TODO
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                        "var_names": ["a", "b",],
                        "raw_var_types": ["c", None,],
                        "simple_var_types": ["e", "f",],
                    },
                ],
            ),
        )

        self.assertRaisesRegex(
            Exception,
            "'' is not a valid 'String' string - Value must have at least 1 character",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                        "var_names": ["a", "b",],
                        "raw_var_types": ["c", "",],
                        "simple_var_types": ["e", "f",],
                    },
                ],
            ),
        )

    # ----------------------------------------------------------------------
    def test_InvalidSimpleVarType(self):
        self.assertRaisesRegex(
            Exception,
            "expected string or bytes-like object", # TODO
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                        "var_names": ["a", "b",],
                        "raw_var_types": ["c", "d",],
                        "simple_var_types": ["e", None, "g",],
                    },
                ],
            ),
        )

        self.assertRaisesRegex(
            Exception,
            "'' is not a valid 'String' string - Value must have at least 1 character",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int2",
                        "var_names": ["", "b",],
                        "raw_var_types": ["c", "d",],
                        "simple_var_types": ["e", "", "g",],
                    },
                ],
            ),
        )
     # ----------------------------------------------------------------------
    def test_InvalidDeclarationLine(self):
        self.assertRaisesRegex(
            Exception,
            "0 is not >= 1",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int1",
                        "declaration_line": 0,
                    },
                ],
            ),
        )
        self.assertRaisesRegex(
            Exception,
            "'String' is not a valid 'Integer' string - Value must be >= 1",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int1",
                        "declaration_line": "String",
                    },
                ],
            ),
        )
     # ----------------------------------------------------------------------
    def test_InvalidDefinitionLine(self):
        self.assertRaisesRegex(
            Exception,
            "0 is not >= 1",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int1",
                        "definition_line": 0,
                    },
                ],
            ),
        )
        self.assertRaisesRegex(
            Exception,
            "'String' is not a valid 'Integer' string - Value must be >= 1",
            lambda: Deserialize(
                [
                    {
                        "func_name": "Name",
                        "raw_return_type": "int1",
                        "simple_return_type": "int1",
                        "definition_line": "String",
                    },
                ],
            ),
        )

    # ----------------------------------------------------------------------
    def test_ProcessAdditionalData(self):
        input = [
            {
                "func_name": "Name",
                "raw_return_type": "int1",
                "simple_return_type": "int2",
                "another_value": {"hello": "world",},
                "another_value2": "a string",
                "optional_list": [1, 2, 3],
            },
        ]

        result = Deserialize(input)

        self.assertEqual(len(result), 1)
        self.assertTrue(not hasattr(result[0], "another_value"))

        result = Deserialize(
            input,
            process_additional_data=True,
        )

        self.assertEqual(len(result), 1)
        self.assertEqual(result[0].another_value.hello, "world")
        self.assertEqual(result[0].another_value2, "a string")
        self.assertEqual(result[0].optional_list, [1, 2, 3,])

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(unittest.main(verbosity=2))
    except KeyboardInterrupt:
        pass
