# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Invokes the CodeGenerator to build code used during Featurization"""

import os
import sys

import CommonEnvironment
from CommonEnvironment import BuildImpl
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment import Process
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

_PLUGINS                                    = [
    (
        "SharedLibrary",
        os.path.join(_script_dir, "..", "..", "SharedLibrary", "GeneratedCode"),
    ),
    (
        "SharedLibraryTests",
        os.path.join(_script_dir, "..", "..", "SharedLibrary", "IntegrationTests", "GeneratedCode"),
    ),
]


# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    output_stream=None,
)
def Build(
    output_stream=sys.stdout,
):
    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        command_line_template = 'python "{script}" {{plugin}} "{input}" "{{output}}"'.format(
            script=_script_dir,
            input=os.path.join(_script_dir, "Featurizers.json"),
        )

        for index, (plugin, output_dir) in enumerate(_PLUGINS):
            dm.stream.write(
                "Generating '{}' ({} of {})...".format(plugin, index + 1, len(_PLUGINS)),
            )
            with dm.stream.DoneManager(
                suffix="\n",
            ) as this_dm:
                this_dm.result = Process.Execute(
                    command_line_template.format(
                        plugin=plugin,
                        output=output_dir,
                    ),
                    this_dm.stream,
                )

        if dm.result != 0:
            return dm.result

        return dm.result


# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    output_stream=None,
)
def Clean(
    output_stream=sys.stdout,
):
    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        for index, (plugin, output_dir) in enumerate(_PLUGINS):
            output_dir = os.path.realpath(output_dir)

            dm.stream.write(
                "Processing '{}' ({} of {})...".format(plugin, index + 1, len(_PLUGINS)),
            )
            with dm.stream.DoneManager() as this_dm:
                if not os.path.isdir(output_dir):
                    this_dm.stream.write("'{}' does not exist.\n".format(output_dir))
                    continue

                this_dm.stream.write("Removing '{}'...".format(output_dir))
                with this_dm.stream.DoneManager():
                    FileSystem.RemoveTree(output_dir)

    return dm.result


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(
            BuildImpl.Main(
                BuildImpl.Configuration(
                    "CodeGenerator",
                    requires_output_dir=False,
                ),
            ),
        )
    except KeyboardInterrupt:
        pass
