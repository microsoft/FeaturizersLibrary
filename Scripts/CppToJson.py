import sys
import json
import re

from DataPipelines import CppToJson
from CommonEnvironment import CommandLine
from DataPipelines.CheckPolicy import Policy

@CommandLine.EntryPoint
@CommandLine.Constraints(
    input_filename=CommandLine.FilenameTypeInfo(
        arity="+",
    ),
)
def EntryPoint(
    input_filename,
    treat_warnings_as_errors=False,
):
    class UnsupportedException(Exception):
        pass

    def OnUnsupportedFunc(func, line):
        # Display error
        if treat_warnings_as_errors:
            sys.stdout.write("Error: Unsupported function '{}' on line {}\n".format(func, line))
            raise UnsupportedException()
        else:
            sys.stdout.write("Warning: Unsupported function '{}' on line {}\n".format(func, line))

    # ----------------------------------------------------------------------

    try:
        file_dict = {}
        for file_name in input_filename:
            file_dict[file_name] = CppToJson.ObtainFunctions(file_name, OnUnsupportedFunc, Policy)
        sys.stdout.write("{}\n".format(json.dumps(file_dict)))
    except UnsupportedException:
        return -1

    return 0

if __name__ == "__main__":
    try: sys.exit(CommandLine.Main())
    except KeyboardInterrupt: pass