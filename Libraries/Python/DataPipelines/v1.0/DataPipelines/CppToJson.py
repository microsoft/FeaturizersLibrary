import os
import re

from collections import OrderedDict

import six

import clang.cindex as cindex
import CommonEnvironment.FileSystem as fileSystem
import CommonEnvironment.CallOnExit as callOnExit
from CommonEnvironment.Shell.All import CurrentShell
import CommonEnvironment.Shell as CE_Shell


def ObtainFunctions(
    input_filename,
    on_unsupported_func,
    policy,
    traverse_include_dependencies=True,
    include_regexes=None,
    exclude_regexes=None,
):
    '''
        This function will extract return value, name and parameters for every
        function given. input_filename can be a file name or a string that is the code
        itself.
        Return value:
            Returns a list of functions, every item in this list is a dictionary that
            has information about the function.
    '''

    # ----------------------------------------------------------------------
    def ProcessRegexes(regexes):
        if regexes is None:
            return []

        results = []
        for regex in regexes:
            if isinstance(regex, six.string_types):
                regex = re.compile(regex)

            results.append(regex)

        return results

    # ----------------------------------------------------------------------

    include_regexes = ProcessRegexes(include_regexes)
    exclude_regexes = ProcessRegexes(exclude_regexes)

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

        parse_queue = [input_filename]
        parsed = set()

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
        class Funcs:
            '''
            This class will hold a function's information, it provides __hash__ and __eq__ functions.
            It is needed so that its possible to have a dictionary using this class as a key, to keep
            track of the declaration and implementation lines and have fast lookup.
            '''
            def __init__(self, func_name, raw_return_type, simple_return_type):
                self._func_name = func_name
                self._raw_return_type = raw_return_type
                self._simple_return_type = simple_return_type
                self._var_names = []
                self._raw_var_types = []
                self._simple_var_types = []

            def AddVar(self, var_name, raw_var_type, simple_var_type):
                self._var_names.append(var_name)
                self._raw_var_types.append(raw_var_type)
                self._simple_var_types.append(simple_var_type)

            def __hash__(self):
                tuple_hash = (self._func_name, self._raw_return_type, self._simple_return_type,) + tuple(self._var_names) + tuple(self._raw_var_types) + tuple(self._simple_var_types)
                return hash(tuple_hash)

            def __eq__(self, other):
                return self.__hash__() == other.__hash__()

            def ToObject(self, declaration_line, definition_line):
                # Need to remove the prefix "_" from the dictionary
                new_dict = {key[1:] if (key and key.startswith("_")) else key :val for key, val in dict(self.__dict__).items()}

                new_dict['declaration_line'] = declaration_line
                new_dict['definition_line'] = definition_line
                return new_dict

        # ----------------------------------------------------------------------
        def QueueIncludeFilename(include_name):
            if not traverse_include_dependencies:
                return

            include_filename = os.path.realpath(os.path.join(os.path.basename(include_name), include_name))

            if any(regex.match(include_filename) for regex in exclude_regexes):
                return

            if include_regexes and not any(regex.match(include_filename) for regex in include_regexes):
                return

            if include_filename in parsed:
                return

            if include_filename in parse_queue:
                return

            parse_queue.append(include_filename)

        # ----------------------------------------------------------------------
        def ParseFile(filename):
            # TODO: Call `QueueIncludeFilename` with included filenames
            # TODO: Create tests that:
            #           parse includes
            #           validate include_regexes
            #           validate exclude_regexes
            #           use the correct name in on_unsupported

            funcs_list = {}

            translation_unit = index.parse(filename, args=args)

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

                if node.kind == cindex.CursorKind.FUNCTION_DECL and node.location.file.name == filename:
                    valid_func = True

                    # ----------------------------------------------------------------------
                    def FullName(node):
                        '''
                        This function will make the name of the function complete to include its namespace.
                        '''
                        name = node.spelling
                        parent = node.semantic_parent
                        while parent.kind != cindex.CursorKind.TRANSLATION_UNIT:
                            name = parent.spelling + "::" + name
                            parent = parent.semantic_parent
                        return name
                    # ----------------------------------------------------------------------
                    func = Funcs(FullName(node), node.result_type.spelling, SimpleVarType(node.result_type.spelling))

                    if not TestAndVerify(node.result_type.spelling):
                        valid_func = False

                    for arg in node.get_arguments():
                        func.AddVar(arg.displayname, arg.type.spelling, SimpleVarType(arg.type.spelling))

                        if not TestAndVerify(arg.type.spelling):
                            valid_func = False

                    if not valid_func:
                        on_unsupported_func(FullName(node), filename if (not is_temp_file or filename != input_filename) else None, node.location.line)
                    else:
                        if func not in funcs_list.keys():
                            funcs_list[func] = {'definition_line': None, 'declaration_line': None}
                        is_def = False
                        for child in node.get_children():
                            if child.kind == cindex.CursorKind.COMPOUND_STMT:
                                is_def = True

                        if is_def:
                            funcs_list[func]['definition_line'] = node.location.line
                        else:
                            funcs_list[func]['declaration_line'] = node.location.line

            # ----------------------------------------------------------------------
            for child in cursor.get_children():
                Enumerate(child)

            return [func.ToObject(key["declaration_line"], key["definition_line"]) for func, key in funcs_list.items()]

        # ----------------------------------------------------------------------

        all_results = OrderedDict()

        while parse_queue:
            filename = parse_queue.pop(0)
            parsed.add(filename)

            these_results = ParseFile(filename)

            # If the original file was a temp file, make the key None rather than
            # the name of the temporary file used.
            if not all_results and is_temp_file:
                filename = None

            all_results[filename] = these_results

        return all_results
