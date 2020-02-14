# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Builds the Shared Library"""

import datetime
import hashlib
import json
import os
import shutil
import sys
import textwrap

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
JSON_FILENAME                               = "Microsoft MLFeaturizers.FileAttributes.json"

# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    configuration=CommandLine.EnumTypeInfo(CONFIGURATIONS),
    output_dir=CommandLine.DirectoryTypeInfo(
        ensure_exists=False,
    ),
    prerelease_build_name=CommandLine.StringTypeInfo(
        arity="?",
    ),
    cmake_generator=CommandLine.StringTypeInfo(
        arity="?",
    ),
    output_stream=None,
)
def Build(
    configuration,
    output_dir,
    release_build=False,
    prerelease_build_name=None,
    no_build_info=False,
    keep_temp_dir=False,
    cmake_generator=(
        None if os.getenv("DEVELOPMENT_ENVIRONMENT_REPOSITORY_CONFIGURATION") == "universal_linux" or os.getenv("DEVELOPMENT_ENVIRONMENT_CPP_USE_DEFAULT_CMAKE_GENERATOR") else "Ninja"
    ),
    output_stream=sys.stdout,
    verbose=False,
):
    """Builds the Featurizer Shared Library"""

    if release_build and prerelease_build_name:
        raise CommandLine.UsageException(
            "A prerelese build name cannot be provided with the 'release_build' flag",
        )

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        FileSystem.RemoveTree(output_dir)
        FileSystem.MakeDirs(output_dir)

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
                if not release_build:
                    if prerelease_build_name is None:
                        # This value should compare as:
                        #   "manual" < "pipeline"
                        prerelease_build_name = "manual"

                    if not no_build_info:
                        now = datetime.datetime.now()

                        prerelease_build_name = "{prerelease_build_name}.{year}.{month}.{day}.{hour}.{minute}.{second}.{configuration}".format(
                            year=now.year,
                            month=now.month,
                            day=now.day,
                            hour=now.hour,
                            minute=now.minute,
                            second=now.second,
                            prerelease_build_name=prerelease_build_name,
                            configuration=configuration.lower(),
                        )

                activities = [
                    (
                        "Generating cmake Files",
                        'cmake {generator}-DCMAKE_BUILD_TYPE={configuration} {prerelease_build_name} "{this_dir}"'.format(
                            generator='-G "{}" '.format(
                                cmake_generator,
                            ) if cmake_generator else "",
                            temp_dir=temp_directory,
                            configuration=configuration,
                            this_dir=_script_dir,
                            prerelease_build_name="" if not prerelease_build_name else "-DPRODUCT_VERSION_PRERELEASE_INFO={}".format(
                                prerelease_build_name,
                            ),
                        ),
                    ),
                    ("Building", "cmake --build ."),
                ]

                if (
                    os.getenv("DEVELOPMENT_ENVIRONMENT_REPOSITORY_CONFIGURATION")
                    == "universal_linux"
                ):
                    activities.append(
                        (
                            "Verifying Universal Linux Binaries",
                            "libcheck libFeaturizers.so",
                        ),
                    )

                activities += [
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
    output_dir=CommandLine.DirectoryTypeInfo(
        ensure_exists=False,
    ),
    build_dir=CommandLine.DirectoryTypeInfo(
        arity="+",
    ),
    output_stream=None,
)
def Package(
    output_dir,
    build_dir,
    output_stream=sys.stdout,
    verbose=False,
):
    """Packages previously built content"""

    build_dirs = build_dir
    del build_dir

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        if len(build_dirs) > 1:
            dm.stream.write("Ensuring that build data matches...")
            with dm.stream.DoneManager() as ensure_dm:
                ensure_dm.stream.write("Checking '{}'...".format(JSON_FILENAME))
                with ensure_dm.stream.DoneManager() as this_dm:
                    this_dm.result = (
                        0
                        if _CompareFiles(
                            this_dm.stream,
                            *[
                                os.path.join(build_dir, JSON_FILENAME)
                                for build_dir in build_dirs
                            ]
                        )
                        else -1
                    )
                    if this_dm.result != 0:
                        return this_dm.result

                ensure_dm.stream.write("Checking 'Data' directories...")
                with ensure_dm.stream.DoneManager() as this_dm:
                    this_dm.result = (
                        0
                        if _CompareDirectories(
                            this_dm.stream,
                            *[os.path.join(build_dir, "Data") for build_dir in build_dirs]
                        )
                        else -1
                    )
                    if this_dm.result != 0:
                        return this_dm.result

        dm.stream.write("Reading build configuration...")
        with dm.stream.DoneManager() as this_dm:
            json_filename = os.path.join(build_dirs[0], JSON_FILENAME)
            if not os.path.isfile(json_filename):
                this_dm.stream.write(
                    "ERROR: The filename '{}' does not exist.\n".format(json_filename),
                )
                this_dm.result = -1

                return this_dm.result

            with open(json_filename) as f:
                build_config = json.load(f)

            build_config["build_dir"] = build_dirs[0]
            build_config["data_dir"] = os.path.join(build_dirs[0], "Data", "**", "*.*")
            build_config["package_id"] = build_config["product_name"].replace(" ", ".")
            build_config["product_copyright"] = build_config["product_copyright"].replace(
                "(C)",
                "Â©",
            )

        # Generate the correct nuget file statements based on output in the build_dir
        dm.stream.write("Generating nuget file statements...")
        with dm.stream.DoneManager() as this_dm:
            nuget_file_statements = {}

            for build_dir in build_dirs:
                these_files = []
                value_type = None

                for item in os.listdir(build_dir):
                    this_value_type = None

                    if item == "Featurizers.dll":
                        if "x86" in build_dir:
                            this_value_type = "runtimes/win-x86/native"
                        else:
                            this_value_type = "runtimes/win-x64/native"

                    elif item.startswith("libFeaturizers.so"):
                        this_value_type = "runtimes/linux-x64/native"

                    else:
                        name, ext = os.path.splitext(item)
                        if name.startswith("libFeaturizers") and ext == ".dylib":
                            this_value_type = "runtimes/osx-x64/native"

                    if this_value_type is not None:
                        assert value_type is None or this_value_type == value_type, (
                            value_type,
                            item,
                            this_value_type,
                        )

                        value_type = this_value_type
                        these_files.append(os.path.join(build_dir, item))

                if value_type in nuget_file_statements:
                    this_dm.stream.write(
                        "ERROR: The build directory '{}' overwrites previously captured content ({}: '{}').\n".format(
                            build_dir,
                            value_type,
                            nuget_file_statements[value_type],
                        ),
                    )
                    this_dm.result = -1

                    return this_dm.result

                nuget_file_statements[value_type] = these_files

            file_statements = []

            for k, v in six.iteritems(nuget_file_statements):
                for filename in v:
                    file_statements.append(
                        '<file src="{}" target="{}" />'.format(filename, k),
                    )

            build_config["file_statements"] = "\n".join(file_statements)

        FileSystem.MakeDirs(output_dir)

        dm.stream.write("Writing nuspec file...")
        with dm.stream.DoneManager():
            nuspec_filename = os.path.join(output_dir, "Featurizers.nuspec")
            with open(nuspec_filename, "w") as f:
                f.write(_nuget_template.format(**build_config))

        dm.stream.write("Running nuget...")
        with dm.stream.DoneManager() as this_dm:
            prev_dir = os.getcwd()

            os.chdir(output_dir)
            with CallOnExit(lambda: os.chdir(prev_dir)):
                this_dm.result = Process.Execute(
                    'nuget.exe pack "{}"'.format(nuspec_filename),
                    this_dm.stream,
                )
                if this_dm.result != 0:
                    return this_dm.result

        return dm.result


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------

# Note that in the following template, '<owners>microsoft</owners>' needs
# to be lowercase to conform to nuget standards.
_nuget_template                             = textwrap.dedent(
    """\
    <?xml version="1.0"?>
    <package xmlns="http://schemas.microsoft.com/packaging/2013/05/nuspec.xsd">
        <metadata>
            <id>{package_id}</id>
            <version>{product_version_full}</version>
            <authors>Microsoft</authors>
            <owners>microsoft</owners>
            <license type="expression">MIT</license>
            <licenseUrl>https://licenses.nuget.org/MIT</licenseUrl>
            <requireLicenseAcceptance>true</requireLicenseAcceptance>
            <copyright>{product_copyright}</copyright>

            <description>{product_bundle}</description>
            <projectUrl>https://aka.ms/MLFeaturizers</projectUrl>

            <contentFiles>
                <files include="any/any/Data/**/*.json" buildAction="None" copyToOutput="true" />
            </contentFiles>
        </metadata>
        <files>
    <file src="{data_dir}" target="contentFiles/any/any/Data" />
    {file_statements}
        </files>
    </package>
    """,
)


# ----------------------------------------------------------------------
def _CopyBinaries(temp_directory, output_dir, output_stream):
    output_files = [JSON_FILENAME]

    if CurrentShell.CategoryName == "Windows":
        output_files += ["Featurizers.dll", "Featurizers.pdb"]
    elif CurrentShell.CategoryName in ["Linux", "BSD"]:
        for item in os.listdir(temp_directory):
            if item.startswith("libFeaturizers") and not os.path.splitext(item)[1] in [
                ".a"
            ]:
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

    FileSystem.CopyTree(os.path.join(temp_directory, "Data"), output_dir)

    return 0


# ----------------------------------------------------------------------
def _CopyHeaders(temp_directory, output_dir, output_stream):
    output_files = []

    output_files += list(
        FileSystem.WalkFiles(
            _script_dir,
            include_file_extensions=[".h"],
            include_file_base_names=[
                lambda basename: basename.startswith("SharedLibrary_")
            ],
            recurse=False,
        ),
    )

    output_files += list(
        FileSystem.WalkFiles(
            os.path.join(_script_dir, "GeneratedCode"),
            include_file_extensions=[".h"],
            include_file_base_names=[
                lambda basename: basename.startswith("SharedLibrary_")
            ],
            exclude_file_names=["SharedLibrary_PointerTable.h"],
            recurse=False,
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
def _CalculateHash(filename):
    hash = hashlib.sha256()

    with open(filename, "rb") as f:
        while True:
            content = f.read(4096)
            if not content:
                break

            # We need to remove carriage returns here to ensure that text content compares
            # equally when produced by Linux ('\n') and Windows ('\r\n') builds.
            content = content.replace(b"\r", b"")

            hash.update(content)

    return hash.hexdigest()


# ----------------------------------------------------------------------
def _CompareFiles(output_stream, *filenames):
    assert len(filenames) > 1, filenames

    if not os.path.isfile(filenames[0]):
        return False

    oracle = _CalculateHash(filenames[0])

    for filename in filenames[1:]:
        if not os.path.isfile(filename):
            return False

        if _CalculateHash(filename) != oracle:
            output_stream.write(
                "'{}' does not match '{}'.\n".format(filename, filenames[0]),
            )
            return False

    return True


# ----------------------------------------------------------------------
def _CompareDirectories(output_stream, *dirs):
    assert len(dirs) > 1, dirs

    # ----------------------------------------------------------------------
    def GetRelativeFiles(dir):
        output_stream.write("Processing files in '{}'...".format(dir))
        with output_stream.DoneManager():
            results = {}

            for filename in FileSystem.WalkFiles(dir):
                assert filename.startswith(dir), (filename, dir)
                results[FileSystem.TrimPath(filename, dir)] = _CalculateHash(filename)

        return results

    # ----------------------------------------------------------------------

    if not os.path.isdir(dirs[0]):
        return False

    oracle = GetRelativeFiles(dirs[0])

    for dir in dirs[1:]:
        if not os.path.isdir(dir):
            return False

        these_relative_files = GetRelativeFiles(dir)
        if these_relative_files != oracle:
            output_stream.write(
                "The files in '{}' do not match the files in '{}'.\n".format(dir, dirs[0]),
            )
            return False

    return True


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
