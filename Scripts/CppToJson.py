import sys
import json
import re

from CommonEnvironment import CommandLine

from DataPipelines.CppToJson import CppToJson
from DataPipelines.CppToJson.CheckPolicy import Policy

@CommandLine.EntryPoint
@CommandLine.Constraints(
    input=CommandLine.FilenameTypeInfo(
        arity="+",
    ),
)
def EntryPoint(
    input,
    treat_warnings_as_errors=False,
):
    inputs = input
    del input

    class UnsupportedException(Exception):
        pass

    def OnUnsupportedFunc(func, filename, line):
        # Display error
        if treat_warnings_as_errors:
            sys.stdout.write("Error: {} in {} <{}>\n".format(func, filename, line))
            raise UnsupportedException()
        else:
            sys.stdout.write("Warning: {} in {} <{}>\n".format(func, filename, line))

    # ----------------------------------------------------------------------

    try:
        file_dict = {}
        for file_name in inputs:
            file_dict[file_name] = CppToJson.ObtainFunctions(file_name, OnUnsupportedFunc, Policy)
        sys.stdout.write("{}\n".format(json.dumps(file_dict)))
    except UnsupportedException:
        return -1

    return 0

if __name__ == "__main__":
    try: sys.exit(CommandLine.Main())
    except KeyboardInterrupt: pass
