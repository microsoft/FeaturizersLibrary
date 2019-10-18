# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

import os
import sys
import textwrap

from collections import OrderedDict

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import StringHelpers
from CommonEnvironment import Interface

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from Plugin import Plugin as PluginBase, TypeVisitor as TypeVisitorBase

# ----------------------------------------------------------------------
_SUPPORTED_CUSTOM_TYPES                     = {
    "TimePoint": (lambda custom_structs: _TimePointTypeInfo(custom_structs)),
    "OneHotStruct": (lambda custom_structs: _OneHotStructTypeInfo(custom_structs)),
    "HashOneHotVectorizerStruct": (lambda custom_structs: _HashOneHotVectorizerStructTypeInfo(custom_structs)),
}

# ----------------------------------------------------------------------
@Interface.staticderived
class Plugin(PluginBase):
    # ----------------------------------------------------------------------
    # |  Properties
    Name                                    = Interface.DerivedProperty("SharedLibraryTests")
    Description                             = Interface.DerivedProperty(
        "Generates code used when testing the Shared Library import/export layer",
    )

    # ----------------------------------------------------------------------
    # |  Methods
    @staticmethod
    @Interface.override
    def Generate(data, output_dir, status_stream):
        type_info_visitor = _TypeInfoVisitor()
        supported_custom_types = set(six.iterkeys(_SUPPORTED_CUSTOM_TYPES))

        for index, items in enumerate(data):
            status_stream.write(
                "Processing '{}' ({} of {})...".format(
                    items[0].name,
                    index + 1,
                    len(data),
                ),
            )
            with status_stream.DoneManager() as this_dm:
                with open(
                    os.path.join(
                        output_dir,
                        "SharedLibraryTests_{}.h".format(items[0].name),
                    ),
                    "w",
                ) as f:
                    f.write(
                        textwrap.dedent(
                            """\
                            /* ---------------------------------------------------------------------- */
                            /* Copyright (c) Microsoft Corporation. All rights reserved.              */
                            /* Licensed under the MIT License                                         */
                            /* ---------------------------------------------------------------------- */
                            #pragma once

                            #include "SharedLibrary_{name}.h"
                            #include "Traits.h"

                            """,
                        ).format(
                            name=items[0].name,
                        ),
                    )

                    for item in items:
                        # Create the custom structs
                        custom_structs = OrderedDict()

                        for custom_struct in getattr(item, "custom_structs", []):
                            members = OrderedDict()

                            for member in custom_struct.members:
                                members[member.name] = type_info_visitor.Accept(
                                    member.type,
                                    supported_custom_types=supported_custom_types,
                                    custom_structs=custom_structs,
                                )

                            custom_structs[custom_struct.name] = members

                        template = getattr(item, "template", None)
                        if template is None:
                            suffix = "_"
                            type_desc = ""
                            cpp_template_suffix = ""
                        else:
                            template_desc = template.replace("std::", "")

                            suffix = "_{}_".format(template_desc)
                            type_desc = " <{}>".format(template_desc)
                            cpp_template_suffix = "<{}>".format(template)

                        if hasattr(item, "configuration_params"):
                            constructor_template_params = ", typename... ConstructorArgsT"
                            constructor_params = (
                                ",\n    ConstructorArgsT &&... constructor_args"
                            )
                            constructor_args = (
                                "std::forward<ConstructorArgsT>(constructor_args)..., "
                            )
                        else:
                            constructor_template_params = ""
                            constructor_params = ""
                            constructor_args = ""

                        transform_input_args = type_info_visitor.Accept(
                            item.input_type,
                            supported_custom_types=supported_custom_types,
                            custom_structs=custom_structs,
                        ).GetTransformInputArgs(
                            is_input_optional=getattr(item, "is_input_optional", False),
                        )

                        output_statement_info = type_info_visitor.Accept(
                            item.transformed_type,
                            supported_custom_types=supported_custom_types,
                            custom_structs=custom_structs,
                        ).GetOutputInfo()

                        inline_destroy_statement = "// No inline destroy statement"
                        trailing_destroy_statement = "// No trailing destroy statement"

                        if output_statement_info.DestroyArgs:
                            if output_statement_info.DestroyInline:
                                inline_destroy_statement = textwrap.dedent(
                                    """\

                                    // Destroy the contents
                                    REQUIRE({name}{suffix}DestroyTransformedData({args}, &pErrorInfo));
                                    REQUIRE(pErrorInfo == nullptr);
                                    """,
                                ).format(
                                    name=item.name,
                                    suffix=suffix,
                                    args=output_statement_info.DestroyArgs,
                                )
                            else:
                                trailing_destroy_statement = textwrap.dedent(
                                    """\
                                    for(auto const & result : results) {{
                                        REQUIRE({name}{suffix}DestroyTransformedData({args}, &pErrorInfo));
                                        REQUIRE(pErrorInfo == nullptr);
                                    }}
                                    """,
                                ).format(
                                    name=item.name,
                                    suffix=suffix,
                                    args=output_statement_info.DestroyArgs,
                                )

                        f.write(
                            textwrap.dedent(
                                """\
                                /* ---------------------------------------------------------------------- */
                                /* |  {name}{type_desc} */
                                template <typename VectorInputT{constructor_template_params}>
                                void {name}{suffix}Test(
                                    std::vector<VectorInputT> const &training_input,
                                    std::vector<VectorInputT> const &inference_input,
                                    std::function<bool (std::vector<{vector_result_type}> const &)> const &verify_func{constructor_params}
                                ) {{
                                    ErrorInfoHandle * pErrorInfo(nullptr);

                                    // Create the estimator
                                    {name}{suffix}EstimatorHandle *pEstimatorHandle(nullptr);

                                    REQUIRE({name}{suffix}CreateEstimator({constructor_args}&pEstimatorHandle, &pErrorInfo));
                                    REQUIRE(pEstimatorHandle != nullptr);
                                    REQUIRE(pErrorInfo == nullptr);

                                    // Train
                                    if(training_input.empty() == false) {{
                                        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

                                        while(true) {{
                                            FitResult result(Continue);
                                            auto const & input(*iter);

                                            REQUIRE({name}{suffix}Fit(pEstimatorHandle, {fit_input_args}, &result, &pErrorInfo));
                                            REQUIRE(pErrorInfo == nullptr);

                                            if(result == Complete)
                                                break;

                                            if(result == ResetAndContinue) {{
                                                iter = training_input.begin();
                                                continue;
                                            }}

                                            if(result == Continue) {{
                                                ++iter;

                                                if(iter != training_input.end())
                                                    continue;

                                                REQUIRE({name}{suffix}CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                                                REQUIRE(pErrorInfo == nullptr);

                                                if(result == Complete)
                                                    break;

                                                if(result == ResetAndContinue) {{
                                                    iter = training_input.begin();
                                                    continue;
                                                }}
                                            }}

                                            INFO("Value is " << result)
                                            REQUIRE(false);
                                        }}
                                    }}

                                    // Once here, training should be complete
                                    {{
                                        bool is_complete(false);

                                        REQUIRE({name}{suffix}IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
                                        REQUIRE(pErrorInfo == nullptr);
                                        REQUIRE(is_complete);
                                    }}

                                    // Create the Transformer
                                    {name}{suffix}TransformerHandle * pTransformerHandle(nullptr);

                                    REQUIRE({name}{suffix}CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
                                    REQUIRE(pTransformerHandle != nullptr);
                                    REQUIRE(pErrorInfo == nullptr);

                                    // Destroy the estimator
                                    REQUIRE({name}{suffix}DestroyEstimator(pEstimatorHandle, &pErrorInfo));
                                    REQUIRE(pErrorInfo == nullptr);

                                    // Inference
                                    std::vector<{vector_result_type}> results;

                                    results.reserve(inference_input.size());

                                    for(auto const & input : inference_input) {{
                                        {transform_vars}

                                        REQUIRE({name}{suffix}Transform(pTransformerHandle, {transform_input_args}, {transform_output_args}, &pErrorInfo));
                                        REQUIRE(pErrorInfo == nullptr);

                                        {transform_statement}
                                        {inline_destroy_statement}
                                    }}

                                    REQUIRE(verify_func(results));

                                    {trailing_destroy_statement}

                                    // Destroy the transformer
                                    REQUIRE({name}{suffix}DestroyTransformer(pTransformerHandle, &pErrorInfo));
                                    REQUIRE(pErrorInfo == nullptr);
                                }}

                                """,
                            ).format(
                                name=item.name,
                                type_desc=type_desc,
                                suffix=suffix,
                                vector_result_type=output_statement_info.VectorResultType,
                                constructor_template_params=constructor_template_params,
                                constructor_params=constructor_params,
                                constructor_args=constructor_args,
                                fit_input_args=transform_input_args,
                                transform_vars=StringHelpers.LeftJustify(
                                    output_statement_info.TransformVars,
                                    8,
                                ),
                                transform_input_args=transform_input_args,
                                transform_output_args=output_statement_info.TransformOutputArgs,
                                transform_statement=StringHelpers.LeftJustify(
                                    output_statement_info.AppendResultStatement,
                                    8,
                                ),
                                inline_destroy_statement=StringHelpers.LeftJustify(
                                    inline_destroy_statement.rstrip(),
                                    8,
                                ),
                                trailing_destroy_statement=StringHelpers.LeftJustify(
                                    trailing_destroy_statement.rstrip(),
                                    4,
                                ),
                            ),
                        )


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
@Interface.staticderived
class _TypeInfoVisitor(TypeVisitorBase):
    # ----------------------------------------------------------------------
    # |  Public Methods
    @classmethod
    @Interface.override
    def OnInt8(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int8_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnInt16(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int16_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnInt32(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int32_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnInt64(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::int64_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt8(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint8_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt16(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint16_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt32(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint32_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnUInt64(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::uint64_t")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnFloat32(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::float_t", "float")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnFloat64(cls, *args, **kwargs):
        return _ScalarTypeInfo("std::double_t", "double")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnBool(cls, *args, **kwargs):
        return _ScalarTypeInfo("bool")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnString(cls, *args, **kwargs):
        return _StringTypeInfo()

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def OnArray(cls, template_args, arg_name, is_input_optional):
        raise Exception("TODO: Not implemented")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def OnVector(*args, **kwargs):
        raise Exception("TODO: Not implemented")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def OnMap(*args, **kwargs):
        raise Exception("TODO: Not implemented")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def OnCustomType(type, *args, **kwargs):
        return _SUPPORTED_CUSTOM_TYPES[type](*args, **kwargs)


# ----------------------------------------------------------------------
class TypeInfo(Interface.Interface):

    # ----------------------------------------------------------------------
    # |  Public Types
    class Info(object):
        """Information about the type when it is used"""

        def __init__(
            self,
            vector_result_type,
            transform_vars,
            transform_output_args,
            append_result_statement,
            destroy_args=None,
            destroy_inline=False,
        ):
            self.VectorResultType           = vector_result_type
            self.TransformVars              = transform_vars
            self.TransformOutputArgs        = transform_output_args
            self.AppendResultStatement      = append_result_statement
            self.DestroyArgs                = destroy_args
            self.DestroyInline              = destroy_inline

    # ----------------------------------------------------------------------
    # |  Public Methods
    @staticmethod
    @Interface.abstractmethod
    def GetTransformInputArgs(
        is_input_optional,
        input_name="input",
    ):
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetOutputInfo(
        result_name="result",
    ):
        raise Exception("Abstract method")


# ----------------------------------------------------------------------
class _ScalarTypeInfo(TypeInfo):
    """Functionality for scalar types"""

    # ----------------------------------------------------------------------
    def __init__(
        self,
        cpp_type,
        interface_type=None,
    ):
        if interface_type is None:
            interface_type = cpp_type.replace("std::", "")

        self._cpp_type                      = cpp_type
        self._interface_type                = interface_type

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        if is_input_optional:
            return "Microsoft::Featurizer::Traits<{cpp_type}>::IsNull({input_name}) ? nullptr : &Microsoft::Featurizer::Traits<{cpp_type}>::GetNullableValue({input_name})".format(
                input_name=input_name,
                cpp_type=self._cpp_type,
            )

        return input_name

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Info(
            self._cpp_type,
            "{} {};".format(self._cpp_type, result_name),
            "&{}".format(result_name),
            "results.emplace_back(std::move({}));".format(result_name),
        )


# ----------------------------------------------------------------------
@Interface.staticderived
class _StringTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def GetTransformInputArgs(
        is_input_optional,
        input_name="input",
    ):
        if is_input_optional:
            return "Microsoft::Featurizer::Traits<std::string>::IsNull({input_name}) ? nullptr : {input_name}->c_str()".format(
                input_name=input_name,
            )

        return "{}.c_str()".format(input_name)

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetOutputInfo(
        cls,
        result_name="result",
    ):
        return cls.Info(
            "std::string",
            textwrap.dedent(
                """\
                char const * {result_name}_ptr(nullptr);
                std::size_t {result_name}_items(0);
                """,
            ).format(
                result_name=result_name,
            ),
            "&{result_name}_ptr, &{result_name}_items".format(
                result_name=result_name,
            ),
            "results.emplace_back(std::string({}_ptr));".format(result_name),
            "{result_name}_ptr, {result_name}_items".format(
                result_name=result_name,
            ),
            destroy_inline=True,
        )


# ----------------------------------------------------------------------
class _TimePointTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    def __init__(self, custom_structs):
        assert "TimePoint" in custom_structs, custom_structs
        self._member_info                   = custom_structs["TimePoint"]

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        raise Exception("'TimePoint' is only used as a TransformedType")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Info(
            "TimePoint *",
            "TimePoint * {}(nullptr);".format(result_name),
            "&{}".format(result_name),
            "results.emplace_back({});".format(result_name),
            result_name,
            destroy_inline=False,
        )

# ----------------------------------------------------------------------
class _OneHotStructTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    def __init__(self, custom_structs):
        assert "OneHotStruct" in custom_structs, custom_structs
        self._member_info                   = custom_structs["OneHotStruct"]

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        raise Exception("'OneHotStruct' is only used as a TransformedType")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Info(
            "OneHotStruct",
            "OneHotStruct {};".format(result_name),
            "&{}".format(result_name),
            "results.emplace_back({});".format(result_name),
            destroy_inline=False,
        )

# ----------------------------------------------------------------------
class _HashOneHotVectorizerStructTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    def __init__(self, custom_structs):
        assert "HashOneHotVectorizerStruct" in custom_structs, custom_structs
        self._member_info                   = custom_structs["HashOneHotVectorizerStruct"]

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        raise Exception("'HashOneHotVectorizerStruct' is only used as a TransformedType")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Info(
            "HashOneHotVectorizerStruct",
            "HashOneHotVectorizerStruct {};".format(result_name),
            "&{}".format(result_name),
            "results.emplace_back({});".format(result_name),
            destroy_inline=False,
        )
        