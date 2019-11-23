import re
import textwrap

def Policy(var_type, verify_struct_func):
    # Basic Types that don't require recursion
    int_types = ["std::int8_t", "std::int16_t", "std::int32_t", "std::int64_t","std::uint8_t", "std::uint16_t", "std::uint32_t", "std::uint64_t"]
    number_types = ["float16", "float32", "float64", "complex64", "complex128", "bfloat16"]
    boolean_types = ["bool"]
    string_types = ["std::string"]

    basic_types = int_types + number_types + boolean_types + string_types

    single_special = ["std::vector", "std::optional"]

    double_special = ["std::array", "std::map"]

    function_special = ["std::function"]

    modifier_types = ["&", "const"]

    # Step 1: Remove modifiers
    pattern_modifier = re.compile(
        textwrap.dedent(
            r"""(?#
            Not a letter)(?<!\w)(?#
            Keyword)(?P<keyword>{})(?#
            Not a letter)(?!\w)(?#
            )"""
        ).format("|".join([re.escape(modifier_type) for modifier_type in modifier_types]))
    )

    var_type = re.sub(pattern_modifier,  "", var_type)


    # Step 2: Check for invalid characters (*)
    pattern_star  = re.compile(r"\*")

    if pattern_star.search(var_type):
        return False

    # Step 3: Get all words in the var_type
    pattern_words = re.compile(
        textwrap.dedent(
            r"""(?#
            Keyword)[[\w:]+(?#
            Or closing parenthesis)|\)(?#
            Or opening parenthesis)|\((?#
            )"""
        )
    )

    type_list = re.findall(pattern_words, var_type)

    # Step 4: Associate how many template arguments each type has
    # To add a new accepted type, simply add it to this dictionary associating it with how many template arguments it takes
    type_to_template_count = {}

    for basic_type in basic_types:
        type_to_template_count[basic_type] = 0
    
    for a_single_special in single_special:
        type_to_template_count[a_single_special] = 1

    for a_double_special in double_special:
        type_to_template_count[a_double_special] = 2 

    # Step 5: Special case of functions
    function_special_regex = re.compile(
        textwrap.dedent(
            r"""(?#
            Keyword)(?P<keyword>{})(?#
            )"""
        ).format("|".join([re.escape(a_function_special) for a_function_special in function_special]))
    )

    # ----------------------------------------------------------------------
    def VerifyType(index, parent_index):
        """
        This function will verify if a type is acceptable or not. Index refers
        to the current type that is being looked at, and parent_index is the type 
        that made the call to the current type It will return True/False
        meaning if the string was accepted or not, and also return the index it stopped looking at.
        """
        if type_list[index] in type_to_template_count:
            valid, new_index = True, index + 1
            counter = 0
            while valid and counter < type_to_template_count[type_list[index]]:
                valid, new_index = VerifyType(new_index, index)
                counter = counter + 1
            return valid, new_index

        if function_special_regex.match(type_list[index]):
            # This is a special case, there is going to be one type, then opening
            # parentesis, then a list of types, then closing parentesis.
            valid, new_index = VerifyType(index + 1, index)

            # I know the next 'word' is going to be an open parentesis, I'll skip it.
            new_index = new_index + 1

            while valid and type_list[new_index] != ")":
                valid, new_index = VerifyType(new_index, index)

            if valid:
                return True, new_index + 1
        
        # This is a special case, since the only time that 'char' or a number are acceptable is 
        # when its preciding 'std::array'
        if type_list[parent_index] == "std::array" and (type_list[index] == "char" or type_list[index].isdigit()):
            return True, index + 1

        # Check to see if this is a valid Struct.
        if verify_struct_func(type_list[index]):
            return True, index + 1

        return False, index + 1

    valid, ending_index = VerifyType(0, 0)

    if ending_index != len(type_list):
        return False
    return valid
