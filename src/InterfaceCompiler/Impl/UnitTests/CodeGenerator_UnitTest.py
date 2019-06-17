# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for CodeGenerator.py"""

import os
import sys
import unittest
import unittest.mock

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from CodeGenerator import *

# ----------------------------------------------------------------------
class StandardTests(unittest.TestCase):
    # ----------------------------------------------------------------------
    def setUp(self):
        self._mock = unittest.mock.Mock()
        self._code_generator = CreateCodeGenerator(self._mock)

    # ----------------------------------------------------------------------
    def test_Properties(self):
        self.assertEqual(self._code_generator.Name, "Interface Compiler")
        self.assertTrue("Extracts C++ methods" in self._code_generator.Description)
        self.assertTrue("FilenameTypeInfo" in str(self._code_generator.InputTypeInfo))

    # ----------------------------------------------------------------------
    def test_GetRequiredMetdataNames(self):
        result = self._code_generator._GetRequiredMetadataNames()

        self.assertTrue("plugin_name" in result)
        self.assertTrue("output_name" in result)

    # ----------------------------------------------------------------------
    def test_GetOptionalMetadata(self):
        result = self._code_generator._GetOptionalMetadata()
        result_names = [r[0] for r in result]

        self.assertTrue("plugin_settings" in result_names)

    # ----------------------------------------------------------------------
    def test_GetAdditionalGeneratorItems(self):
        self._mock.GetAdditionalGeneratorFilenames.return_value = []
        self._code_generator._GetAdditionalGeneratorItems(None)

        self.assertTrue(self._mock.GetAdditionalGeneratorFilenames.called)

    # ----------------------------------------------------------------------
    def test_InvokeImpl(self):
        self._code_generator._InvokeImpl(None, None, None, None, None)
        self.assertTrue(self._mock.Execute.called)

# ----------------------------------------------------------------------
class CreateContextTests(unittest.TestCase):
    # ----------------------------------------------------------------------
    def setUp(self):
        mock = unittest.mock.Mock()
        mock.GenerateCustomMetadataSettingsAndDefaults.return_value = []
        mock.GetRequiredMetadataNames.return_value = []
        mock.GenerateOutputFilenames.return_value = []
        mock.PreprocessMetadata = lambda metadata: metadata
        mock.PreprocessContext = lambda context: context
        mock.PostprocessContext = lambda context: context

        self._mock = mock
        self._code_generator = CreateCodeGenerator(self._mock)

    # ----------------------------------------------------------------------
    def test_InvlidPluginSettings(self):
        self.assertRaisesRegex(
            Exception,
            "'Invalid Value' is not a valid plugin setting",
            lambda: self._code_generator._CreateContext(
                {
                    "plugin_settings": {
                        "Invalid Value": True,
                    },
                },
            ),
        )

    # ----------------------------------------------------------------------
    def test_ValidPluginSettings(self):
        self._mock.GenerateCustomMetadataSettingsAndDefaults.return_value = [("Custom", True)]

        result = self._code_generator._CreateContext(
            {
                "output_dir": os.getcwd(),
                "plugin_settings": {
                    "Custom": "False",
                },
            },
        )

        self.assertEqual(result["plugin_settings"]["Custom"], False)

    # ----------------------------------------------------------------------
    def test_RequiredError(self):
        self._mock.GetRequiredMetadataNames.return_value = ["This Does Not Exist"]

        self.assertRaisesRegex(
            Exception,
            "'This Does Not Exist' is required but was not found",
            lambda: self._code_generator._CreateContext(
                {
                    "plugin_settings": {},
                },
            ),
        )

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(unittest.main(verbosity=2))
    except KeyboardInterrupt:
        pass
