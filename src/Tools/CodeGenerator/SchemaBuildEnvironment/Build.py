# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

"""Builds generated code"""

import os
import sys

import CommonEnvironment
from CommonEnvironment import BuildImpl
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment import Process
from CommonEnvironment.Shell.All import CurrentShell
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    output_stream=None,
)
def Build(
    force=False,
    output_stream=sys.stdout,
    verbose=False,
):
    return Process.Execute(
        '"{script}" Generate PythonYaml Featurizers "{output_dir}" "/input={input}" /plugin_arg=no_serialization:true{force}{verbose}'.format(
            script=CurrentShell.CreateScriptName("SimpleSchemaGenerator"),
            output_dir=os.path.join(_script_dir, "..", "GeneratedCode"),
            input=os.path.join(_script_dir, "..", "Featurizers.SimpleSchema"),
            force=" /force" if force else "",
            verbose=" /verbose" if verbose else "",
        ),
        output_stream,
    )


# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    output_stream=None,
)
def Clean(
    output_stream=sys.stdout,
):
    output_dir = os.path.join(_script_dir, "..", "GeneratedCode")
    if not os.path.isdir(output_dir):
        output_stream.write("'{}' does not exist.\n".format(output_dir))
    else:
        filenames = [
            "Compiler.ConditionalInvocationQueryMixin.data",
            "Featurizers_PythonJsonSerialization.py",
        ]

        output_stream.write("Removing content in '{}'...".format(output_dir))
        with StreamDecorator(output_stream).DoneManager():
            for filename in filenames:
                filename = os.path.join(output_dir, filename)
                FileSystem.RemoveFile(filename)

    return 0


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(
            BuildImpl.Main(
                BuildImpl.Configuration(
                    "SchemaCodeGenerator",
                    requires_output_dir=False,
                ),
            ),
        )
    except KeyboardInterrupt:
        pass
