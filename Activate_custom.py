# ----------------------------------------------------------------------
# |
# |  Activate_custom.py
# |
# |  David Brownell <db@DavidBrownell.com>
# |      2018-05-07 08:59:57
# |
# ----------------------------------------------------------------------
# |
# |  Copyright David Brownell 2018-19.
# |  Distributed under the Boost Software License, Version 1.0.
# |  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# |
# ----------------------------------------------------------------------
"""Performs repository-specific activation activities."""

import os
import sys
import textwrap
import uuid

sys.path.insert(0, os.getenv("DEVELOPMENT_ENVIRONMENT_FUNDAMENTAL"))
from RepositoryBootstrap.SetupAndActivate import CommonEnvironment, CurrentShell

del sys.path[0]

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# <Class '<name>' has no '<attr>' member> pylint: disable = E1101
# <Unrearchable code> pylint: disable = W0101
# <Unused argument> pylint: disable = W0613

# ----------------------------------------------------------------------
def GetCustomActions(
    output_stream,
    configuration,
    version_specs,
    generated_dir,
    debug,
    verbose,
    fast,
    repositories,
    is_mixin_repo,
):
    """
    Returns an action or list of actions that should be invoked as part of the activation process.

    Actions are generic command line statements defined in
    <Common_Environment>/Libraries/Python/CommonEnvironment/v1.0/CommonEnvironment/Shell/Commands/__init__.py
    that are converted into statements appropriate for the current scripting language (in most
    cases, this is Bash on Linux systems and Batch or PowerShell on Windows systems.
    """

    actions = []

    if configuration == "universal_linux":
        python_uuid = str(uuid.uuid4()).replace("-", "")
        cmake_uuid = str(uuid.uuid4()).replace("-", "")

        actions += [
            CurrentShell.Commands.Set("CC", "gcc"),
            CurrentShell.Commands.Set("GCC", "g++"),

            # Activating holy-build-box updates the path to include a new version of python,
            # and other tools, so we need to restore the originals. Preserve the current values
            # to file(s).
            CurrentShell.Commands.Raw('which python > {}'.format(python_uuid)),
            CurrentShell.Commands.Raw('which cmake > {}'.format(cmake_uuid)),

            # Activate holy-build-box
            CurrentShell.Commands.Message("\n"),
            CurrentShell.Commands.Call("/hbb_shlib/activate"),

            # Restore the original values
            CurrentShell.Commands.Raw('export PATH=$(dirname $(cat {})):${{PATH}}'.format(python_uuid)),
            CurrentShell.Commands.Raw('export PATH=$(dirname $(cat {})):${{PATH}}'.format(cmake_uuid)),

            # Delete the temp files
            CurrentShell.Commands.Raw('rm -f {}'.format(python_uuid)),
            CurrentShell.Commands.Raw('rm -f {}'.format(cmake_uuid)),

            CurrentShell.Commands.Augment(
                "CXXFLAGS",
                "-static-libstdc++",
                is_space_delimited_string=True,
                append_values=True,
            ),

            # All of the build tools want to use Ninja as the cmake generator, but ninja doesn't work in the universal_linux
            # environment. Rather than specifying a generator, use whichever happens to be the default on the machine.
            CurrentShell.Commands.Set("DEVELOPMENT_ENVIRONMENT_CPP_USE_DEFAULT_CMAKE_GENERATOR", "1"),
            CurrentShell.Commands.Message(
                textwrap.dedent(
                    """\


                    This configuration should be run within a Docker container using the image
                    'phusion/holy-build-box-64' when building universal linux binaries. More
                    information about Holy Build Box is available at
                    http://phusion.github.io/holy-build-box/.

                    This environment may be activated within a docker container by running:

                        docker run -it --rm phusion/holy-build-box-64


                    """,
                ),
            ),
        ]

    return actions


# ----------------------------------------------------------------------
def GetCustomScriptExtractors():
    """
    Returns information that can be used to enumerate, extract, and generate documentation
    for scripts stored in the Scripts directory in this repository and all repositories
    that depend upon it.

    ****************************************************
    Note that it is very rare to have the need to implement
    this method. In most cases, it is safe to delete it.
    ****************************************************

    There concepts are used with custom script extractors:

        - DirGenerator:             Method to enumerate sub-directories when searching for scripts in a
                                    repository's Scripts directory.

                                        def Func(directory, version_sepcs) -> [ (subdir, should_recurse), ... ]
                                                                              [ subdir, ... ]
                                                                              (subdir, should_recurse)
                                                                              subdir

        - CreateCommands:           Method that creates the shell commands to invoke a script.

                                        def Func(script_filename) -> [ command, ...]
                                                                     command
                                                                     None           # Indicates not supported

        - CreateDocumentation:      Method that extracts documentation from a script.

                                        def Func(script_filename) -> documentation string

        - ScriptNameDecorator:      Returns a new name for the script.

                                        def Func(script_filename) -> name string

    See <Common_Environment>/Activate_custom.py for an example of how script extractors
    are used to process Python and PowerShell scripts.
    """

    return
