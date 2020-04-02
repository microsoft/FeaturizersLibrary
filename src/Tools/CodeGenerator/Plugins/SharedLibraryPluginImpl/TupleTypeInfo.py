# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the TupleTypeInfo object"""

import os
import re
import textwrap

import six

import CommonEnvironment
from CommonEnvironment import Interface
from CommonEnvironment import StringHelpers

from Plugins.SharedLibraryPluginImpl.TypeInfo import TypeInfo
from Plugin import GetTemplateArgs

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class TupleTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"tuple\<(?P<types>.+)\>"))
    CppType                                 = Interface.DerivedProperty(None)

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

        assert create_type_info_func is not None

        super(TupleTypeInfo, self).__init__(*args, **kwargs)

        match = self.TypeName.match(member_type)
        assert match, member_type

        type_infos = []

        for type_ in GetTemplateArgs(match.group("types")):
            type_info = create_type_info_func(type_)
            assert type_info, type_

            type_infos.append(type_info)

        self._type_infos                    = type_infos
        self._create_type_info_func         = create_type_info_func

        # Override the CppType property with this type info
        self.CppType                        = "std::tuple<{}>".format(
            ", ".join([ type_info.CppType for type_info in self._type_infos ]),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetCppTemplateSuffix(self, template_mapping):
        # When a featurizer defines a tuple that has a template, it means
        # that some portion of the signature is templatized and not the entire
        # thing.
        templates = []

        for type_ in six.iterkeys(template_mapping):
            type_info = self._create_type_info_func(type_)
            assert type_info, type_

            templates.append(type_info.CppType)

        return ", ".join(templates)

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        if self.IsOptional:
            raise NotImplementedError("Optional tuples are not supported at this time")

        parameters = []
        validation_statements = []
        invocation_statements = []

        for index, type_info in enumerate(self._type_infos):
            result = type_info.GetInputInfo(
                "{}{}".format(arg_name, index),
                "{}",
            )

            parameters += result.Parameters
            invocation_statements.append(result.InvocationStatements)

            if result.ValidationStatements:
                validation_statements.append(result.ValidationStatements)

        return self.Result(
            parameters,
            "\n".join(validation_statements),
            invocation_template.format("InputType({})".format(", ".join(invocation_statements)))
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(
        self,
        arg_name,
        invocation_template,
        items_var_name=None,
    ):
        if self.IsOptional:
            raise NotImplementedError("Optional tuples are not supported at this time")

        if items_var_name is None:
            items_var_name = "{}_items".format(arg_name)
            append_items_parameter = True
        else:
            append_items_parameter = False

        parameters = []
        validation_statements = []
        invocation_statements = []
        invocation_tuples = []

        # Some types generate complicated buffers to store incoming data while
        # others simply provide the pointer and items. Handle both scenarios by
        # generating the content with an easily-recognizable string; extract
        # the content within the string for later use, and then remove it from
        # the invocation contents.

        for index, type_info in enumerate(self._type_infos):
            result = type_info.GetInputBufferInfo(
                "{}{}".format(arg_name, index),
                self._InvocationTemplate,
                items_var_name=items_var_name,
            )

            parameters += result.Parameters
            if result.ValidationStatements:
                validation_statements.append(result.ValidationStatements)

            item_invocation_statements, invocation_tuple = self._ExtractDecoratedInvocationStatements(result.InvocationStatements)

            invocation_tuples.append(invocation_tuple)
            invocation_statements.append(
                textwrap.dedent(
                    """\
                    // {}
                    {}

                    """,
                ).format(
                    type_info.CppType,
                    item_invocation_statements,
                ),
            )

        if append_items_parameter:
            parameters.append(self.Type("size_t", items_var_name))

        return self.Result(
            parameters,
            "\n".join(validation_statements),
            textwrap.dedent(
                """\
                {invocation_statements}

                std::vector<typename make_tuple_elements_const_references<{cpp_type}>::type> {arg_name}_buffer;

                {arg_name}_buffer.reserve({items_var_name});

                {ptrs}

                while({arg_name}_buffer.size() < {items_var_name}) {{
                    {arg_name}_buffer.emplace_back({emplace_args});
                    {ptrs_increment}
                }}

                {invoke}
                """,
            ).format(
                invocation_statements="".join(invocation_statements).rstrip(),
                cpp_type=self.CppType,
                arg_name=arg_name,
                items_var_name=items_var_name,
                ptrs="\n".join(
                    [
                        "auto * {arg_name}{index}_creation_ptr({value});".format(
                            arg_name=arg_name,
                            index=index,
                            value=invocation_tuple[0],
                        )
                        for index, invocation_tuple in enumerate(invocation_tuples)
                    ],
                ),
                emplace_args=", ".join(["*{}{}_creation_ptr".format(arg_name, index) for index in range(len(invocation_tuples))]),
                ptrs_increment=StringHelpers.LeftJustify(
                    "\n".join(["++{}{}_creation_ptr;".format(arg_name, index) for index in range(len(invocation_tuples))]),
                    4,
                ).rstrip(),
                invoke=invocation_template.format(
                    "{arg_name}_buffer.data(), {arg_name}_buffer.size()".format(
                        arg_name=arg_name,
                    ),
                ),
            ),
            input_buffer_type=self.Type(
                "std::vector<{}>".format(self.CppType),
                "{}_buffer".format(arg_name),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        suppress_pointer=False,
    ):
        if self.IsOptional:
            raise NotImplementedError("Optional tuples are not supported at this time")

        parameters = []
        validation_statements = []
        invocation_statements = []

        for index, type_info in enumerate(self._type_infos):
            result = type_info.GetOutputInfo(
                "{}{}".format(arg_name, index),
                result_name="{}{}".format(result_name, index),
                suppress_pointer=suppress_pointer,
            )

            parameters += result.Parameters
            if result.ValidationStatements:
                validation_statements.append(result.ValidationStatements)

            invocation_statements.append(
                textwrap.dedent(
                    """\
                    // [{index}] {type}

                    auto const & {result_name}{index}(std::get<{index}>({result_name}));

                    {statements}
                    """,
                ).format(
                    index=index,
                    type=type_info.CppType,
                    result_name=result_name,
                    statements=result.InvocationStatements.rstrip(),
                ),
            )

        return self.Result(
            parameters,
            "{}\n".format("\n".join(validation_statements).rstrip()),
            "\n".join(invocation_statements).rstrip(),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        if self.IsOptional:
            raise NotImplementedError("Optional tuples are not supported at this time")

        parameters = []
        validation_statements = []
        invocation_statements = []

        for index, type_info in enumerate(self._type_infos):
            result = type_info.GetDestroyOutputInfo("{}{}".format(arg_name, index))
            if result is None:
                continue

            parameters += result.Parameters
            if result.ValidationStatements:
                validation_statements.append(result.ValidationStatements)

            invocation_statements.append(
                textwrap.dedent(
                    """\
                    // [{index}] {type}
                    {statements}
                    """,
                ).format(
                    index=index,
                    type=type_info.CppType,
                    statements=result.InvocationStatements.rstrip(),
                ),
            )

        if not parameters:
            return None

        return self.Result(
            parameters,
            "{}\n".format("\n".join(validation_statements).rstrip()),
            "\n".join(invocation_statements).rstrip(),
        )
