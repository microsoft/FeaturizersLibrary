# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for CreateCsFile.py"""

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
    from MlNetPluginImpl import CreateCsFile

# ----------------------------------------------------------------------
class StandardSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def test_Standard(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCsFile.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            result = CreateCsFile.CreateCsFile("ignored", None, lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    // The file header!
                    // TODO: Append more output here
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
