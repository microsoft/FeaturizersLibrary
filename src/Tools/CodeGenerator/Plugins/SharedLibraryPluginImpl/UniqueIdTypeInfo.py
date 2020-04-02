# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the UniqueIdTypeInfo object"""

import os
import textwrap

import six

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class UniqueIdTypeInfo(TypeInfo):
    """\
    This class exists as a temporary placeholder for functionality that uniquely identifies
    a row; because this identity can be any combination of any type (and we don't have a way
    to represent this over a strongly-typed C interface), we require that all components
    of the identity are converted to a string - thus the C++ type of std::vector<std::string>.
    Longer term, we probably want to do something more intelligent with hashes to avoid the
    overhead of covering and marshalling strings.

    In theory, the functionality in this class could be written with vectors and strings.
    However, we want this code to be a drop-in replacement for a more efficient implementation
    in the future, and therefore don't want to burden all featurizers that unique a unique id
    with the range requirement (which is a requirement of a vector).
    """

    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("unique_id")
    CppType                                 = Interface.DerivedProperty("std::vector<std::string>")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        *args,
        member_type=None,
        create_type_info_func=None,
        **kwargs
    ):
        if member_type is None:
            return

        super(UniqueIdTypeInfo, self).__init__(*args, **kwargs)

        if self.IsOptional:
            raise Exception("UniqueId types cannot be optional")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        return self.Result(
            [
                self.Type("char const * const *", "{}_ptr".format(arg_name)),
                self.Type("size_t", "{}_items".format(arg_name)),
            ],
            textwrap.dedent(
                """
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");

                std::vector<std::string> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                while({name}_buffer.size() < {name}_items) {{
                    {name}_buffer.emplace_back(*{name}_ptr);
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
            ),
            invocation_template.format("{}_buffer".format(arg_name)),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(
        self,
        arg_name,
        invocation_template,
        items_var_name=None,
    ):
        parameters = [
            self.Type("char const * const * const *", "{}_ptrs".format(arg_name)),
            self.Type("size_t const *", "{}_ptr_items".format(arg_name)),
        ]

        if items_var_name is None:
            items_var_name = "{}_items".format(arg_name)
            parameters.append(self.Type("size_t", items_var_name))

        return self.Result(
            parameters,
            textwrap.dedent(
                """\
                if({name}_ptrs == nullptr) throw std::invalid_argument("'{name}_ptrs' is null");
                if({name}_ptr_items == nullptr) throw std::invalid_argument("'{name}_ptr_items' is null");
                if({items_var_name} == 0) throw std::invalid_argument("'{items_var_name}' is 0");

                std::vector<std::vector<std::string>> {name}_buffer;

                {name}_buffer.reserve({items_var_name});

                while({name}_buffer.size() < {items_var_name}) {{
                    if(*{name}_ptrs == nullptr) throw std::invalid_argument("'{name}_ptrs' element is null");
                    if(*{name}_ptr_items == 0) throw std::invalid_argument("'{name}_ptr_items' element is 0");

                    std::vector<std::string> this_buffer;

                    this_buffer.reserve(*{name}_ptr_items);

                    char const * const * strings_ptr(*{name}_ptrs);

                    while(this_buffer.size() < *{name}_ptr_items) {{
                        this_buffer.emplace_back(*strings_ptr);
                        ++strings_ptr;
                    }}

                    {name}_buffer.emplace_back(std::move(this_buffer));

                    ++{name}_ptrs;
                    ++{name}_ptr_items;
                }}
                """,
            ).format(
                name=arg_name,
                items_var_name=items_var_name,
            ),
            invocation_template.format(
                "{arg_name}_buffer.data(), {arg_name}_buffer.size()".format(
                    arg_name=arg_name,
                ),
            ),
            input_buffer_type=self.Type(
                "std::vector<{}>".format(self.CppType),
                "{}_buffer".format(arg_name),
            )
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        suppress_pointer=False,
    ):
        return self.Result(
            [
                self.Type("char ***", "{}_ptr".format(arg_name)),
                self.Type("size_t *", "{}_items".format(arg_name)),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == nullptr) throw std::invalid_argument("'{name}_items' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                // TODO: There are potential memory leaks if allocation fails
                *{name}_ptr = new char *[{result}.size()];

                char ** {name}_ptr_item(*{name}_ptr);

                for(std::string const & {result}_item : {result}) {{
                    // TODO: There are potential memory leaks if allocation fails
                    *{name}_ptr_item = new char[{result}_item.size() + 1];

                    std::copy({result}_item.begin(), {result}_item.end(), *{name}_ptr_item);
                    (*{name}_ptr_item)[{result}_item.size()] = 0;

                    ++{name}_ptr_item;
                }}

                *{name}_items = {result}.size();
                """,
            ).format(
                name=arg_name,
                result=result_name,
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        return self.Result(
            [
                self.Type("char const * const *", "{}_ptr".format(arg_name)),
                self.Type("size_t", "{}_items".format(arg_name)),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr && {name}_items != 0) throw std::invalid_argument("'{name}_items' is not 0");
                if({name}_ptr != nullptr && {name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                if({name}_ptr != nullptr) {{
                    char const * const * {name}_ptr_ptr({name}_ptr);
                    char const * const * const {name}_ptr_end({name}_ptr_ptr + {name}_items);

                    while({name}_ptr_ptr != {name}_ptr_end) {{
                        if(*{name}_ptr_ptr == nullptr) throw std::invalid_argument("{name}_ptr has an invalid element");

                        delete [] *{name}_ptr_ptr;

                        ++{name}_ptr_ptr;
                    }}

                    delete [] {name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
            ),
        )
