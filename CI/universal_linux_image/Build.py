# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Tools to create and publish a docker image that can be used to create universal linux binaries."""

import os
import sys

import six

import CommonEnvironment
from CommonEnvironment import BuildImpl
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import CommandLine
from CommonEnvironment import Process
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

DEFAULT_IMAGE_NAME                          = "featurizersbuild/universal_linux"

# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    tag=CommandLine.StringTypeInfo(
        arity="*",
    ),
    output_stream=None,
)
def Build(
    image_name=DEFAULT_IMAGE_NAME,
    tag=None,
    output_stream=sys.stdout,
    verbose=False,
):
    """Creates a docker image"""

    tags = tag
    del tag

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        dm.stream.write("Building docker image...")
        with dm.stream.DoneManager(
            line_prefix="      ",
            suffix="\n",
        ) as this_dm:
            prev_dir = os.getcwd()

            os.chdir(_script_dir)
            with CallOnExit(lambda: os.chdir(prev_dir)):
                this_dm.result = Process.Execute('docker build --tag {} .'.format(image_name), this_dm.stream)
                if this_dm.result != 0:
                    return this_dm.result

        if tags:
            dm.stream.write("Applying tags...")
            with dm.stream.DoneManager() as tag_dm:
                for index, tag in enumerate(tags):
                    tag_dm.stream.write("'{}' ({} of {})...".format(tag, index + 1, len(tags)))
                    with tag_dm.stream.DoneManager() as this_dm:
                        this_dm.result, output = Process.Execute(
                            'docker tag {image_name} {image_name}:{tag}'.format(
                                image_name=image_name,
                                tag=tag,
                            ),
                        )

                        if this_dm.result != 0:
                            this_dm.stream.write(output)
                            return this_dm.result

        return dm.result


# ----------------------------------------------------------------------
@CommandLine.EntryPoint
@CommandLine.Constraints(
    tag=CommandLine.StringTypeInfo(
        arity="*",
    ),
    output_stream=None,
)
def Clean(
    image_name=DEFAULT_IMAGE_NAME,
    tag=None,
    all=False,
    output_stream=sys.stdout,
):
    """Cleans previously built content"""

    tags = tag
    del tag

    if all and tags:
        raise CommandLine.UsageException("Individual tag values should not be provided when 'all' is provided on the command line")

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        if all:
            image_id = _GetImageId(image_name, dm)

            command_line = 'docker image rm --force {}'.format(image_id)
        else:
            command_line = 'docker image rm {}'.format(image_name)

        dm.stream.write("Removing docker image(s)...")
        with dm.stream.DoneManager() as this_dm:
            this_dm.result, output = Process.Execute(command_line)
            if this_dm.result != 0:
                # If the user provided tags, it may be that they have already deleted this
                # image, in which case this is not an error.
                this_dm.stream.write(output)

                if tags:
                    this_dm.result = 0
                else:
                    return this_dm.result

        if tags:
            dm.stream.write("Removing tags...")
            with dm.stream.DoneManager() as tag_dm:
                for index, tag in enumerate(tags):
                    tag_dm.stream.write("'{}' ({} of {})...".format(tag, index + 1, len(tags)))
                    with tag_dm.stream.DoneManager() as this_dm:
                        this_dm.result, output = Process.Execute('docker image rm {}:{}'.format(image_name, tag))
                        if this_dm.result != 0:
                            this_dm.stream.write(output)
                            return this_dm.result

        return dm.result


# ----------------------------------------------------------------------
@CommandLine.EntryPoint(
    registry_name=CommandLine.EntryPoint.Parameter("Name of the container registry to push to (e.g. 'featurizersbuild.azurecr.io')"),
)
@CommandLine.Constraints(
    registry_name=CommandLine.StringTypeInfo(),
    tag=CommandLine.StringTypeInfo(
        arity="?",
    ),
    output_stream=None,
)
def Publish(
    registry_name,
    image_name=DEFAULT_IMAGE_NAME,
    tag=None,
    output_stream=sys.stdout,
):
    """Publishes previously built content to a docker registry"""

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        image_id = _GetImageId(
            image_name,
            dm,
            tag=tag,
        )

        new_image_name = "{}/{}".format(registry_name, image_name.split("/")[-1])
        if new_image_name is None:
            assert dm.result != 0
            return dm.result

        dm.stream.write("Renaming image...")
        with dm.stream.DoneManager() as this_dm:
            this_dm.result, output = Process.Execute(
                'docker tag {} {}{}'.format(
                    image_id,
                    new_image_name,
                    ":{}".format(tag) if tag else "",
                ),
            )

            if this_dm.result != 0:
                this_dm.stream.write(output)
                return this_dm.result

        dm.stream.write("Pushing image...")
        with dm.stream.DoneManager(
            line_prefix="      ",
        ) as this_dm:
            this_dm.result = Process.Execute('docker push {}'.format(new_image_name), this_dm.stream)
            if this_dm.result != 0:
                return this_dm.result

        return dm.result


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def _GetImageId(
    image_name,
    dm,
    tag=None,
):
    dm.stream.write("Retrieving image id...")
    with dm.stream.DoneManager() as this_dm:
        this_dm.result, output = Process.Execute('docker images {}{} --quiet'.format(image_name, ":{}".format(tag) if tag else ""))
        if this_dm.result != 0:
            this_dm.stream.write(output)
            return None

        lines = output.strip().split("\n")
        return lines[0]


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(
            BuildImpl.Main(
                BuildImpl.Configuration(
                    "universal_linux_build",
                    requires_output_dir=False,
                ),
            ),
        )
    except KeyboardInterrupt:
        pass
