# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Performs repository-specific setup activities."""

# ----------------------------------------------------------------------
# |
# |  To setup an environment, run:
# |
# |     Setup(.cmd|.ps1|.sh) [/debug] [/verbose] [/configuration=<config_name>]*
# |
# ----------------------------------------------------------------------

import os
import sys

from collections import OrderedDict

import CommonEnvironment

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# <Missing function docstring> pylint: disable = C0111
# <Line too long> pylint: disable = C0301
# <Wrong hanging indentation> pylint: disable = C0330
# <Class '<name>' has no '<attr>' member> pylint: disable = E1103
# <Unreachable code> pylint: disable = W0101
# <Wildcard import> pylint: disable = W0401
# <Unused argument> pylint: disable = W0613

fundamental_repo                            = os.getenv("DEVELOPMENT_ENVIRONMENT_FUNDAMENTAL")
assert os.path.isdir(fundamental_repo), fundamental_repo

sys.path.insert(0, fundamental_repo)
from RepositoryBootstrap import *                                           # <Unused import> pylint: disable = W0614
from RepositoryBootstrap.SetupAndActivate import CurrentShell               # <Unused import> pylint: disable = W0614
from RepositoryBootstrap.SetupAndActivate.Configuration import *            # <Unused import> pylint: disable = W0614

del sys.path[0]

# ----------------------------------------------------------------------
# There are two types of repositories: Standard and Mixin. Only one standard
# repository may be activated within an environment at a time while any number
# of mixin repositories can be activated within a standard repository environment.
# Standard repositories may be dependent on other repositories (thereby inheriting
# their functionality), support multiple configurations, and specify version
# information for tools and libraries in themselves or its dependencies.
#
# Mixin repositories are designed to augment other repositories. They cannot
# have configurations or dependencies and may not be activated on their own.
#
# These difference are summarized in this table:
#
#                                                       Standard  Mixin
#                                                       --------  -----
#      Can be activated in isolation                       X
#      Supports configurations                             X
#      Supports VersionSpecs                               X
#      Can be dependent upon other repositories            X
#      Can be activated within any other Standard                  X
#        repository
#
# Consider a script that wraps common Git commands. This functionality is useful
# across a number of different repositories, yet doesn't have functionality that
# is useful on its own; it provides functionality that augments other repositories.
# This functionality should be included within a repository that is classified
# as a mixin repository.
#
# To classify a repository as a Mixin repository, decorate the GetDependencies method
# with the MixinRepository decorator.
#


# @MixinRepository # <-- Uncomment this line to classify this repository as a mixin repository
def GetDependencies():
    """
    Returns information about the dependencies required by this repository.

    The return value should be an OrderedDict if the repository supports multiple configurations
    (aka is configurable) or a single Configuration if not.
    """

    d = OrderedDict()

    architectures = ["x64"]

    if CurrentShell.CategoryName == "Windows":
        architectures.append("x86")

    # Clang
    for version, guid in [("8", "3DE9F3430E494A6C8429B26A1503C895")]:
        for architecture in architectures:
            d["{}_Clang_{}".format(architecture, version)] = Configuration(
                "Builds using Clang {} for a {} architecture".format(
                    version,
                    architecture,
                ),
                [
                    Dependency(
                        guid,
                        "Common_cpp_Clang_{}".format(version),
                        "{}-ex".format(architecture),
                        "https://github.com/davidbrownell/Common_cpp_Clang_{}".format(
                            version,
                        ),
                    ),
                ],
            )

    # MSVC
    if CurrentShell.CategoryName == "Windows":
        for version, guid in [
            ("2019", "AB7D87C49C2449F79D9F42E5195030FD"),
            ("2017", "8FC8ACE80A594D2EA996CAC5DBFFEBBC"),
        ]:
            for architecture in architectures:
                d["{}_MSVC_{}".format(architecture, version)] = Configuration(
                    "Builds using MSVC {} for a {} architecture".format(
                        version,
                        architecture,
                    ),
                    [
                        Dependency(
                            guid,
                            "Common_cpp_MSVC_{}".format(version),
                            architecture,
                            "https://github.com/davidbrownell/Common_cpp_MSVC_{}.git".format(
                                version,
                            ),
                        ),
                    ],
                )

    # Misc
    d["system_compiler"] = Configuration(
        "Enables basic C++ tools (cmake, ninja, doxygen, etc.)",
        [
            Dependency(
                "F33C43DA6BB54336A7573B39509CDAD7",
                "Common_cpp_Common",
                "x64",
                "https://github.com/davidbrownell/Common_cpp_Common.git",
            ),
        ],
    )

    if CurrentShell.CategoryName == "Linux":
        d["universal_linux"] = Configuration(
            "Builds using the Holy Build Box Docker Image (phusion/holy-build-box-64). More info at http://phusion.github.io/holy-build-box/",
            [
                Dependency(
                    "F33C43DA6BB54336A7573B39509CDAD7",
                    "Common_cpp_Common",
                    "x64",
                    "https://github.com/davidbrownell/Common_cpp_Common.git",
                ),
            ],
        )

    # Set the defaults
    d["x64_Clang"] = d["x64_Clang_8"]
    if "x86" in architectures:
        d["x86_Clang"] = d["x86_Clang_8"]

    if CurrentShell.CategoryName == "Windows":
        d["x64_MSVC"] = d["x64_MSVC_2019"]
        d["x86_MSVC"] = d["x86_MSVC_2019"]

    d["x64"] = d["x64_Clang"]
    if "x86" in architectures:
        d["x86"] = d["x86_Clang"]

    return d


# ----------------------------------------------------------------------
def GetCustomActions(debug, verbose, explicit_configurations):
    """
    Returns an action or list of actions that should be invoked as part of the setup process.

    Actions are generic command line statements defined in
    <Common_Environment>/Libraries/Python/CommonEnvironment/v1.0/CommonEnvironment/Shell/Commands/__init__.py
    that are converted into statements appropriate for the current scripting language (in most
    cases, this is Bash on Linux systems and Batch or PowerShell on Windows systems.
    """

    return []
