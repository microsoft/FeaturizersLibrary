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
                "std::move({})",
            )

            parameters += result.Parameters
            invocation_statements.append(result.InvocationStatements)

            if result.ValidationStatements:
                validation_statements.append(result.ValidationStatements)

        return self.Result(
            parameters,
            "\n".join(validation_statements),
            invocation_template.format("std::make_tuple({})".format(", ".join(invocation_statements)))
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, invocation_template):
        if self.IsOptional:
            raise NotImplementedError("Optional tuples are not supported at this time")

        parameters = []
        validation_statements = []
        invocation_statements = []
        invocation_tuples = []

        # Some types generate complicated buffers to store incoming data while
        # others simply provide the pointer and items. Handle both scenarios by
        # generating the content with an easily-recognizable string; extract
        # the content within the string for later use, and then remove it from
        # the invocation contents.

        # TODO: This needs some work
        invocation_statement_regex = re.compile(
            r"\*\*\*\*\*(?P<content>.+)\*\*\*\*\*",
            re.DOTALL | re.MULTILINE,
        )

        for index, type_info in enumerate(self._type_infos):
            result = type_info.GetInputBufferInfo(
                "{}{}".format(arg_name, index),
                "*****{}*****",
            )

            parameters += result.Parameters
            if result.ValidationStatements:
                validation_statements.append(result.ValidationStatements)

            match = invocation_statement_regex.search(result.InvocationStatements)
            assert match, result.InvocationStatements

            invocation_tuple = [item.strip() for item in match.group("content").split(",")]
            assert len(invocation_tuple) == 2, match.group("content")

            invocation_tuples.append(invocation_tuple)
            invocation_statements.append(
                textwrap.dedent(
                    """\
                    // {}
                    {}

                    """,
                ).format(
                    type_info.CppType,
                    result.InvocationStatements[:match.start()].rstrip(),
                ),
            )

        for index in range(1, len(self._type_infos)):
            validation_statements.append(
                textwrap.dedent(
                    """\
                    if({arg_name}{index}_items != {arg_name}0_items) throw std::invalid_argument("'{arg_name}{index}_items' != '{arg_name}0_items'");
                    """,
                ).format(
                    arg_name=arg_name,
                    index=index,
                ),
            )

        # TODO: Needs number of items
        return self.Result(
            parameters,
            "\n".join(validation_statements),
            textwrap.dedent(
                """\
                {invocation_statements}

                std::vector<{cpp_type}> {arg_name}_buffer;

                {arg_name}_buffer.reserve(input0_items);

                {ptrs}

                while({arg_name}_buffer.size() < input0_items) {{
                    {arg_name}_buffer.emplace_back({emplace_args});
                    {ptrs_increment}
                }}

                {invoke}
                """,
            ).format(
                invocation_statements="".join(invocation_statements).rstrip(),
                cpp_type=self.CppType,
                arg_name=arg_name,
                first_element_buffer=invocation_tuples[0][0],
                first_element_size=invocation_tuples[0][1],
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
                emplace_args=", ".join(["std::move(*{}{}_creation_ptr)".format(arg_name, index) for index in range(len(invocation_tuples))]),
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
        raise NotImplementedError("Tuples are only used during input; use custom structures for output")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        raise NotImplementedError("Tuples are only used during input; use custom structures for output")
