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
    TypeName                                = Interface.DerivedProperty(re.compile(r"vector\<(?P<type>\S+)\>"))
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
        assert not invocation_statements, invocation_statements

        return self.Result(
            result.Parameters,
            result.ValidationStatements,
            invocation_template.format(
                "std::make_tuple({ptr}, {ptr} + {size})".format(
                    ptr=invocation_tuple[0],
                    size=invocation_tuple[1],
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, invocation_template):
        result = self._type_info.GetInputBufferInfo("{}_item".format(arg_name), self._InvocationTemplate)
        assert result.InputBufferType is not None, self._type_info

        invocation_statements, invocation_tuple = self._ExtractDecoratedInvocationStatements(result.InvocationStatements)
        assert not invocation_statements, invocation_statements

        # Update the parameters to account for another level of indirection
        input_parameters = [self.Type("{} const *".format(p.Type), "{}_ptr".format(p.Name)) for p in result.Parameters]

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
            if({name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");

            {buffer_type} {buffer_name};

            {buffer_name}.reserve({name}_items);

            while({buffer_name}.size() < {name}_items) {{
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
            input_parameters + [self.Type("size_t", "{}_items".format(arg_name))],
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
                // TODO: There are potential memory leaks if allocation fails
                {allocations}
                *{name}_items = {result_name}.size();

                {initial_assignments}

                {for_loop} {{
                    {validations}
                    {statements}
                    {ptr_increments}
                }}
                """,
            ).format(
                name=arg_name,
                result_name=result_name,
                allocations="\n".join(
                    [
                        "*{name}_ptr = new {type}[{result_name}.size()];".format(
                            name=p.Name,
                            type=self._StripPointer(p.Type),
                            result_name=result_name,
                        )
                        for p in result.Parameters
                    ]
                ),
                initial_assignments="\n".join(
                    [
                        "{type} {name}(*{name}_ptr);".format(
                            name=p.Name,
                            type=p.Type,
                        )
                        for p in result.Parameters
                    ]
                ),
                for_loop=for_loop,
                validations=StringHelpers.LeftJustify(result.ValidationStatements, 4),
                statements=StringHelpers.LeftJustify(result.InvocationStatements, 4),
                ptr_increments=StringHelpers.LeftJustify(
                    "\n".join(["++{};".format(p.Name) for p in result.Parameters]),
                    4,
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        # Use the input info as a way to get arguments
        input_item_info = self.GetInputInfo(arg_name, "")

        # The expected convention is that all arguments are pointers except
        # one (probably the last) that is the number of items.
        pointer_parameters = []
        size_parameter = None

        for p in input_item_info.Parameters:
            if p.Type.endswith("*"):
                pointer_parameters.append(p)
                continue

            assert size_parameter is None
            assert p.Type == "size_t", p.Type

            size_parameter = p

        assert pointer_parameters
        assert size_parameter is not None

        if len(pointer_parameters) == 1:
            validation_statements = textwrap.dedent(
                """\
                if({ptr} == nullptr && {size} != 0) throw std::invalid_argument("'{size}' is not 0");
                """,
            ).format(
                ptr=pointer_parameters[0].Name,
                size=size_parameter.Name,
            )
        else:
            validation_statements = textwrap.dedent(
                """\
                if({first_ptr} == nullptr) {{
                    {verify_null}
                    if({size} != 0) throw std::invalid_argument("'{size}' is not 0");
                }}
                else {{
                    {verify_not_null}
                    if({size} == 0) throw std::invalid_argument("'{size}' is 0");
                """,
            ).format(
                first_ptr=pointer_parameters[0].Name,
                size=size_parameter.Name,
                verify_null=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            """if({ptr} != nullptr) throw std::invalid_argument("'{ptr}' is not null");""".format(
                                ptr=p.Name,
                            )
                            for p in pointer_parameters[1:]
                        ]
                    ),
                    4,
                ),
                verify_not_null=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            """if({ptr} == nullptr) throw std::invalid_argument("'{ptr}' is null");""".format(
                                ptr=p.Name,
                            )
                            for p in pointer_parameters[1:]
                        ]
                    ),
                    4,
                ),
            )

        # Determine if individual items need to be destroyed
        destroy_item_info = self._type_info.GetDestroyOutputInfo(
            arg_name="{}_item".format(arg_name),
        )

        if destroy_item_info is not None:
            assert len(destroy_item_info.Parameters) == len(pointer_parameters), (destroy_item_info.Parameters, pointer_parameters)

            destroy_statements = textwrap.dedent(
                """\
                {declarations}

                for(size_t ctr=0; ctr < {size_name}; ++ctr) {{
                    {references}

                    {statements}

                    {increment}
                }}
                """,
            ).format(
                declarations="\n".join(
                    [
                        "{type} {name}_item({name});".format(
                            type=p.Type,
                            name=p.Name,
                        )
                        for p in pointer_parameters
                    ]
                ),
                size_name=size_parameter.Name,
                references=StringHelpers.LeftJustify(
                    "\n".join(
                        [
                            "{} {}(*{}_item);".format(
                                destroy_param.Type,
                                destroy_param.Name,
                                pointer_param.Name,
                            )
                            for destroy_param, pointer_param in zip(destroy_item_info.Parameters, pointer_parameters)
                        ]
                    ),
                    4,
                ),
                statements=StringHelpers.LeftJustify(destroy_item_info.InvocationStatements.rstrip(), 4),
                increment=StringHelpers.LeftJustify("\n".join(["++{}_item;".format(p.Name) for p in pointer_parameters]), 4),
            )

        else:
            destroy_statements = ""

        return self.Result(
            input_item_info.Parameters,
            textwrap.dedent(
                """\
                {validation_statements}

                if({size} == 0)
                    return true;
                """,
            ).format(
                validation_statements=validation_statements,
                size=size_parameter.Name,
            ),
            textwrap.dedent(
                """\
                {destroy_statements}
                {statements}
                """,
            ).format(
                destroy_statements=destroy_statements,
                statements="\n".join(
                    [
                        "delete [] {};".format(p.Name)
                        for p in pointer_parameters
                    ]
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
