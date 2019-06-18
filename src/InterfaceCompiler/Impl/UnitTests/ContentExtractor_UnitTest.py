# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for ContentExtractor.py"""

import os
import re
import sys
import textwrap
import unittest
import unittest.mock

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from ContentExtractor import *

# ----------------------------------------------------------------------
class StandardTests(unittest.TestCase):
    # ----------------------------------------------------------------------
    def test_Standard(self):
        with unittest.mock.patch("ContentExtractor.ObtainFunctions") as mocked:
            mocked.side_effect = lambda filename, *args, **kwargs: {filename: filename}

            sink = six.moves.StringIO()

            results = ExtractContent(["one.cpp", "two.cpp"], StreamDecorator(sink))
            sink = sink.getvalue()

            self.assertEqual(len(mocked.call_args_list), 2)
            self.assertEqual(mocked.call_args_list[0][0][0], "one.cpp")
            self.assertEqual(mocked.call_args_list[1][0][0], "two.cpp")

            self.assertEqual(len(results), 2)
            self.assertTrue("one.cpp" in results)
            self.assertEqual(results["one.cpp"], "one.cpp")
            self.assertTrue("two.cpp" in results)
            self.assertEqual(results["two.cpp"], "two.cpp")

            # Match by regex as times won't always be the same
            self.assertTrue(
                re.match(
                    textwrap.dedent(
                        r"""(?#\
                        Line 1)Processing input files\.\.\.\n(?#
                        Line 2)  'one\.cpp' \(1 of 2\)\.\.\.DONE! \(0, .+?\)\n(?#
                        Line 3)  'two\.cpp' \(2 of 2\)\.\.\.DONE! \(0, .+?\)\n(?#
                        Line 4)DONE! \(0, .+?\)\n(?#
                        Line 5)""",
                    ),
                    sink,
                ),
            )

    # ----------------------------------------------------------------------
    def test_Unsupported(self):
        # ----------------------------------------------------------------------
        def MyObtainFunctions(input_filename, on_unsupported_func, *args, **kwargs):
            on_unsupported_func("A test message", input_filename, 123)
            return {input_filename: input_filename}

        # ----------------------------------------------------------------------

        with unittest.mock.patch(
            "ContentExtractor.ObtainFunctions", side_effect=MyObtainFunctions,
        ) as mocked:
            sink = six.moves.StringIO()

            results = ExtractContent(["one.cpp", "two.cpp"], StreamDecorator(sink))
            sink = sink.getvalue()

            self.assertEqual(len(results), 2)
            self.assertTrue("one.cpp" in results)
            self.assertEqual(results["one.cpp"], "one.cpp")
            self.assertTrue("two.cpp" in results)
            self.assertEqual(results["two.cpp"], "two.cpp")

            # Match by regex as times won't always be the same
            self.assertTrue(
                re.match(
                    textwrap.dedent(
                        r"""(?#\
                        Line 1)Processing input files\.\.\.\n(?#
                        Line 2)  'one\.cpp' \(1 of 2\)\.\.\.\n(?#
                        Line 3)    A test message \(one\.cpp <123>\)DONE! \(0, .+?\)\n(?#
                        Line 4)  'two\.cpp' \(2 of 2\)\.\.\.\n(?#
                        Line 5)    A test message \(two\.cpp <123>\)DONE! \(0, .+?\)\n(?#
                        Line 6)DONE! \(0, .+?\)\n(?#
                        Line 7)""",
                    ),
                    sink,
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
