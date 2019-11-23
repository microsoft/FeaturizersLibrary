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
        result_code = 0

        status_stream.write("Preprocessing data...")
        with status_stream.DoneManager():
            type_info_data = []

            for items in data:
                type_info_data.append([TypeInfoData(item) for item in items])

        for desc, func in [("Generating .h files...", _GenerateHeaderFile)]:
            status_stream.write(desc)
            with status_stream.DoneManager(
                suffix="\n",
            ) as dm:
                for index, (items, items_type_info_data) in enumerate(
                    zip(data, type_info_data),
                ):
                    dm.stream.write(
                        "Processing '{}' ({} of {})...".format(
                            items[0].name,
                            index + 1,
                            len(data),
                        ),
                    )
                    with dm.stream.DoneManager() as this_dm:
                        this_dm.result = func(
                            output_dir,
                            items,
                            items_type_info_data,
                            this_dm.stream,
                        )

                if dm.result < 0:
                    return dm.result

                result_code = result_code or dm.result

        return result_code


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def _GenerateHeaderFile(output_dir, items, all_type_info_data, output_stream):
    with open(
        os.path.join(output_dir, "SharedLibraryTests_{}.h".format(items[0].name)),
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

        for item, type_info_data in zip(items, all_type_info_data):
            template = getattr(item, "template", None)
            if template:
                template_desc = template.replace("std::", "")

                suffix = "_{}_".format(template_desc)
                type_desc = " <{}>".format(template_desc)
                cpp_template_suffix = "<{}>".format(template)
            else:
                suffix = "_"
                type_desc = ""
                cpp_template_suffix = ""

            if type_info_data.ConfigurationParamTypeInfoFactories:
                constructor_template_params = ", typename... ConstructorArgTs"
                constructor_params = ",\n    ConstructorArgTs &&... constructor_args"
                constructor_args = "std::forward<ConstructorArgTs>(constructor_args)..., "
            else:
                constructor_template_params = ""
                constructor_params = ""
                constructor_args = ""

            transform_input_args = type_info_data.InputTypeInfoFactory.GetTransformInputArgs(
                is_input_optional=getattr(item, "is_input_optional", False),
            )

            output_statement_info = type_info_data.OutputTypeInfoFactory.GetOutputInfo()

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
                        for(auto & result: results) {{
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

                                    break;
                                }}

                                INFO("Value is " << result)
                                REQUIRE(false);
                            }}
                        }}

                        {name}{suffix}CompleteTraining(pEstimatorHandle, &pErrorInfo);
                        REQUIRE(pErrorInfo == nullptr);


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
                    transform_output_args=output_statement_info.TransformOutputVars,
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
class TypeInfoData(object):
    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(self, item):
        # Create the custom structs
        custom_structs = OrderedDict()

        for custom_struct in getattr(item, "custom_structs", []):
            members = OrderedDict()

            for member in custom_struct.members:
                tif = self._GetTypeInfoClass(member.type)
                assert tif, member.type

                members[member.name] = tif()

            custom_structs[custom_struct.name] = members

        # Create the configuration param factories
        configuration_param_type_info_factories = []

        for configuration_param in getattr(item, "configuration_params", []):
            tif = self._GetTypeInfoClass(configuration_param.type)
            assert tif, configuration_param.type

            configuration_param_type_info_factories.append(tif(custom_structs))

        # Create the input factory
        tif = self._GetTypeInfoClass(item.input_type)
        assert tif, item.input_type

        input_type_info_factory = tif(custom_structs)

        # Create the output factory
        tif = self._GetTypeInfoClass(item.output_type)
        assert tif, item.output_type

        output_type_info_factory = tif(custom_structs)

        # Commit the results
        self.CustomStructs                              = custom_structs
        self.ConfigurationParamTypeInfoFactories        = configuration_param_type_info_factories
        self.InputTypeInfoFactory                       = input_type_info_factory
        self.OutputTypeInfoFactory                      = output_type_info_factory

    # ----------------------------------------------------------------------
    # |
    # |  Private Data
    # |
    # ----------------------------------------------------------------------
    _type_info_factory_classes              = None

    # ----------------------------------------------------------------------
    # |
    # |  Private Methods
    # |
    # ----------------------------------------------------------------------
    @classmethod
    def _GetTypeInfoClass(cls, the_type):
        if cls._type_info_factory_classes is None:
            from Plugins.SharedLibraryTestsPluginImpl import ScalarTypeInfoFactories
            from Plugins.SharedLibraryTestsPluginImpl.StringTypeInfoFactory import (
                StringTypeInfoFactory,
            )
            from Plugins.SharedLibraryTestsPluginImpl import StructTypeInfoFactories

            type_info_factory_classes = [StringTypeInfoFactory]

            for compound_module in [ScalarTypeInfoFactories, StructTypeInfoFactories]:
                for obj_name in dir(compound_module):
                    if (
                        obj_name.startswith("_")
                        or not obj_name.endswith("Factory")
                        or obj_name == "TypeInfoFactory"
                    ):
                        continue

                    type_info_factory_classes.append(getattr(compound_module, obj_name))

            # Associate the type info factories with the class rather than the instance
            # so that we only need to perform this initialization once.
            cls._type_info_factory_classes = type_info_factory_classes

        for type_info_factory_class in cls._type_info_factory_classes:
            if type_info_factory_class.TypeName == the_type:
                return type_info_factory_class

        return None
