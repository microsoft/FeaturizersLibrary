# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Tool that generates code using in the Featurizer ecosystem."""

import contextlib
import copy
import hashlib
import importlib
import itertools
import os
import re
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
from CommonEnvironment.Shell.All import CurrentShell
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
SUPPORTED_TYPES                             = set(
    [
        "int8",
        "int16",
        "int32",
        "int64",
        "uint8",
        "uint16",
        "uint32",
        "uint64",
        "float",
        "double",
        "string",
        "bool",
        "datetime",
        re.compile(r"matrix\<\S+\>"),
        re.compile(r"vector\<\S+\>"),
        re.compile(r"sparse_vector\<\S+\>"),
        re.compile(r"single_value_sparse_vector\<\S+\>"),
    ],
)

# ----------------------------------------------------------------------
@CommandLine.EntryPoint(
    include=CommandLine.EntryPoint.Parameter(
        "Regular expression specifying the name of featurizers to include",
    ),
    exclude=CommandLine.EntryPoint.Parameter(
        "Regular expression specifying the name of featurizers to exclude",
    ),
)
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
            raise CommandLine.UsageException(
                "'{}' is not a valid regular expression".format(value),
            )

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
            # ----------------------------------------------------------------------
            def NormalizeEnum(enum):
                # Simplify the provided enum structure be creating an ordered dictionary with names and values
                if hasattr(enum, "integer_values"):
                    if len(enum.integer_values) != len(enum.values):
                        raise Exception("When integer values are specified for an enum, the number of integers must match the number of enums ('{}', '{}')".format(enum.values, enum.integer_values))

                    integer_values = enum.integer_values
                    del enum.integer_values
                else:
                    integer_values = list(range(enum.starting_index, enum.starting_index + len(enum.values)))

                del enum.starting_index

                assert len(enum.values) == len(integer_values), (enum.values, integer_values)
                enum.values = OrderedDict([(k, v) for k, v in zip(enum.values, integer_values)])

                return enum

            # ----------------------------------------------------------------------

            # Get the global custom structs
            global_custom_struct_names = set()
            global_custom_structs = []

            for item in data.custom_structs:
                if item.name in global_custom_struct_names:
                    raise Exception("The custom struct '{}' has already been defined".format(item.name))

                global_custom_struct_names.add(item.name)
                global_custom_structs.append(item)

            # Get the global custom enums
            global_custom_enum_names = set()
            global_custom_enums = []

            for item in data.custom_enums:
                if item.name in global_custom_enum_names:
                    raise Exception("The custom enum '{}' has already been defined".format(item.name))

                global_custom_enum_names.add(item.name)
                global_custom_enums.append(NormalizeEnum(item))

            # If there are templates at play, preprocess the content and expand the values
            new_data = []

            for item in data.featurizers:
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
                    this_dm.stream.write(
                        "'{}' has been explicitly excluded.\n".format(item.name),
                    )
                    nonlocals.skipped += 1

                    continue

                if includes and not any(include.match(item.name) for include in includes):
                    this_dm.stream.write(
                        "'{}' has not been included.\n".format(item.name),
                    )
                    nonlocals.skipped += 1

                    continue

                for enum in getattr(item, "custom_enums", []):
                    NormalizeEnum(enum)

                if not hasattr(item, "templates"):
                    assert item.type_mappings

                    for mapping in item.type_mappings:
                        new_item = copy.deepcopy(item)

                        new_item.input_type = mapping.input_type
                        new_item.output_type = mapping.output_type

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
                            if any(gcs for gcs in global_custom_structs if gcs.name == custom_struct.name):
                                raise Exception("The custom structure '{}' in '{}' has already been defined as a global custom struct.\n".format(custom_struct.name, item.name))

                            for member in custom_struct.members:
                                member.type = regex.sub(template_type, member.type)

                        for custom_enum in getattr(new_item, "custom_enums", []):
                            if any(gce for gce in global_custom_enums if gce.name == custom_enum.name):
                                raise Exception("The custom enum '{}' in '{}' has already been defined as a global custom enum.\n".format(custom_enum.name, item.name))

                            custom_enum.underlying_type = regex.sub(template_type, custom_enum.underlying_type)

                        for mapping in item.type_mappings:
                            # TODO: sub all types (for example: map<K, V>
                            if not regex.search(mapping.input_type) and not regex.search(mapping.output_type):
                                continue

                            new_item.input_type = regex.sub(
                                template_type,
                                mapping.input_type,
                            )
                            new_item.output_type = regex.sub(
                                template_type,
                                mapping.output_type,
                            )

                            # This will end up copying one more time than needed, but I couldn't think of a better way for now.
                            new_data_items.append(copy.deepcopy(new_item))

                new_data.append(new_data_items)

            data = new_data

        # Validate parameters
        dm.stream.write("Validating types...")
        with dm.stream.DoneManager():
            for items in data:
                for item in items:
                    # ----------------------------------------------------------------------
                    def IsSupportedType(typename):
                        for potential_type in SUPPORTED_TYPES:
                            if hasattr(potential_type, "match"):
                                if potential_type.match(typename):
                                    return True

                            elif typename == potential_type:
                                return True

                        return False

                    # ----------------------------------------------------------------------
                    def IsCustomStructType(typename):
                        return any(
                            custom_struct
                            for custom_struct in itertools.chain(getattr(item, "custom_structs", []), global_custom_structs)
                            if custom_struct.name == typename
                        )

                    # ----------------------------------------------------------------------
                    def IsCustomEnumType(typename):
                        return any(
                            custom_enum
                            for custom_enum in itertools.chain(getattr(item, "custom_enums", []), global_custom_enums)
                            if custom_enum.name == typename
                        )

                    # ----------------------------------------------------------------------

                    input_type = item.input_type
                    if input_type.endswith("?"):
                        input_type = input_type[:-1]

                    if (
                        not IsSupportedType(input_type)
                        and not IsCustomStructType(input_type)
                        and not IsCustomEnumType(input_type)
                    ):
                        raise Exception(
                            "The input type '{}' defined in '{}' is not valid.".format(
                                input_type,
                                item.name,
                            ),
                        ) from None

                    output_type = item.output_type
                    if output_type.endswith("?"):
                        output_type = output_type[:-1]

                    if (
                        not IsSupportedType(output_type)
                        and not IsCustomStructType(output_type)
                        and not IsCustomEnumType(output_type)
                    ):
                        raise Exception(
                            "The output type '{}' defined in '{}' is not valid.".format(
                                output_type,
                                item.name,
                            ),
                        ) from None

        dm.stream.write("Generating content...")
        with dm.stream.DoneManager() as this_dm:
            FileSystem.MakeDirs(output_dir)

            # ----------------------------------------------------------------------
            def CalcHash(filename):
                hash = hashlib.sha256()

                with open(filename, "rb") as f:
                    while True:
                        block = f.read(4096)
                        if not block:
                            break

                        hash.update(block)

                return hash.digest()

            # ----------------------------------------------------------------------
            @contextlib.contextmanager
            def FileWriter(filename, mode):
                """\
                Method that writes to a temporary location and only copies to the intended
                destination if there are changes. This prevents full rebuilds (which are
                triggered based on timestamps) on files that haven't changed.
                """

                temp_filename = CurrentShell.CreateTempFilename()
                with open(temp_filename, mode) as f:
                    yield f

                if not os.path.isfile(filename) or CalcHash(temp_filename) != CalcHash(filename):
                    FileSystem.RemoveFile(filename)
                    shutil.move(temp_filename, filename)
                else:
                    FileSystem.RemoveFile(temp_filename)

            # ----------------------------------------------------------------------

            this_dm.result = plugin.Generate(
                FileWriter,
                global_custom_structs,
                global_custom_enums,
                data,
                output_dir,
                this_dm.stream,
            )
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
