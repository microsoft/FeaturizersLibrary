import sys
import json
from DataPipelines import CppToJson

from CommonEnvironment import CommandLine

@CommandLine.EntryPoint
@CommandLine.Constraints(
    input_filename=CommandLine.FilenameTypeInfo(
        arity="+",
    ),
)
def EntryPoint(
    input_filename,
):
    file_dict = {}
    for file_name in input_filename:
        file_dict[file_name] = CppToJson.ObtainFunctions(file_name)
    sys.stdout.write("{}\n".format(json.dumps(file_dict)))
    return 0

if __name__ == "__main__":
    try: sys.exit(CommandLine.Main())
    except KeyboardInterrupt: pass