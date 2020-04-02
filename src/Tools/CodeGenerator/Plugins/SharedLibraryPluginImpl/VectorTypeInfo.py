# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the VectorTypeInfo object"""

import os
import re
import textwrap

import six

import CommonEnvironment
from CommonEnvironment import Interface
from CommonEnvironment import StringHelpers

from Plugins.SharedLibraryPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class VectorTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"vector\<(?P<type>.+)\>"))
    CppType                                 = Interface.DerivedProperty(None)

    # ----------------------------------------------------------------------
    # |
    # |  Public Types
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

        assert create_type_info_func is not None

        super(VectorTypeInfo, self).__init__(*args, **kwargs)

        if self.IsOptional:
            raise NotImplementedError("Optional vectors are not supported at this time")

        match = self.TypeName.match(member_type)
        assert match, member_type

        the_type = match.group("type")

        type_info = create_type_info_func(the_type)
        assert type_info, the_type

        # The content is expressed by a range of pointers.
        self._type_info             = type_info
        self.CppType                = "std::tuple<{type} const *, {type} const *>".format(
            type=self._type_info.CppType,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        result = self._type_info.GetInputBufferInfo(arg_name, self._InvocationTemplate)
        assert result.InputBufferType is not None, self._type_info

        invocation_statements, invocation_tuple = self._ExtractDecoratedInvocationStatements(result.InvocationStatements)
        assert len(invocation_tuple) == 2, invocation_tuple

        return self.Result(
            result.Parameters,
            result.ValidationStatements,
            "{}{}".format(
                "{}\n\n".format(invocation_statements.rstrip()) if invocation_statements else "",
                invocation_template.format(
                    "std::make_tuple({ptr}, {ptr} + {size})".format(
                        ptr=invocation_tuple[0],
                        size=invocation_tuple[1],
                    ),
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(
        self,
        arg_name,
        invocation_template,
        items_var_name=None,
    ):
        # Don't reuse the items var (if it exists)
        items_var_name = "{}_items".format(arg_name)

        result = self._type_info.GetInputBufferInfo(
            "{}_item".format(arg_name),
            self._InvocationTemplate,
            items_var_name=items_var_name,
        )
        assert result.InputBufferType is not None, self._type_info

        input_parameters = [self.Type("{} const *".format(p.Type), "{}_ptr".format(p.Name)) for p in result.Parameters]

        invocation_statements, invocation_tuple = self._ExtractDecoratedInvocationStatements(result.InvocationStatements)
        assert not invocation_statements, invocation_statements

        # If the input buffer type is a pointer, it means that we don't
        # have to transform the input prior to passing it on. If it is not
        # a pointer, transformation is required.
        if result.InputBufferType.Type.endswith("*"):
            # No transformation is required
            buffer_type = self.Type(
                "std::vector<std::tuple<{type}, {type}>>".format(
                    type=result.InputBufferType.Type,
                ),
                "{}_buffer".format(arg_name),
            )

            buffer_assignment = "{name}_buffer.emplace_back({invocation_ptr}, {invocation_ptr} + {invocation_size});".format(
                name=arg_name,
                invocation_ptr=invocation_tuple[0],
                invocation_size=invocation_tuple[1],
            )

            validation_suffix  = ""
        else:
            # Transformation is required
            buffer_type = self.Type(
                "std::vector<{}>".format(result.InputBufferType.Type),
                "{}_temp_buffer".format(arg_name),
            )

            buffer_assignment = "{buffer_name}.emplace_back(std::move({item}));".format(
                buffer_name=buffer_type.Name,
                item=result.InputBufferType.Name,
            )

            # We have a vector of the concrete types, but need to pass a vector of tuples
            # to the featurizer itself. Create a new vector that has that info.
            validation_suffix = textwrap.dedent(
                """\
                std::vector<std::tuple<{type}, {type}>> {name}_buffer;

                {name}_buffer.reserve({temp_buffer}.size();

                for(auto const & {temp_buffer}_item : {temp_buffer})
                    {name}_buffer.emplace_back({temp_buffer}_item.cbegin(), {temp_buffer}_item.cend());
                """,
            ).format(
                name=arg_name,
                type="typename {}::const_iterator".format(result.InputBufferType.Type),
                temp_buffer=buffer_type.Name,
            )

        validation_statements = textwrap.dedent(
            """\
            {parameter_validation}
            if({items_var_name} == 0) throw std::invalid_argument("'{items_var_name}' is 0");

            {buffer_type} {buffer_name};

            {buffer_name}.reserve({items_var_name});

            while({buffer_name}.size() < {items_var_name}) {{
                {references}

                {validation_statements}
                {invocation_statements}

                {buffer_assignment}

                {increment_pointers}
            }}{validation_suffix}
            """,
        ).format(
            parameter_validation="\n".join(
                [
                    """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                        name=p.Name,
                    )
                    for p in input_parameters
                ]
            ),
            name=arg_name,
            items_var_name=items_var_name,
            buffer_type=buffer_type.Type,
            buffer_name=buffer_type.Name,
            references=StringHelpers.LeftJustify(
                "\n".join(
                    [
                        "{type} const &{name}(*{name}_ptr);".format(
                            type=p.Type,
                            name=p.Name,
                        )
                        for p in result.Parameters
                    ]
                ),
                4,
            ),
            validation_statements=StringHelpers.LeftJustify(
                result.ValidationStatements.rstrip(),
                4,
            ),
            invocation_statements=StringHelpers.LeftJustify(
                invocation_statements.rstrip(),
                4,
            ),
            buffer_assignment=buffer_assignment,
            increment_pointers=StringHelpers.LeftJustify(
                "\n".join(["++{};".format(p.Name) for p in input_parameters]),
                4,
            ),
            validation_suffix="" if not validation_suffix else "\n\n{}".format(validation_suffix),
        )

        return self.Result(
            input_parameters + [self.Type("size_t", items_var_name)],
            validation_statements,
            invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
                ),
            ),
            input_buffer_type=self.Type(buffer_type, "{}_buffer".format(arg_name)),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        suppress_pointer=False,
    ):
        result = self._type_info.GetOutputInfo(
            "{}_item".format(arg_name),
            result_name="{}_item".format(result_name),
        )

        input_parameters = [self.Type("{}*".format(p.Type), "{}_ptr".format(p.Name)) for p in result.Parameters]

        if len(result.Parameters) == 1 and result.Parameters[0].Type == "bool *":
            # We can't take a reference to bools within a vector, as the values are stored as bits rather than
            # bool types.
            for_loop = "for(bool {result_name}_item : {result_name})".format(
                result_name=result_name,
            )

        else:
            for_loop = "for(auto const & {result_name}_item : {result_name})".format(
                result_name=result_name,
            )

        return self.Result(
            input_parameters + [self.Type("size_t *", "{}_items".format(arg_name))],
            textwrap.dedent(
                """\
                {statements}
                if({name}_items == nullptr) throw std::invalid_argument("'{name}_items' is null");
                """,
            ).format(
                statements="\n".join(
                    [
                        """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                            name=p.Name,
                        )
                        for p in input_parameters
                    ]
                ),
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                if({result_name}.empty()) {{
                    {empty_allocations}
                }}
                else {{
                    // TODO: There are potential memory leaks if allocation fails
                    {allocations}

                    {initial_assignments}

                    {for_loop} {{
                        {validations}

                        {statements}

                        {ptr_increments}
                    }}
                }}

                *{name}_items = {result_name}.size();
                """,
            ).format(
                name=arg_name,
                result_name=result_name,
                empty_allocations=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            "*{}_ptr = nullptr;".format(p.Name)
                            for p in result.Parameters
                        ]
                    ),
                    4,
                ),
                allocations=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            "*{name}_ptr = new {type}[{result_name}.size()];".format(
                                name=p.Name,
                                type=self._StripPointer(p.Type),
                                result_name=result_name,
                            )
                            for p in result.Parameters
                        ]
                    ),
                    4,
                ),
                initial_assignments=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            "{type} {name}(*{name}_ptr);".format(
                                name=p.Name,
                                type=p.Type,
                            )
                            for p in result.Parameters
                        ]
                    ),
                    4,
                ),
                for_loop=for_loop,
                validations=StringHelpers.LeftJustify(result.ValidationStatements, 8).rstrip(),
                statements=StringHelpers.LeftJustify(result.InvocationStatements, 8).rstrip(),
                ptr_increments=StringHelpers.LeftJustify(
                    "\n".join(["++{};".format(p.Name) for p in result.Parameters]),
                    8,
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        result = self.GetOutputInfo(
            arg_name,
        )

        input_parameters = [self.Type(self._StripPointer(p.Type), p.Name) for p in result.Parameters]

        # Create the destroy statements
        destroy_result = self._type_info.GetDestroyOutputInfo("{}_destroy_item".format(arg_name))
        if destroy_result is not None:
            assert input_parameters[-1].Type == "size_t", input_parameters[-1].Type
            assert input_parameters[-1].Name.endswith("_items"), input_parameters[-1].Name
            pointer_parameters = input_parameters[:-1]

            assert len(destroy_result.Parameters) == len(result.Parameters) - 1

            destroy_statements = textwrap.dedent(
                """\
                {variable_statements}

                while({name}_items--) {{
                    {assignment_statements}

                    {delete_statements}
                    {increment_statements}
                }}
                """,
            ).format(
                name=arg_name,
                variable_statements="\n".join(
                    [
                        "{type} this_{name}({name});".format(
                            type=p.Type,
                            name=p.Name,
                        )
                        for p in pointer_parameters
                    ],
                ),
                assignment_statements=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            """{destroy_type} const & {destroy_name}(*this_{parameter_name});""".format(
                                destroy_type=destroy_p.Type,
                                destroy_name=destroy_p.Name,
                                parameter_name=standard_p.Name,
                            )
                            for destroy_p, standard_p in zip(destroy_result.Parameters, pointer_parameters)
                        ]
                    ),
                    4,
                ),
                delete_statements=StringHelpers.LeftJustify(
                    textwrap.dedent(
                        """\
                        {}

                        {}
                        """,
                    ).format(
                        destroy_result.ValidationStatements.rstrip() if destroy_result.ValidationStatements else "// No validation statements",
                        destroy_result.InvocationStatements.rstrip(),
                    ),
                    4,
                ),
                increment_statements=StringHelpers.LeftJustify(
                    "\n".join([ "++this_{};".format(p.Name) for p in pointer_parameters]),
                    4,
                ),
            )
        else:
            destroy_statements = "// No destroy statements"

        return self.Result(
            input_parameters,
            textwrap.dedent(
                """\
                if({initial_ptr_name} != nullptr && {name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");
                if({initial_ptr_name} == nullptr && {name}_items != 0) throw std::invalid_argument("'{name}_items' is not 0");
                {ptr_validations}
                """,
            ).format(
                initial_ptr_name=input_parameters[0].Name,
                name=arg_name,
                ptr_validations="\n".join(
                    [
                        """if(bool({name}) != bool({initial_ptr_name})) throw std::invalid_argument("'{name}' is not internally consistent");""".format(
                            initial_ptr_name=input_parameters[0].Name,
                            name=p.Name,
                        )
                        for p in input_parameters[1:]
                    ]
                ),
            ),
            textwrap.dedent(
                """\
                if({initial_ptr_name} != nullptr) {{
                    {statements}

                    {delete_ptrs}
                }}
                """,
            ).format(
                initial_ptr_name=input_parameters[0].Name,
                statements=StringHelpers.LeftJustify(destroy_statements, 4).rstrip(),
                delete_ptrs=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            "delete [] {};".format(p.Name)
                            for p in input_parameters if p.Type.endswith("*")
                        ]
                    ),
                    4,
                ),
            ),
        )

    # ----------------------------------------------------------------------
    # ----------------------------------------------------------------------
    # ----------------------------------------------------------------------
    @staticmethod
    def _StripPointer(value):
        assert value.endswith("*"), value
        return value[:-1].rstrip()
