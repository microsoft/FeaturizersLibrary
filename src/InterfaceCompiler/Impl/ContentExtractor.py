# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

import os

from collections import OrderedDict

import six

import CommonEnvironment

from DataPipelines.CheckPolicy import Policy as CheckPolicy
from DataPipelines.CppToJson import ObtainFunctions

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
def ExtractContent(
    input_filenames,
    status_stream,
    include_regexes=None,
    exclude_regexes=None,
):
    all_results = OrderedDict()

    status_stream.write("Processing input files...")
    with status_stream.DoneManager() as status_dm:
        for input_index, input_filename in enumerate(input_filenames):
            status_dm.stream.write("'{}' ({} of {})...".format(input_filename, input_index + 1, len(input_filenames)))
            with status_dm.stream.DoneManager() as this_dm:
                # ----------------------------------------------------------------------
                def OnUnsupported(item, filename, line):
                    this_dm.stream.write("{} ({} <{}>)".format(item, filename, line))

                # ----------------------------------------------------------------------

                these_results = ObtainFunctions(
                    input_filename,
                    OnUnsupported,
                    CheckPolicy,
                    include_regexes=include_regexes,
                    exclude_regexes=exclude_regexes,
                )

                for k, v in six.iteritems(these_results):
                    if k not in all_results:
                        all_results[k] = v

        return all_results
