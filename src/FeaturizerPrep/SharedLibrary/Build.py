# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Builds the Shared Library"""

import os
import shutil
import sys

import six

import CommonEnvironment
from CommonEnvironment import BuildImpl
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment import Process
from CommonEnvironment.Shell.All import CurrentShell
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

CONFIGURATIONS                              = ["Debug", "Release"]

# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    configuration=CommandLine.EnumTypeInfo(CONFIGURATIONS),
    output_dir=CommandLine.DirectoryTypeInfo(
        ensure_exists=False,
    ),
    output_stream=None,
)
def Build(
    configuration,
    output_dir,
    keep_temp_dir=False,
    cmake_generator="Ninja",
    output_stream=sys.stdout,
    verbose=False,
):
    """Builds the Featurizer Shared Library"""

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        temp_directory = CurrentShell.CreateTempDirectory()

        # ----------------------------------------------------------------------
        def CleanupTempDir():
            if keep_temp_dir:
                dm.stream.write(
                    "\nCMake output has been written to '{}'.\n".format(temp_directory),
                )
                return

            FileSystem.RemoveTree(temp_directory)

        # ----------------------------------------------------------------------

        with CallOnExit(CleanupTempDir):
            prev_dir = os.getcwd()
            os.chdir(temp_directory)

            with CallOnExit(lambda: os.chdir(prev_dir)):
                activities = [
                    (
                        "Generating cmake Files",
                        'cmake -G "{generator}" -DCMAKE_BUILD_TYPE={configuration} "{this_dir}"'.format(
                            generator=cmake_generator,
                            temp_dir=temp_directory,
                            configuration=configuration,
                            this_dir=_script_dir,
                        ),
                    ),
                    ("Building", "cmake --build ."),
                    ("Copying Binaries", _CopyBinaries),
                    ("Copying Data", _CopyData),
                    ("Copying Headers", _CopyHeaders),
                ]

                for index, (activity, command_line) in enumerate(activities):
                    dm.stream.write(
                        "{} ({} of {})...".format(activity, index + 1, len(activities)),
                    )
                    with dm.stream.DoneManager(
                        suffix="\n" if verbose else None,
                    ) as this_dm:
                        sink = six.moves.StringIO()

                        output_streams = [sink]

                        if verbose:
                            output_streams.append(
                                StreamDecorator(
                                    this_dm.stream,
                                    line_prefix="INFO: ",
                                ),
                            )

                        this_output_stream = StreamDecorator(output_streams)

                        if callable(command_line):
                            this_dm.result = command_line(
                                temp_directory,
                                output_dir,
                                this_output_stream,
                            )
                        else:
                            this_dm.result = Process.Execute(
                                command_line,
                                this_output_stream,
                            )

                        if this_dm.result != 0:
                            if not verbose:
                                this_dm.stream.write(sink.getvalue())

                            return this_dm.result

        return dm.result


# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    configuration=CommandLine.EnumTypeInfo(CONFIGURATIONS),
    output_dir=CommandLine.DirectoryTypeInfo(),
    output_stream=None,
)
def Clean(
    configuration,
    output_dir,
    output_stream=sys.stdout,
):
    """Cleans previously built content"""

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        if not os.path.isdir(output_dir):
            dm.stream.write("\nNothing to clean.\n")
        else:
            dm.stream.write("Removing '{}'...".format(output_dir))
            with dm.stream.DoneManager():
                FileSystem.RemoveTree(output_dir)

        return dm.result


# ----------------------------------------------------------------------
@CommandLine.EntryPoint(
    # TODO
)
@CommandLine.Constraints(
    windows_build_dir=CommandLine.DirectoryTypeInfo(),
    linux_build_dir=CommandLine.DirectoryTypeInfo(),
    output_dir=CommandLine.DirectoryTypeInfo(
        ensure_exists=False,
    ),
    output_stream=None,
)
def Package(
    windows_build_dir,
    linux_build_dir,
    output_dir,
    output_stream=sys.stdout,
    verbose=False,
):
    """Packages previously built content"""

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:

        # TODO: Implement this

        return dm.result

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def _CopyBinaries(temp_directory, output_dir, output_stream):
    if CurrentShell.CategoryName == "Windows":
        output_files = ["Featurizers.dll", "Featurizers.pdb"]
    elif CurrentShell.CategoryName == "Linux":
        output_files = []

        for item in os.listdir(temp_directory):
            if item.startswith("libFeaturizers.so"):
                output_files.append(item)
    else:
        raise Exception("The Current Shell is not supported")

    for index, output_file in enumerate(output_files):
        output_stream.write(
            "Copying '{}' ({} of {})...".format(output_file, index + 1, len(output_files)),
        )
        with output_stream.DoneManager():
            shutil.copyfile(
                os.path.join(temp_directory, output_file),
                os.path.join(output_dir, output_file),
            )

    return 0


# ----------------------------------------------------------------------
def _CopyData(temp_directory, output_dir, output_stream):
    output_dir = os.path.join(output_dir, "Data")

    FileSystem.RemoveTree(output_dir)

    FileSystem.CopyTree(
        os.path.join(temp_directory, "Data"),
        output_dir,
    )

    return 0


# ----------------------------------------------------------------------
def _CopyHeaders(temp_directory, output_dir, output_stream):
    output_files = list(
        FileSystem.WalkFiles(
            os.path.join(_script_dir, "GeneratedCode"),
            include_file_extensions=[".h"],
        ),
    )

    for index, output_file in enumerate(output_files):
        output_stream.write(
            "Copying '{}' ({} of {})...".format(output_file, index + 1, len(output_files)),
        )
        with output_stream.DoneManager():
            shutil.copyfile(
                output_file,
                os.path.join(output_dir, os.path.basename(output_file)),
            )

    return 0


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(
            BuildImpl.Main(
                BuildImpl.Configuration(
                    "SharedLibrary",
                    configurations=CONFIGURATIONS,
                ),
            ),
        )
    except KeyboardInterrupt:
        pass
