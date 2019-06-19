# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Methods that help when creating a c++ wrapper"""

import os

import CommonEnvironment

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# <unused argument> pylint: disable = W0613
def CreateCppWrapper(output_filename, data, generate_header_func):
    output = [generate_header_func("// ")]

    output.append("// TODO: Append more output here\n")

    with open(output_filename, "w") as f:
        f.write("".join(output))

    return 0
