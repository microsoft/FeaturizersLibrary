# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for CreateCsInstructions.py"""

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

sys.path.insert(0, os.path.join(_script_dir, "..", ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from MlNetPluginImpl import CreateCsInstructions

# ----------------------------------------------------------------------
class StandardSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def setUp(self):
        self.maxDiff = None

    # ----------------------------------------------------------------------
    def test_Standard(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCsInstructions.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            result = CreateCsInstructions.CreateCsInstructions(
                "TestOutputFilename",
                "TestOutputName",
                "TestOutputDir",
                lambda prefix: "{}The file header!\n".format(prefix),
            )
            sink = sink.getvalue()

            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    # The file header!

                    # This is a temporary solution; longer-term, we will generate scripts that invoke the
                    # commands below; there will be a batch file script for Windows and a bash script for
                    # Ubuntu.

                    # This command should be run from:
                    #
                    #       "TestOutputDir"
                    #

                    csc -target:library -out:TestOutputNameMlNet.dll *.cs -reference:Microsoft.ML.Core.dll -reference:Microsoft.ML.Data.dll -reference:Microsoft.ML.DataView.dll -reference:netstandard.dll
                    """,
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
