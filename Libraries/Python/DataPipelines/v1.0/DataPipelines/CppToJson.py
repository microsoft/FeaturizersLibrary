import os
import re
import clang.cindex as cindex
import CommonEnvironment.FileSystem as fileSystem
import CommonEnvironment.CallOnExit as callOnExit
from CommonEnvironment.Shell.All import CurrentShell
import CommonEnvironment.Shell as CE_Shell


def ObtainFunctions(input_filename, on_unsupported_func, policy):
    '''
        This function will extract return value, name and parameters for every
        function given. input_filename can be a file name or a string that is the code
        itself.
        Return value:
            Returns a list of functions, every item in this list is a dictionary that
            has information about the function.
    '''
    is_temp_file = False
    # Since clang can only parse from a file, if we are given a string we need to create
    #   a new temp file and put the string inside.
    if not fileSystem.IsFilename(input_filename):
        is_temp_file = True
        file_content = input_filename
        input_filename = CE_Shell.Shell.CreateTempFilename(suffix=".cpp")
        with open(input_filename, "w") as file_pointer:
            file_pointer.write(file_content)
    # ----------------------------------------------------------------------
    def DeleteFile():
        if is_temp_file:
            os.remove(input_filename)
    # ----------------------------------------------------------------------

    with callOnExit.CallOnExit(DeleteFile):
        funcs_list = []

        pattern_const = re.compile("^const ")
        pattern_star  = re.compile(r"( \*)*\**")
        pattern_amper = re.compile("( &)*&*")

        # ----------------------------------------------------------------------
        def SimpleVarType(name):
            name = re.sub(pattern_const,  "", name)
            name = re.sub(pattern_star,  "", name)
            name = re.sub(pattern_amper,  "", name)
            return name

        # ----------------------------------------------------------------------

        index = cindex.Index.create()
        args = []

        # On Windows, clang recognizes the INCLUDE and LIB environment variables, but
        # on Linux it does not. Recognize the INCLUDE var on Linux.
        if CurrentShell.CategoryName == "Linux":
            include_vars = [value for value in os.getenv("INCLUDE").split(":") if value.strip()]

            # In the past, we used the GCC repository which would prepopulate the INCLUDE environment
            # variable with standard includes. However, that repo had issues when attempting to link
            # compile binaries and has been temporarily disabled. Unfortunately, this code needs that
            # populated environment variable to function correctly in order to tokenize input.
            #
            # For now, add those includes here. When Clang's dependency on GCC is restored in the future,
            # we can remove this explicit step.
            include_vars.append("/usr/lib/gcc/x86_64-linux-gnu/7/include")

            args = ['-I{}'.format(include_var) for include_var in include_vars]

        translation_unit = index.parse(input_filename, args=args)

        diagnostics = list(translation_unit.diagnostics)
        if diagnostics:
            raise Exception("\n".join([str(diag) for diag in diagnostics]))

        cursor = translation_unit.cursor

        # ----------------------------------------------------------------------
        def Enumerate(node):

            if node.kind == cindex.CursorKind.NAMESPACE:
                for child in node.get_children():
                    Enumerate(child)

            # ----------------------------------------------------------------------

            pattern_words = re.compile(r"[\w']+")

            def TestAndVerify(types):
                '''
                This is an early version of TestAndVerify that checks if a type should be accepted or not.
                It will find all words in the type and check them against a policy. This will be adapted as we
                get more information about what is supported and what is not.
                '''
                type_list = re.findall(pattern_words, types)

                for var_type in type_list:
                    if not policy(var_type):
                        return False
                return True

            # ----------------------------------------------------------------------


            if node.kind == cindex.CursorKind.FUNCTION_DECL and node.location.file.name == input_filename:
                valid_func = True
                func = {}
                func["func_name"] = node.spelling

                if not TestAndVerify(node.result_type.spelling):
                    valid_func = False

                func["raw_return_type"] = node.result_type.spelling
                func["simple_return_type"] = SimpleVarType(node.result_type.spelling)
                func["var_names"] = []
                func["raw_var_types"] = []
                func["simple_var_types"] = []
                for arg in node.get_arguments():
                    func["var_names"].append(arg.displayname)

                    if not TestAndVerify(arg.type.spelling):
                        valid_func = False

                    func["raw_var_types"].append(arg.type.spelling)
                    func["simple_var_types"].append(SimpleVarType(arg.type.spelling))

                if not valid_func:
                    on_unsupported_func(node.spelling, node.location.line)
                else:
                    funcs_list.append(func)

        # ----------------------------------------------------------------------
        for child in cursor.get_children():
            Enumerate(child)

        return funcs_list
    # ----------------------------------------------------------------------
