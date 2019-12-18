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

import inflect as inflect_mod
import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment.StreamDecorator import StreamDecorator
from CommonEnvironment import StringHelpers

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, "GeneratedCode"))
with CallOnExit(lambda: sys.path.pop(0)):
    import Featurizers_PythonYamlSerialization as Serialization

inflect                                     = inflect_mod.engine()

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

            if ext != ".py" or not basename.endswith("Plugin") or basename == "Plugin":
                continue

            mod = importlib.import_module(basename)

            plugin_class = getattr(mod, "Plugin", None)
            if plugin_class is None:
                raise Exception(
                    "The module '{}' does not contain a supported plugin".format(fullpath),
                )

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
@CommandLine.EntryPoint
@CommandLine.Constraints(
    plugin=_PluginTypeInfo,
    input_filename=CommandLine.FilenameTypeInfo(),
    output_dir=CommandLine.DirectoryTypeInfo(
        ensure_exists=False,
    ),
    include=CommandLine.StringTypeInfo(
        arity="*",
    ),
    exclude=CommandLine.StringTypeInfo(
        arity="*",
    ),
    output_stream=None,
)
def EntryPoint(
    plugin,
    input_filename,
    output_dir,
    include=None,
    exclude=None,
    output_stream=sys.stdout,
):
    """Generates content based on a configuration file according to the specified plugin"""

    plugin = PLUGINS[plugin]

    # ----------------------------------------------------------------------
    def ToRegex(value):
        try:
            return re.compile(value)
        except:
            raise CommandLine.UsageException("'{}' is not a valid regular expression".format(value))

    # ----------------------------------------------------------------------

    includes = [ToRegex(arg) for arg in include]
    del include

    excludes = [ToRegex(arg) for arg in exclude]
    del exclude

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        dm.stream.write("Reading input data...")
        with dm.stream.DoneManager() as this_dm:
            try:
                data = Serialization.Deserialize(input_filename)
            except Exception as e:
                this_dm.stream.write(
                    textwrap.dedent(
                        """\
                        ERROR: {}
                               {}
                        """,
                    ).format(
                        StringHelpers.LeftJustify(str(e), len("ERROR: ")),
                        str(getattr(e, "stack", None)),
                    ),
                )

                this_dm.result = -1
                return this_dm.result

        nonlocals = CommonEnvironment.Nonlocals(
            skipped=0,
        )

        dm.stream.write("Preprocessing data...")
        with dm.stream.DoneManager(
            done_suffix=lambda: "{} were skipped".format(
                inflect.no("file", nonlocals.skipped),
            ),
            suffix=lambda: "\n" if nonlocals.skipped else None,
        ) as this_dm:
            # If there are templates at play, preprocess the content and expand the values
            new_data = []

            for item in data:
                if item.status != "Available":
                    this_dm.stream.write(
                        "The status for '{}' is set to '{}' and will not be processed.\n".format(
                            item.name,
                            item.status,
                        ),
                    )
                    nonlocals.skipped += 1

                    continue

                if excludes and any(exclude.match(item.name) for exclude in excludes):
                    this_dm.stream.write("'{}' has been explicitly excluded.\n".format(item.name))
                    nonlocals.skipped += 1

                    continue

                if includes and not any(include.match(item.name) for include in includes):
                    this_dm.stream.write("'{}' has not been included.\n".format(item.name))
                    nonlocals.skipped += 1

                    continue

                if not hasattr(item, "templates"):
                    assert item.type_mappings

                    for mapping in item.type_mappings:
                        new_item = copy.deepcopy(item)

                        new_item.input_type = mapping.input_type
                        new_item.output_type = mapping.output_type
                        new_item.is_input_optional = mapping.is_input_optional
                        new_item.is_output_optional = mapping.is_output_optional

                        new_data.append([new_item])

                    continue

                new_data_items = []
                for template in item.templates:
                    regex = re.compile(r"\b{}\b".format(template.name))

                    for template_type in template.types:
                        new_item = copy.deepcopy(item)
                        new_item.template = template_type

                        # Remove the template mapping and list of templates
                        del new_item.templates
                        del new_item.type_mappings

                        for configuration_param in getattr(
                            new_item,
                            "configuration_params",
                            [],
                        ):
                            configuration_param.type = regex.sub(
                                template_type,
                                configuration_param.type,
                            )

                        for custom_struct in getattr(new_item, "custom_structs", []):
                            for member in custom_struct.members:
                                member.type = regex.sub(template_type, member.type)

                        for mapping in item.type_mappings:
                            # Since we can have multiple templates this is for when a mapping doesn't use a template or not the current template
                            if (
                                mapping.input_type != template.name
                                and mapping.output_type != template.name
                            ):
                                continue

                            new_item.input_type = regex.sub(
                                template_type,
                                mapping.input_type,
                            )
                            new_item.output_type = regex.sub(
                                template_type,
                                mapping.output_type,
                            )
                            new_item.is_input_optional = mapping.is_input_optional
                            new_item.is_output_optional = mapping.is_output_optional

                            # This will end up copying one more time than needed, but I couldn't think of a better way for now.
                            new_data_items.append(copy.deepcopy(new_item))

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
