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

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

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

        super(VectorTypeInfo, self).__init__(*args, **kwargs)

        match = self.TypeName.match(member_type)
        assert match, member_type

        the_type = match.group("type")

        type_info = create_type_info_func(the_type)
        assert type_info, the_type

        # The content is expressed by a range of pointers
        self._type_info             = type_info
        self.CppType                = "std::tuple<{type} const *, {type} const *>".format(
            type=self._type_info.CppType,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        return self._type_info.GetTransformInputBufferArgs(
            input_name=input_name,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputBufferArgs(
        self,
        input_name='input',
    ):
        raise NotImplementedError("Not implemented yet")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        invocation_template,
        result_name="result",
    ):
        buffer_name = "{}_buffer".format(result_name)

        if self._type_info.TypeName == "bool":
            # vector<bool> doesn't support emplace_back on older compliers
            item_invocation_template = "{}.push_back({{}});".format(buffer_name)
        else:
            item_invocation_template = "{}.emplace_back({{}});".format(buffer_name)

        result = self._type_info.GetOutputInfo(
            invocation_template=item_invocation_template,
            result_name="{}_item".format(result_name),
        )

        parameters = [self.Type("{}*".format(p.Type), "{}_items".format(p.Name)) for p in result.TransformVars]

        statements = textwrap.dedent(
            """\
            typename decltype({decl_name})::value_type {buffer_name};

            {buffer_name}.reserve({name}_items);

            {vars}

            while({buffer_name}.size() < {name}_items) {{
                {references}

                {item_statement}

                {increment}
            }}

            {items_statement}
            """,
        ).format(
            name=result_name,
            buffer_name=buffer_name,
            decl_name="{}_buffer".format(result_name[:-len("_item")]) if result_name.endswith("_item") else result_name,
            vars="\n".join(
                [
                    "{type} {name}_ptr({name});".format(
                        type=p.Type,
                        name=p.Name,
                    )
                    for p in parameters
                ]
            ),
            references=StringHelpers.LeftJustify(
                "\n".join(
                    [
                        "{type} & {item_name}(*{name}_ptr);".format(
                            type=item_p.Type,
                            item_name=item_p.Name,
                            name=p.Name,
                        )
                        for item_p, p in zip(result.TransformVars, parameters)
                    ]
                ),
                4,
            ).rstrip(),
            item_statement=StringHelpers.LeftJustify(
                result.AppendResultStatement,
                4,
            ).rstrip(),
            increment=StringHelpers.LeftJustify(
                "\n".join(
                    [
                        "++{}_ptr;".format(p.Name)
                        for p in parameters
                    ]
                ),
                4,
            ).rstrip(),
            items_statement=invocation_template.format("std::move({})".format(buffer_name)),
        )

        parameters += [self.Type("size_t", "{}_items".format(result_name))]

        return self.Result(
            "std::vector<{}>".format(result.VectorResultType),
            parameters,
            statements,
            ", ".join([p.Name for p in parameters]),
            destroy_inline=True,
        )
