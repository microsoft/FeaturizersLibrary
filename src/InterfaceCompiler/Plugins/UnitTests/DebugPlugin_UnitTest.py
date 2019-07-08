# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for DebugPlugin.py"""

import os
import sys
import textwrap
import unittest
import unittest.mock

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from DebugPlugin import Plugin

# ----------------------------------------------------------------------
class StandardSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def setUp(self):
        self.maxDiff = None

    # ----------------------------------------------------------------------
    def test_Properties(self):
        self.assertEqual(Plugin.Name, "Debug")
        self.assertEqual(
            Plugin.Description,
            "Plugin that displays debug information and nothing else",
        )

    # ----------------------------------------------------------------------
    def test_GetRequiredMetadataNames(self):
        self.assertEqual(Plugin.GetRequiredMetadataNames(), [])

    # ----------------------------------------------------------------------
    def test_GenerateOutputFilenames(self):
        self.assertEqual(
            list(Plugin.GenerateOutputFilenames({"output_name": "an_output_name"})),
            ["an_output_name.txt"],
        )

    # ----------------------------------------------------------------------
    def test_Execute(self):
        with unittest.mock.patch("DebugPlugin.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            status_stream_mock = unittest.mock.MagicMock()
            verbose_stream_mock = unittest.mock.MagicMock()

            result = Plugin.Execute(
                invoke_reason="An interesting invoke reason",
                context={
                    "output_filenames": ["an_output_name.txt"],
                    "value1": "one",
                    "value2": "two",
                },
                status_stream=status_stream_mock,
                verbose_stream=verbose_stream_mock,
                verbose=False,
            )
            sink = sink.getvalue()

            self.assertEqual(result, None)

            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    # ----------------------------------------------------------------------
                    # |
                    # |  Debug Output - Execute
                    # |
                    # ----------------------------------------------------------------------
                    invoke_reason:
                        An interesting invoke reason

                    context:
                        output_filenames : 0)   an_output_name.txt
                        value1           : one
                        value2           : two

                    """,
                ),
            )

            self.assertEqual(len(status_stream_mock.method_calls), 2)
            self.assertEqual(status_stream_mock.method_calls[0][0], "write")
            self.assertEqual(
                status_stream_mock.method_calls[0][1][0],
                "Writing 'an_output_name.txt'...",
            )
            self.assertEqual(status_stream_mock.method_calls[1][0], "DoneManager")
            self.assertTrue(not status_stream_mock.method_calls[1][1])

            self.assertTrue(not verbose_stream_mock.mock_calls)


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(
            unittest.main(
                verbosity=2,
            ),
        )
    except KeyboardInterrupt:
        pass
