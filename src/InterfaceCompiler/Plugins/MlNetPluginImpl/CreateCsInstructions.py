# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Methods that help when creating instructions to compile the C# code"""

import os
import textwrap

import CommonEnvironment

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
def CreateCsInstructions(
    output_filename,
    output_name,
    output_dir,
    generate_header_func,
):
    output = [
        generate_header_func("# "),
        textwrap.dedent(
            """\

            # This is a temporary solution; longer-term, we will generate scripts that invoke the
            # commands below; there will be a batch file script for Windows and a bash script for
            # Ubuntu.

            # This command should be run from:
            #
            #       "{output_dir}"
            #

            csc -target:library -out:{output_name}MlNet.dll *.cs -reference:Microsoft.ML.Core.dll -reference:Microsoft.ML.Data.dll -reference:Microsoft.ML.DataView.dll -reference:netstandard.dll
            """,
        ).format(
            output_name=output_name,
            output_dir=output_dir,
        ),
    ]

    with open(output_filename, "w") as f:
        f.write("".join(output))

    return 0
