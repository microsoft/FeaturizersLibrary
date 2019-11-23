# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Generates wrapper code for interfaces extracted from C++ source"""

import importlib
import os
import sys
import textwrap

from collections import OrderedDict

import inflect as inflect_mod
import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment import Interface
from CommonEnvironment.StreamDecorator import StreamDecorator

from CommonEnvironment.CompilerImpl.CodeGenerator import CommandLineGenerate, CommandLineClean

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

from Impl.CodeGenerator import CreateCodeGenerator

# ----------------------------------------------------------------------
def EnumeratePlugins():
    plugin_dir = os.path.join(_script_dir, "Plugins")
    if not os.path.isdir(plugin_dir):
        raise Exception("'{}' is not a valid directory".format(plugin_dir))

    sys.path.insert(0, plugin_dir)
    with CallOnExit(lambda: sys.path.pop(0)):
        for item in os.listdir(plugin_dir):
            fullpath = os.path.join(plugin_dir, item)
            if not os.path.isfile(fullpath):
                continue

            basename, ext = os.path.splitext(item)

            if (
                not basename.endswith("Plugin")
                or basename == "Plugin"
                or ext != ".py"
            ):
                continue

            mod = importlib.import_module(basename)

            plugin_class = getattr(mod, "Plugin", None)
            if plugin_class is None:
                raise Exception("The module '{}' does not contain a supported plugin".format(fullpath))

            error_string = plugin_class.IsValidEnvironment()
            if error_string is not None:
                sys.stdout.write("INFO: {}\n".format(error_string.strip()))
                continue

            yield plugin_class

PLUGINS                                     = OrderedDict([(plugin.Name, plugin) for plugin in EnumeratePlugins()])
del EnumeratePlugins

if not PLUGINS:
    sys.stdout.write("\nWARNING: No plugins were found.\n")
    sys.exit(1)

_PluginTypeInfo                             = CommandLine.EnumTypeInfo(list(six.iterkeys(PLUGINS)))

inflect                                     = inflect_mod.engine()

# ----------------------------------------------------------------------
@CommandLine.EntryPoint(
    plugin=CommandLine.EntryPoint.Parameter("Name of plugin used for generation."),
    output_name=CommandLine.EntryPoint.Parameter("Output name used during generation; the way in which this value impacts generated output varies from plugin to plugin."),
    output_dir=CommandLine.EntryPoint.Parameter("Output directory used during generation; the way in which this value impacts generated output varies from plugin to plugin."),
    input=CommandLine.EntryPoint.Parameter("C++ input filename or directory containing C++ source code."),
    include_regex=CommandLine.EntryPoint.Parameter("Regular expression used to control which include files are parsed when extracting information from C++ files; only files in this list are included when specified."),
    exclude_regex=CommandLine.EntryPoint.Parameter("Regular expression used to control which include files are parsed when extracting information from C++ files; files in this list are excluded."),
    output_data_filename_prefix=CommandLine.EntryPoint.Parameter("Prefix for filenames used by the compiler system to store information from invocation to invocation; customize this value if multiple plugins output to the same output directory."),
    plugin_arg=CommandLine.EntryPoint.Parameter("Argument value passed directly to the plugin"),
    force=CommandLine.EntryPoint.Parameter("Force generation"),
    verbose=CommandLine.EntryPoint.Parameter("Generate verbose output"),
)
@CommandLine.Constraints(
    plugin=_PluginTypeInfo,
    output_name=CommandLine.StringTypeInfo(),
    output_dir=CommandLine.DirectoryTypeInfo(
        ensure_exists=False,
    ),
    input=CommandLine.FilenameTypeInfo(
        match_any=True,
        arity="+",
    ),
    include_regex=CommandLine.StringTypeInfo(
        arity="*",
    ),
    exclude_regex=CommandLine.StringTypeInfo(
        arity="*",
    ),
    output_data_filename_prefix=CommandLine.StringTypeInfo(
        arity="?",
    ),
    plugin_arg=CommandLine.DictTypeInfo(
        require_exact_match=False,
        arity="?",
    ),
    output_stream=None,
)
def Generate(
    plugin,
    output_name,
    output_dir,
    input,
    include_regex=None,
    exclude_regex=None,
    output_data_filename_prefix=None,
    plugin_arg=None,
    force=False,
    output_stream=sys.stdout,
    verbose=False,
):
    """Generates content for the given input using the named plugin"""

    plugin_args = plugin_arg
    del plugin_arg

    include_regexes = include_regex
    del include_regex

    exclude_regexes = exclude_regex
    del exclude_regex

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        code_generator = CreateCodeGenerator(PLUGINS[plugin])

        # Get the inputs
        inputs = []

        dm.stream.write("Analyzing inputs...")
        with dm.stream.DoneManager(
            suffix="\n",
        ) as this_dm:
            for i in input:
                if os.path.isfile(i):
                    try:
                        code_generator.InputTypeInfo.ValidateItem(i)
                        inputs.append(i)
                    except Exception as ex:
                        this_dm.stream.write("ERROR: {}\n".format(str(ex)))
                        this_dm.result = -1

                elif os.path.isdir(i):
                    len_inputs = len(inputs)

                    for filename in FileSystem.WalkFiles(i):
                        if code_generator.InputTypeInfo.IsValid(filename):
                            inputs.append(filename)

                    if len(inputs) == len_inputs:
                        this_dm.stream.write("WARNING: No valid input files were found in '{}'\n".format(i))
                        if this_dm.result >= 0:
                            this_dm.result = 1

                else:
                    assert False, i

            if this_dm.result < 0:
                return this_dm.result

        # Invoke the code generator
        dm.stream.write("Generating code...")
        with dm.stream.DoneManager() as this_dm:
            this_dm.result = CommandLineGenerate(
                code_generator,
                inputs,
                this_dm.stream,
                verbose,
                plugin_name=plugin,
                output_name=output_name,
                output_dir=output_dir,
                plugin_settings=plugin_args,
                force=force,
                output_data_filename_prefix=output_data_filename_prefix,
                include_regexes=include_regexes,
                exclude_regexes=exclude_regexes,
            )
            if this_dm.result < 0:
                return this_dm.result

        return dm.result


# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    output_dir=CommandLine.DirectoryTypeInfo(),
    output_stream=None,
)
def Clean(
    output_dir,
    output_stream=None,
):
    """Cleans content previously generated"""

    return CommandLineClean(output_dir, output_stream)


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def CommandLineSuffix():
    content = []

    for plugin in six.itervalues(PLUGINS):
        content.append(
            "    {name:<36} {desc}".format(
                name=plugin.Name,
                desc=plugin.Description,
            ),
        )

    return textwrap.dedent(
        """\
        Where '<plugin>' can be one of the following values:

        {}

        """,
    ).format(
        "\n".join(content).rstrip(),
    )


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(CommandLine.Main())
    except KeyboardInterrupt:
        pass
