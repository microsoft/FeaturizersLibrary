import os
import re
import textwrap

from collections import OrderedDict

import six

import clang.cindex as cindex

import CommonEnvironment.FileSystem as fileSystem
import CommonEnvironment.CallOnExit as callOnExit
from CommonEnvironment.Shell.All import CurrentShell
import CommonEnvironment.Shell as CE_Shell

# ----------------------------------------------------------------------

def _FullName(node):
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

def _GetObjectType(node, SimpleVarType, FullVarType):
    '''
    This function will return the Object Type that this node refers to. It will return None if there were
    errors.
    '''

    valid_object_type = True
    has_move_constructor = False
    object_type = {}
    object_type['name'] = _FullName(node)
    object_type['var_names'] = []
    object_type['raw_var_types'] = []
    object_type['simple_var_types'] = []
    object_type['definition_line'] = node.location.line
    object_type['constructor_list'] = []

    # The way to see if this is a definition or not, is to see if 'node' has any children. 
    is_def = True

    for child in node.get_children():
        is_def = False
        if child.kind == cindex.CursorKind.CONSTRUCTOR:
            constructor = {}
            if child.is_move_constructor() and child.access_specifier == cindex.AccessSpecifier.PUBLIC:
                has_move_constructor = True
            elif child.is_copy_constructor() and child.access_specifier == cindex.AccessSpecifier.PUBLIC:
                token_list = []
                # If this is a public copy constructor, it needs to be deleted with "=delete" 
                for token in child.get_tokens():
                    token_list.append(token.spelling)
                if len(token_list) < 2 or token_list[-1] != 'delete' or token_list[-2] != '=':
                    valid_object_type = False

            constructor['arg_names'] = []
            constructor['raw_arg_types'] = []
            constructor['simple_arg_types'] = []
            constructor['definition_line'] = child.location.line
            for arg in child.get_arguments():
                constructor['arg_names'].append(arg.spelling)
                arg_type = FullVarType(arg.type.spelling)
                constructor['raw_arg_types'].append(arg_type)
                constructor['simple_arg_types'].append(SimpleVarType(arg_type))
            object_type['constructor_list'].append(constructor)
            
        elif child.kind == cindex.CursorKind.FIELD_DECL:
            object_type['var_names'].append(child.spelling)
            var_type = FullVarType(child.type.spelling)
            object_type['raw_var_types'].append(var_type)
            object_type['simple_var_types'].append(SimpleVarType(var_type))
            if child.access_specifier != cindex.AccessSpecifier.PUBLIC:
                valid_object_type = False
        elif child.kind == cindex.CursorKind.CXX_METHOD:
            '''
            TODO: This will change at some point, we will want to support 'operator=' as long as it is public and 
            a move operator. This is a small draft of what it will look like. For now, all functions are not
            supported.
        
            move_operator_arg_type = FullVarType(node.spelling) + " &&"
            if child.spelling == "operator=" and child.access_specifier == cindex.AccessSpecifier.PUBLIC:
                for arg in child.get_arguments():
                    if FullVarType(arg.type.spelling) != move_operator_arg_type:
                        valid_object_type = False
            else:
                valid_object_type = False
            '''

            valid_object_type = False
                
        elif child.kind != cindex.CursorKind.CXX_ACCESS_SPEC_DECL:
            valid_object_type = False

    if not is_def and (not valid_object_type or not has_move_constructor):
        return None
    elif not is_def:
        return object_type
    return {}

# ----------------------------------------------------------------------

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
    def _DeleteFile():
        if is_temp_file:
            os.remove(input_filename)

    # ----------------------------------------------------------------------

    with callOnExit.CallOnExit(_DeleteFile):
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
            '''
            Remove 'const', '*' and '&'
            '''
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

            def GetAlias():
                '''
                This function will process all 'typedef' and 'using' and it will map the underlying type to
                its definition. 
                '''
                alias = {}
                for child in cursor.get_children():
                    if (child.kind == cindex.CursorKind.TYPEDEF_DECL or child.kind == cindex.CursorKind.TYPE_ALIAS_DECL) and child.location.file.name == input_filename:
                        alias[child.spelling] = child.underlying_typedef_type.spelling
                return alias
            
            alias = GetAlias()
            
            alias_regex = re.compile(
                textwrap.dedent(
                    r'''(?#
                    Not a letter)(?<!\w)(?#
                    Keyword)(?P<keyword>{})(?#
                    Not a letter)(?!\w)(?#
                    )'''
                ).format("|".join([re.escape(key) for key in alias.keys()]))
            )

            struct_class_pattern = re.compile(
                textwrap.dedent(
                    r'''(?#
                    Not a letter)(?<!\w)(?#
                    Keyword with a space)(?P<keyword>struct\s|class\s)(?#
                    )'''
                )
            )

            # ----------------------------------------------------------------------
            pattern_words = re.compile(r"[\w']+")

            def FullVarType(types):
                '''
                This will undo all 'typedef' and 'using' by looking for the items in the 'alias' dict and substituting
                the corresponding definitions. It will also remove all occurences of the words 'struct' and 'class'.
                ''' 
                num_subs = True
                while num_subs and alias:
                    types, num_subs = re.subn(alias_regex, lambda k: alias[k.group(1)], types)

                types = struct_class_pattern.sub(r'', types)      
                return types
            # ----------------------------------------------------------------------

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

            object_type_list = []

            # ----------------------------------------------------------------------
            def Enumerate(node):
                if node.kind == cindex.CursorKind.NAMESPACE:
                    for child in node.get_children():
                        Enumerate(child)

                if (node.kind == cindex.CursorKind.STRUCT_DECL or node.kind == cindex.CursorKind.CLASS_DECL) and node.location.file.name == filename:
                    obj_type = _GetObjectType(node, SimpleVarType, FullVarType)

                    if obj_type:
                        object_type_list.append(obj_type)
                    elif obj_type is None:
                        # If None was returned, there was a problem with the ObjectType and it can't be processed
                        on_unsupported_func(_FullName(node), filename if (not is_temp_file or filename != input_filename) else None, node.location.line)


                if node.kind == cindex.CursorKind.FUNCTION_DECL and node.location.file.name == filename:
                    ret_type = FullVarType(node.result_type.spelling)
                    func = Funcs(_FullName(node), ret_type, SimpleVarType(ret_type))

                    for arg in node.get_arguments():
                        arg_type = FullVarType(arg.type.spelling)
                        func.AddVar(arg.displayname, arg_type, SimpleVarType(arg_type))

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
            
            function_list = [func.ToObject(key["declaration_line"], key["definition_line"]) for func, key in funcs_list.items()]

            # ----------------------------------------------------------------------
            def GetIncludeList():
                include_list = []
                for child in translation_unit.get_includes():
                    if child.location.file.name == filename:
                        include_list.append(os.path.realpath(os.path.join(filename, str(child.include))))
                return include_list

            # ----------------------------------------------------------------------
            def GetAcceptedObjList():
                accepted_obj_list = []

                for obj in object_type_list:
                    for curr_obj in object_type_list:
                        if curr_obj in accepted_obj_list:
                            break
                        valid_obj = True
                        for var_type in curr_obj['simple_var_types']:
                            if not TestAndVerify(var_type):
                                valid_obj = False
                                break
                        if valid_obj:
                            accepted_obj_list.append(curr_obj)
                return accepted_obj_list
            
            # ----------------------------------------------------------------------
            def GetAcceptedFuncList():
                accepted_func_list = []

                for func in function_list:
                    valid_func = True
                    for var_type in func['simple_var_types']:
                        if not TestAndVerify(var_type):
                            valid_func = False
                    if not TestAndVerify(func['simple_return_type']):
                        valid_func = False
                    if valid_func:
                        accepted_func_list.append(func)
                return accepted_func_list
            # ----------------------------------------------------------------------

            include_list = GetIncludeList()
            accepted_obj_list = GetAcceptedObjList()
            accepted_func_list = GetAcceptedFuncList()

            for obj in object_type_list:
                if obj not in accepted_obj_list:
                    on_unsupported_func(obj['name'], filename if (not is_temp_file or filename != input_filename) else None, obj['definition_line'])
            for func in function_list:
                if func not in accepted_func_list:
                    on_unsupported_func(func['func_name'], filename if (not is_temp_file or filename != input_filename) else None, func['definition_line'])


            # TODO: Needs to expose structs/classes that are on other files. For now, it will just say that its an invalid
            # function/struct/class.

            return {"function_list": accepted_func_list, "object_type_list": accepted_obj_list, "include_list": include_list }
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
