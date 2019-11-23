# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Methods that help when creating a c++ wrapper"""

import os
import textwrap

import CommonEnvironment

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# <unused argument> pylint: disable = W0613
def CreateCppWrapper(output_filename, data, generate_header_func):
    output = [generate_header_func("// ")]
    output.append(_GeneratePreProcessorCommands())

    for value in data.values():
        for include in value["include_list"]:
            output.insert(1, "#include \"{}\"\n".format(include.split(os.sep)[-1]))

        for function in value["function_list"]:

            function_name = function["func_name"]
            var_names = function["var_names"]
            raw_var_types = function["raw_var_types"]
            return_type = function["simple_return_type"]
            simple_var_types = function["simple_var_types"]

            output.append(_GenerateFunctionDeclaration(return_type, function_name, raw_var_types))
            output.append(_GenerateExportSignature(return_type, function_name, var_names, simple_var_types))
    
    with open(output_filename, "w") as f:
        f.write("".join(output))

    return 0

def _GenerateFunctionDeclaration(return_type, function_name, raw_var_types):
    code = ["\n{return_type} {function_name}(".format(
        return_type = return_type,
        function_name = function_name
    )]

    length = len(raw_var_types)
    for index in range(length):
        if index == length - 1:
            code.append("{type}".format(
                type = raw_var_types[index]
                )
            )
        else:
            code.append("{type}, ".format(
                type = raw_var_types[index]
                )
            )
    code.append(");")

    return "".join(code)

def _GeneratePreProcessorCommands():
    code = textwrap.dedent(
        """\

        #if defined(_MSC_VER)
        #   define EXPORT __declspec(dllexport)
        #elif defined(__GNUC__)
        #   define EXPORT __attribute__((visibility("default")))
        #else
        #   error unsupported!
        #endif
        """
    )
    return code

def _GenerateExportSignature(return_type, function_name, var_names, simple_var_types):
    code = [textwrap.dedent(
        """
        extern "C" {{
            EXPORT {return_type} {function_name}Proxy("""
        ).format(
            return_type = return_type,
            function_name = function_name
        )
    ]

    length = len(simple_var_types)
    for index in range(length):
        code.append("{0} {1}{2}".format(
            simple_var_types[index],
            var_names[index],
            ", " if index != length - 1 else "")
        )
        
    code.append(textwrap.dedent(
        """\
        ) {{
                return {function_name}("""
        ).format(
            function_name = function_name
        )
    )
    for index in range(length):
        code.append("{0}{1}".format(
            var_names[index],
            ", " if index != length - 1 else "")
        )
    code.append(textwrap.dedent(
        """\
        );
            }
        }
        """
        )
    )
    return "".join(code)