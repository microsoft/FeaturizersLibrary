# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Tool that generates code using in the Featurizer ecosystem."""

import copy
import importlib
import os
import re
import sys
import textwrap

from collections import OrderedDict

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, "GeneratedCode"))
with CallOnExit(lambda: sys.path.pop(0)):
    import Featurizers_PythonJsonSerialization as Serialization

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
                ext != ".py"
                or not basename.endswith("Plugin")
                or basename == "Plugin"
            ):
                continue

            mod = importlib.import_module(basename)

            plugin_class = getattr(mod, "Plugin", None)
            if plugin_class is None:
                raise Exception("The module '{}' does not contain a supported plugin".format(fullpath))

            error_string = plugin_class.IsValidEnvironment()
            if error_string is not None:
                sys.stdout.write("INFO: {}\n".format(error_string))
                continue

            yield plugin_class

PLUGINS                                     = OrderedDict([(plugin.Name, plugin) for plugin in EnumeratePlugins()])
del EnumeratePlugins

if not PLUGINS:
    sys.stdout.write("\nWARNING: No plugins were found.\n")
    sys.exit(1)

_PluginTypeInfo                             = CommandLine.EnumTypeInfo(list(six.iterkeys(PLUGINS)))

# ----------------------------------------------------------------------
@CommandLine.EntryPoint(
    # BugBug
)
@CommandLine.Constraints(
    plugin=_PluginTypeInfo,
    input_filename=CommandLine.FilenameTypeInfo(),
    output_dir=CommandLine.DirectoryTypeInfo(
        ensure_exists=False,
    ),
    output_stream=None,
)
def EntryPoint(
    plugin,
    input_filename,
    output_dir,
    output_stream=sys.stdout,
):
    """Generates content based on a configuration file according to the specified plugin"""

    plugin = PLUGINS[plugin]

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        dm.stream.write("Reading input data...")
        with dm.stream.DoneManager():
            data = Serialization.Deserialize(input_filename)

        dm.stream.write("Preprocessing data...")
        with dm.stream.DoneManager():
            # If there are templates at play, preprocess the content and expand the values
            new_data = []

            for item in data:
                if not hasattr(item, "template"):
                    new_data.append([item])
                    continue

                regex = re.compile(r"\b{}\b".format(item.template.name))

                new_data_items = []

                for template_type in item.template.types:
                    new_item = copy.deepcopy(item)
                    new_item.template = template_type

                    for configuration_param in getattr(new_item, "configuration_params", []):
                        configuration_param.type = regex.sub(template_type, configuration_param.type)

                    new_item.input_type = regex.sub(template_type, new_item.input_type)
                    new_item.transformed_type = regex.sub(template_type, new_item.transformed_type)

                    for custom_struct in getattr(new_item, "custom_structs", []):
                        for member in custom_struct.members:
                            member.type = regex.sub(template_type, member.type)

                    new_data_items.append(new_item)

                new_data.append(new_data_items)

            data = new_data

        dm.stream.write("Generating content...")
        with dm.stream.DoneManager() as this_dm:
            FileSystem.MakeDirs(output_dir)

            this_dm.result = plugin.Generate(data, output_dir, this_dm.stream)
            if this_dm.result != 0:
                return this_dm.result

        return dm.result

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def CommandLineSuffix():
    content = []

    for plugin in six.itervalues(PLUGINS):
        content.append(
            "    {name:<36} {desc}".format(
                name="{}:".format(plugin.Name),
                desc=plugin.Description,
            ),
        )

    return textwrap.dedent(
        """\
        Where '<plugin>' can be one of the following values:

        {}

        """,
    ).format("\n".join(content).rstrip())

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(CommandLine.Main())
    except KeyboardInterrupt:
        pass
