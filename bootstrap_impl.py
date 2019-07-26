# ----------------------------------------------------------------------
# |
# |  bootstrap_impl.py
# |
# |  David Brownell <db@DavidBrownell.com>
# |      2019-05-21 08:23:15
# |
# ----------------------------------------------------------------------
# |
# |  Copyright David Brownell 2019
# |  Distributed under the Boost Software License, Version 1.0. See
# |  accompanying file LICENSE_1_0.txt or copy at
# |  http://www.boost.org/LICENSE_1_0.txt.
# |
# ----------------------------------------------------------------------
"""Performs repository bootstrap activities (Enlistment and setup)"""

import os
import shutil
import sys
import textwrap

from collections import OrderedDict

import inflect as inflect_mod
import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment import Process
from CommonEnvironment.Shell.All import CurrentShell
from CommonEnvironment.StreamDecorator import StreamDecorator
from CommonEnvironment import StringHelpers

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# Tuples in the form:
#   ("<repo name>", "<clone command line>", "<setup command suffix>" or None)
_REPO_DATA                                  = [
    ("Common_cpp_Clang_8", 'git clone https://github.com/davidbrownell/Common_cpp_Clang_8 "{output_dir}"', None),
    ("Common_cpp_Clang_Common", 'git clone https://github.com/davidbrownell/Common_cpp_Clang_Common "{output_dir}"', None),
    ("Common_cpp_Common", 'git clone https://github.com/davidbrownell/Common_cpp_Common "{output_dir}"', None),
    ("Common_cpp_boost_Common", 'git clone https://github.com/davidbrownell/Common_cpp_boost_Common "{output_dir}"', None),
    ("Common_cpp_boost_1.70.0", 'git clone https://github.com/davidbrownell/Common_cpp_boost_1.70.0 "{output_dir}"', '"/configuration=standard" "/configuration=MSVC-2019-x64"'),
]

if CurrentShell.CategoryName == "Linux":
    _REPO_DATA += [
        ("Common_cpp_binutils", 'git clone https://github.com/davidbrownell/Common_cpp_binutils "{output_dir}"', None),
        ("Common_cpp_GCC", 'git clone https://github.com/davidbrownell/Common_cpp_GCC "{output_dir}"', None),
    ]
elif CurrentShell.CategoryName == "Windows":
    _REPO_DATA += [
        ("Common_cpp_MSVC_2019", 'git clone https://github.com/davidbrownell/Common_cpp_MSVC_2019 "{output_dir}"', None),
        ("Common_cpp_MSVC_Common", 'git clone https://github.com/davidbrownell/Common_cpp_MSVC_Common "{output_dir}"', None),
        ("Common_cpp_MSVC_WindowsKits_10", 'git clone https://github.com/davidbrownell/Common_cpp_MSVC_WindowsKits_10 "{output_dir}"', None),
    ]
else:
    raise Exception("'{}' is not supported OS".format(CurrentShell.CategoryName))

_ACTIVATION_REPO_CONFIGURATION              = "<x64|featurizer_prep>"

# ----------------------------------------------------------------------
inflect                                     = inflect_mod.engine()

# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    output_dir=CommandLine.DirectoryTypeInfo(),
    output_stream=None,
)
def EntryPoint(
    output_dir,
    verbose=False,
    output_stream=sys.stdout,
):
    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        repo_data = OrderedDict()
        enlistment_repositories = []
        sync_repositories = []

        dm.stream.write("Calculating enlistment repositories...")
        with dm.stream.DoneManager(
            done_suffix=lambda: "{} found for enlistment".format(inflect.no("repository", len(enlistment_repositories))),
            suffix="\n",
        ) as this_dm:
            for data in _REPO_DATA:
                repo_name = data[0]

                repo_output_dir = os.path.join(output_dir, repo_name.replace("_", os.path.sep))
                if not os.path.isdir(repo_output_dir):
                    enlistment_repositories.append((repo_output_dir, data))
                else:
                    sync_repositories.append((repo_output_dir, data))

                repo_data[repo_output_dir] = data

        repo_data[_script_dir] = (_script_dir, None, None)

        if enlistment_repositories:
            dm.stream.write("Enlisting in {}...".format(inflect.no("repository", len(enlistment_repositories))))
            with dm.stream.DoneManager(
                suffix="\n",
            ) as enlist_dm:
                for index, (repo_output_dir, data) in enumerate(enlistment_repositories):
                    enlist_dm.stream.write("'{}' ({} of {})...".format(data[0], index + 1, len(enlistment_repositories)))
                    with enlist_dm.stream.DoneManager() as this_dm:
                        FileSystem.MakeDirs(os.path.dirname(repo_output_dir))

                        temp_directory = repo_output_dir + "_tmp"

                        sink = six.moves.StringIO()

                        this_dm.result = Process.Execute(
                            data[1].format(
                                output_dir=temp_directory,
                            ),
                            StreamDecorator(
                                [
                                    sink,
                                    StreamDecorator(
                                        this_dm.stream if verbose else None,
                                        line_prefix="INFO: ",
                                    ),
                                ],
                            ),
                        )
                        if this_dm.result != 0:
                            if not verbose:
                                this_dm.stream.write(sink.getvalue())

                            return this_dm.result

                        shutil.move(temp_directory, repo_output_dir)

                if CurrentShell.CategoryName == "Linux":
                    CurrentShell.UpdateOwnership(output_dir)

        if sync_repositories:
            dm.stream.write("Syncing {}...".format(inflect.no("repository", len(sync_repositories))))
            with dm.stream.DoneManager(
                suffix="\n",
            ) as sync_dm:
                sync_command_template = '{} PullAndUpdate "/directory={{}}"'.format(CurrentShell.CreateScriptName("SCM"))

                for index, (repo_output_dir, data) in enumerate(sync_repositories):
                    sync_dm.stream.write("'{}' ({} of {})...".format(data[0], index + 1, len(sync_repositories)))
                    with sync_dm.stream.DoneManager() as this_dm:
                        this_dm.result, output = Process.Execute(sync_command_template.format(repo_output_dir))
                        if this_dm.result != 0:
                            this_dm.stream.write(output)

                if sync_dm.result != 0:
                    return sync_dm.result

        dm.stream.write("Setting up {}...".format(inflect.no("repository", len(repo_data))))
        with dm.stream.DoneManager(
            suffix="\n",
        ) as setup_dm:
            command_line_template = "Setup{} {{suffix}}".format(CurrentShell.ScriptExtension)

            for index, (repo_output_dir, data) in enumerate(six.iteritems(repo_data)):
                setup_dm.stream.write("'{}' ({} of {})...".format(data[0], index + 1, len(repo_data)))
                with setup_dm.stream.DoneManager() as this_dm:
                    prev_dir = os.getcwd()
                    os.chdir(repo_output_dir)

                    with CallOnExit(lambda: os.chdir(prev_dir)):
                        command_line = command_line_template.format(
                            suffix=data[2] or "",
                        )

                        if CurrentShell.CategoryName == "Linux":
                            command_line = "./{}".format(command_line)

                        sink = six.moves.StringIO()

                        this_dm.result = Process.Execute(
                            command_line,
                            StreamDecorator(
                                [
                                    sink,
                                    StreamDecorator(
                                        this_dm.stream if verbose else None,
                                        line_prefix="INFO: ",
                                    ),
                                ],
                            ),
                        )
                        if this_dm.result != 0:
                            if not verbose:
                                this_dm.stream.write(sink.getvalue())

                            return this_dm.result

        dm.stream.write(
            StringHelpers.LeftJustify(
                textwrap.dedent(
                    """\






                    # ----------------------------------------------------------------------
                    # ----------------------------------------------------------------------
                    # ----------------------------------------------------------------------

                    The enlistment and setup of all repositories was successful. To begin
                    development activities, please run the following command. Note that
                    this command must be run every time you open a new terminal window.

                        {}{} {}

                    # ----------------------------------------------------------------------
                    # ----------------------------------------------------------------------
                    # ----------------------------------------------------------------------

                    """,
                ).format(
                    ". " if CurrentShell.CategoryName == "Linux" else "",
                    os.path.join(
                        _script_dir,
                        "Activate{}{}".format(
                            ".{}".format(os.getenv("DEVELOPMENT_ENVIRONMENT_ENVIRONMENT_NAME")) if os.getenv("DEVELOPMENT_ENVIRONMENT_ENVIRONMENT_NAME") != "DefaultEnv" else "",
                            CurrentShell.ScriptExtension,
                        ),
                    ),
                    _ACTIVATION_REPO_CONFIGURATION or "",
                ),
                16,
                skip_first_line=False,
            ),
        )

        return dm.result

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(CommandLine.Main())
    except KeyboardInterrupt:
        pass
