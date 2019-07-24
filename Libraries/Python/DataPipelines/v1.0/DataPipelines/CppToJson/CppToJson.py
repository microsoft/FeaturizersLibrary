import os
import re
import textwrap

from collections import OrderedDict

import clang.cindex as cindex

import CommonEnvironment.FileSystem as fileSystem
import CommonEnvironment.CallOnExit as callOnExit
from CommonEnvironment.Shell.All import CurrentShell
import CommonEnvironment.Shell as CE_Shell

from DataPipelines.CppToJson.Impl.Struct import Struct
from DataPipelines.CppToJson.Impl.Constructor import Constructor
from DataPipelines.CppToJson.Impl.Function import Function

# ----------------------------------------------------------------------
def ObtainFunctions(
    input_filename,
    on_unsupported,
    policy_func,
):
    """
    This function will extract return value, name and parameters for every
    function given. input_filename can be a file name or a string that is the code
    itself.
    Return value:
        Returns a list of functions, every item in this list is a dictionary that
        has information about the function.
    """

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
    def TestAndVerify(types, verify_struct_func):
        return policy_func(types, verify_struct_func)

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

        pattern_const = re.compile(
            textwrap.dedent(
                r"""(?#
                Not a letter)(?<!\w)(?#
                Keyword)(?P<keyword>const)(?#
                Not a letter)(?!\w)(?#
                )"""
            )
        )
        
        pattern_amper = re.compile("&*(& )*")

        # ----------------------------------------------------------------------
        def SimpleVarType(name):
            """
            Remove 'const' and '&'
            """

            name = re.sub(pattern_const,  "", name)
            name = re.sub(pattern_amper,  "", name)
            return name.strip()

        # ----------------------------------------------------------------------
        def ParseFile(filename):
            """
            Clang opens all files that are included in 'filename' at the same time. Only the functions on 
            'filename' are processed, but all structs are processed, because one of the functions
            in 'filename' might need to use it. The ones that are not in 'filename' and are not used are not
            exported.
            """

            translation_unit = index.parse(filename, args=args + ['-std=c++17'])

            diagnostics = list(translation_unit.diagnostics)
            if diagnostics:
                raise Exception("\n".join([str(diag) for diag in diagnostics]))

            cursor = translation_unit.cursor

           # ----------------------------------------------------------------------
            def GetAlias(node, prefix):
                """
                This function will process all 'typedef' and 'using' and it will map the underlying type to
                its definition.
                """
                alias = {}
                
                if node.kind == cindex.CursorKind.NAMESPACE:
                    for child in node.get_children():
                        ret = GetAlias(child, prefix + node.spelling + "::")
                        for a, b in ret.items():
                            assert prefix + a not in alias.keys()
                            alias[prefix + a] = b
                
                if (node.kind == cindex.CursorKind.TYPEDEF_DECL or node.kind == cindex.CursorKind.TYPE_ALIAS_DECL):
                    alias[prefix + node.spelling] = node.underlying_typedef_type.spelling

                return alias

            # ----------------------------------------------------------------------
            alias = {}
            for node in cursor.get_children():
                for before_type, after_type in GetAlias(node, "").items():
                    assert before_type not in alias.keys()
                    '''
                    If TestAndVerify with no structs (lambda function is always False) is True, then it means
                    that before_type is already an accepted type, so we don't want to extend it any further.
                    '''
                    if not TestAndVerify(before_type, lambda type: False):
                        alias[before_type] = after_type
                        

            alias_regex = re.compile(
                textwrap.dedent(
                    r"""(?#
                    Not a letter or a ':')(?<![:\w])(?#
                    Keyword)(?P<keyword>{})(?#
                    Not a letter or a ':')(?![:\w])(?#
                    )"""
                ).format("|".join([re.escape(key) for key in alias]))
            )

            struct_pattern = re.compile(
                textwrap.dedent(
                    r"""(?#
                    Not a letter)(?<!\w)(?#
                    Keyword with a space)(?P<keyword>struct\s)(?#
                    )"""
                )
            )

            # ----------------------------------------------------------------------
            def FullVarType(types):
                """
                This will undo all 'typedef' and 'using' by looking for the items in the 'alias' dict and substituting
                the corresponding definitions. It will also remove all occurences of the words 'struct'.
                """
                num_subs = True
                while num_subs and alias:
                    types, num_subs = re.subn(alias_regex, lambda k: alias[k.group(1)], types)

                types = struct_pattern.sub(r'', types)
                return types

            # ----------------------------------------------------------------------

            struct_list = []
            function_dict = {}

            # ----------------------------------------------------------------------
            def EnumerateStruct(node):
                if node.kind == cindex.CursorKind.NAMESPACE:
                    for child in node.get_children():
                        EnumerateStruct(child)

                if node.kind == cindex.CursorKind.STRUCT_DECL:
                    this_struct = _GetStruct(node, SimpleVarType, FullVarType)

                    if this_struct:
                        struct_list.append(this_struct)

            # ----------------------------------------------------------------------
            def EnumerateFuncs(node):
                if node.kind == cindex.CursorKind.NAMESPACE:
                    for child in node.get_children():
                        EnumerateFuncs(child)

                if node.kind == cindex.CursorKind.FUNCTION_DECL and node.location.file.name == filename:
                    ret_type = FullVarType(node.result_type.spelling)
                    
                    arg_list = []
                    for arg in node.get_arguments():
                        arg_type = FullVarType(arg.type.spelling)
                        arg_list.append(arg_type)

                    # There is the need for arg_list to be a tuple here, because this will be the key
                    # to the dictionary of functions, and tuple are hashable unlike lists.
                    func_key = (_FullName(node), ret_type, tuple(arg_list))

                    is_def = False
                    for child in node.get_children():
                        if child.kind == cindex.CursorKind.COMPOUND_STMT:
                            is_def = True
                    
                    if func_key not in function_dict.keys():
                        variable_info = []
                        for arg in node.get_arguments():
                            arg_type = FullVarType(arg.type.spelling)
                            variable_info.append((arg.displayname, arg_type, SimpleVarType(arg_type)))

                        # Create the instance of the function
                        function_dict[func_key] = Function(_FullName(node), ret_type, SimpleVarType(ret_type), variable_info, node.location.line)
                    
                    if is_def:
                        function_dict[func_key].definition_line = node.location.line

            # ----------------------------------------------------------------------

            # EnumerateStruct needs to be separated from EnumerateFuncs because of constructors that might be out
            # of the function.
            for child in cursor.get_children():
                EnumerateStruct(child)

            for child in cursor.get_children():
                EnumerateFuncs(child)

            # ----------------------------------------------------------------------
            def GetIncludeList(filename):
                include_list = []
                for child in translation_unit.get_includes():
                    include_list.append((os.path.realpath(str(child.location.file.name)) if (not is_temp_file or child.location.file.name != input_filename) else None, os.path.realpath(os.path.join(filename, str(child.include)))))
                return include_list

            # ----------------------------------------------------------------------

            include_list = GetIncludeList(filename)
            
            function_list = [func for func in function_dict.values()]
            return {"function_list": function_list, "struct_list": struct_list, "include_list": include_list}

        clean_results = OrderedDict()
        
        # ----------------------------------------------------------------------
        def InitializeCleanResults(filename, raw_includes):
            clean_results[filename] = Results()
            for include_tuple in raw_includes:
                name, include = include_tuple
                if name == filename:
                    clean_results[filename].include_list.append(include)

        # ----------------------------------------------------------------------

        filename = os.path.realpath(input_filename)
        these_results = ParseFile(filename)

        # If the original file was a temp file, make the key None rather than
        # the name of the temporary file used.
        if not clean_results and is_temp_file:
            filename = None

        if not clean_results:
            InitializeCleanResults(filename, these_results["include_list"])

        needed_struct_list = []
        invalid_struct_list = []

        # ----------------------------------------------------------------------
        def GetStruct(this_struct_name):
            """
            Get Struct from its name.
            """
            for this_struct in these_results["struct_list"]:
                if this_struct.Name == this_struct_name:
                    return this_struct
            return None

        # ----------------------------------------------------------------------
        def VerifyStruct(struct_name):
            """
            Check all var types in this Struct, this Struct is valid if they are all valid. There is an assumption that
            this function will only be called for an Struct that is required. If this Struct depends on another Struct,
            that means that the other Struct is also required.
            """
            this_struct = GetStruct(struct_name)
            if this_struct is None or this_struct in invalid_struct_list:
                return False
            if this_struct in needed_struct_list:
                return True
            invalid_reasons = []
            for var_type, var_name in zip(this_struct.EnumerateSimpleVarTypes(), this_struct.EnumerateVarNames()):
                if GetStruct(var_type) != this_struct and not TestAndVerify(var_type, VerifyStruct):
                    invalid_reasons.append("\t- Invalid var {} of type {}.".format(var_name, var_type))

            for constructor in this_struct.constructor_list:
                for arg_type in constructor.EnumerateSimpleVarTypes():
                    if GetStruct(arg_type) != this_struct and not TestAndVerify(arg_type, VerifyStruct):
                        invalid_reasons.append("\t- Invalid type {} on constructor argument.".format(arg_type))

            for parent_struct in this_struct.base_structs:
                if not VerifyStruct(parent_struct):
                    invalid_reasons.append("\t- Invalid base struct {}.".format(parent_struct))

            if not this_struct.has_move_constructor:
                invalid_reasons.append("\t- Struct doesn't have a move constructor.")
            if this_struct.has_copy_constructor:
                invalid_reasons.append("\t- Struct has a copy constructor.")
            if this_struct.has_private:
                invalid_reasons.append("\t- Struct has a private variable or inherits from a private struct.")
            if this_struct.has_other:
                invalid_reasons.append("\t- Struct has an unsupported definition.")

            if invalid_reasons:
                on_unsupported(textwrap.dedent(
                    """\
                        The struct {} is not supported:
                        {}
                    """
                ).format(this_struct.Name, "\n".join(invalid_reasons)),
                this_struct.Filename if (not is_temp_file or this_struct.Filename != input_filename) else None,
                this_struct.DefinitionLine
                )
                invalid_struct_list.append(this_struct)
                return False
            needed_struct_list.append(this_struct)
            return True

        # ----------------------------------------------------------------------
        def VerifyFunction(func, filename):
            """
            A function is valid if all var types are valid.
            """
            invalid_reasons = []
            for var_type, var_name in zip(func.EnumerateSimpleVarTypes(), func.EnumerateVarNames()):
                if not TestAndVerify(var_type, lambda struct: False):
                    invalid_reasons.append("\t- Invalid argument {} of type {}.".format(var_name, var_type))

            return_type = func.SimpleReturnType
            if not TestAndVerify(return_type, VerifyStruct):
                invalid_reasons.append("\t- Invalid return type {}.".format(return_type))

            if invalid_reasons:
                on_unsupported(textwrap.dedent(
                    """\
                        The function {} is not supported:
                        {}
                    """
                ).format(func.Name, "\n".join(invalid_reasons)),
                filename if (not is_temp_file or filename != input_filename) else None,
                func.definition_line
                )
                return False
            return True

        # ----------------------------------------------------------------------

        for func in these_results["function_list"]:
            if VerifyFunction(func, filename):
                clean_results[filename].function_list.append(func.ToDict())

        # Add required Struct to the clean_results list.
        for this_struct in needed_struct_list:
            this_file_name = this_struct.Filename

            if is_temp_file:
                this_file_name = None
            if this_file_name not in clean_results:
                InitializeCleanResults(this_file_name, these_results["include_list"])
            clean_results[this_file_name].struct_list.append(this_struct.ToDict())

        return dict([(filename, result.ToDict()) for  filename, result in clean_results.items()])

# ----------------------------------------------------------------------
# |
# |  Private Types
# |
# ----------------------------------------------------------------------
class Results(object):
    """Stores final versions of Includes, Functions and Struct objects"""

    # ----------------------------------------------------------------------
    def __init__(
        self,
        function_list=None,
        struct_list=None,
        include_list=None,
    ):
        self.function_list                  = function_list or []
        self.struct_list                    = struct_list or []
        self.include_list                   = include_list or []

    # ----------------------------------------------------------------------
    def ToDict(self):
        new_dict = {}

        new_dict["function_list"]           = self.function_list
        new_dict["struct_list"]             = self.struct_list
        new_dict["include_list"]            = self.include_list

        return new_dict


# ----------------------------------------------------------------------
# |
# |  Private Methods
# |
# ----------------------------------------------------------------------
def _FullName(node):
    """
    This function will make the name of the function complete to include its namespace.
    """
    name = node.spelling
    parent = node.semantic_parent
    while parent.kind != cindex.CursorKind.TRANSLATION_UNIT:
        name = parent.spelling + "::" + name
        parent = parent.semantic_parent
    return name

# ----------------------------------------------------------------------

def _GetStruct(node, simple_var_type_func, full_var_type_func):
    """
    This function will return the Object Type that this node refers to. It will return None if there were
    errors.
    """
    struct_pattern = re.compile(
        textwrap.dedent(
            r"""(?#
            Not a letter)(?<!\w)(?#
            Keyword with a space)(?P<keyword>struct\s)(?#
            )"""
        )
    )
    is_def = True
    # There are a few kinds that are supported, even though they are not directly exposed.
    accepted_kinds = [cindex.CursorKind.CXX_ACCESS_SPEC_DECL]

    # ----------------------------------------------------------------------
    def DeleteDefault(node, speficier):
        """
        This function will receive a node and a specifier (default or deleted), and check if the
        node has the specifier in question.
        """
        token_list = []
        for token in node.get_tokens():
            token_list.append(token.spelling)
        return len(token_list) >= 2 and token_list[-1] == speficier and token_list[-2] == '='

    # ----------------------------------------------------------------------

    struct_vars = []
    for child in node.get_children():
        if child.kind == cindex.CursorKind.FIELD_DECL:
            var_type = full_var_type_func(child.type.spelling)
            struct_vars.append((child.spelling, var_type, simple_var_type_func(var_type)))

    this_struct = Struct(_FullName(node), node.location.line, os.path.realpath(node.location.file.name), struct_vars)

    for child in node.get_children():
        # The way to see if this is a definition or not, is to see if 'node' has any children.
        is_def = False
        if child.kind == cindex.CursorKind.CONSTRUCTOR:
            # If this constructor ends in "=delete", ignore it.
            if DeleteDefault(child, "delete"):
                continue

            constructor_args = []
            for arg in child.get_arguments():
                arg_type = full_var_type_func(arg.type.spelling)
                constructor_args.append((arg.spelling, arg_type, simple_var_type_func(arg_type)))

            constructor = Constructor(child.location.line, constructor_args)

            this_struct.constructor_list.append(constructor)

            if child.is_move_constructor() and child.access_specifier == cindex.AccessSpecifier.PUBLIC:
                this_struct.has_move_constructor = True
                if DeleteDefault(child, "default"):
                    # If this is a default move constructor, there wont be a variable name for the
                    # argument in the function, so I create one when I return the dictionary representation.
                    assert len(constructor.VariableInfo) == 1

            elif child.is_copy_constructor() and child.access_specifier == cindex.AccessSpecifier.PUBLIC:
                # No public copy constructors are allowed.
                this_struct.has_copy_constructor = True

        elif child.kind == cindex.CursorKind.FIELD_DECL:
            if child.access_specifier != cindex.AccessSpecifier.PUBLIC:
                this_struct.has_private = True

        elif child.kind == cindex.CursorKind.CXX_METHOD:
            # If this method ends in "=delete", ignore it.
            if DeleteDefault(child, "delete"):
                continue

            # 'operator=' is supported as long as it is public and a move operator.
            move_operator_arg_type = full_var_type_func(node.spelling) + " &&"
            if child.spelling == "operator=" and child.access_specifier == cindex.AccessSpecifier.PUBLIC:
                for arg in child.get_arguments():
                    # Check the arguments to verify that this is a move operator.
                    if full_var_type_func(arg.type.spelling) != move_operator_arg_type:
                        this_struct.has_other = True
            else:
                # No other functions besides move operators are allowed.
                this_struct.has_other = True

        elif child.kind == cindex.CursorKind.CXX_BASE_SPECIFIER:
            if child.access_specifier != cindex.AccessSpecifier.PUBLIC:
                this_struct.has_private = True
            struct_name = child.spelling
            struct_name = struct_pattern.sub(r'', struct_name)

            this_struct.base_structs.append(struct_name.strip())

        elif child.kind not in accepted_kinds:
            this_struct.has_other = True

    if not is_def:
        return this_struct

    return None
