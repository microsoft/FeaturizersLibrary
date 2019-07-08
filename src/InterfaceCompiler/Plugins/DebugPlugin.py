# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

import os
import textwrap
import sys

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import Interface
from CommonEnvironment import StringHelpers

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from Plugin import PluginBase           # <unable to import> pylint: disable = E0401

# ----------------------------------------------------------------------
@Interface.staticderived
class Plugin(PluginBase):
    # ----------------------------------------------------------------------
    # |  Properties
    Name                                    = Interface.DerivedProperty("Debug")
    Description                             = Interface.DerivedProperty(
        "Plugin that displays debug information and nothing else",
    )

    # ----------------------------------------------------------------------
    # |  Methods
    @staticmethod
    @Interface.override
    def GetRequiredMetadataNames():
        return []

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def GenerateOutputFilenames(context):
        assert "output_name" in context

        yield "{}.txt".format(context["output_name"])

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def Execute(invoke_reason, context, status_stream, verbose_stream, verbose): # <unused argument> pylint: disable = W0613
        assert len(context["output_filenames"]) == 1, context["output_filenames"]
        output_filename = context["output_filenames"][0]

        status_stream.write("Writing '{}'...".format(output_filename))
        with status_stream.DoneManager():
            sink = six.StringIO()
            CommonEnvironment.Describe(
                context,
                output_stream=sink,
            )
            sink = sink.getvalue()

            with open(output_filename, "w") as f:
                f.write(
                    textwrap.dedent(
                        """\
                        # ----------------------------------------------------------------------
                        # |
                        # |  Debug Output - Execute
                        # |
                        # ----------------------------------------------------------------------
                        invoke_reason:
                            {invoke_reason}

                        context:
                            {context}

                        """,
                    ).format(
                        invoke_reason=invoke_reason,
                        context=StringHelpers.LeftJustify(sink.strip(), 4),
                    ),
                )
