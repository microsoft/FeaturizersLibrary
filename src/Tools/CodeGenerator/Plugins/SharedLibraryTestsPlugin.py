# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

import itertools
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
    def Generate(
        open_file_func,
        global_custom_structs,
        global_custom_enums,
        data,
        output_dir,
        status_stream,
    ):
        result_code = 0

        status_stream.write("Preprocessing data...")
        with status_stream.DoneManager():
            type_info_data = []

            for items in data:
                type_info_data.append([TypeInfoData(item, global_custom_structs, global_custom_enums) for item in items])

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
                            open_file_func,
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
def _GenerateHeaderFile(open_file_func, output_dir, items, all_type_info_data, output_stream):
    with open_file_func(
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
                #include "Featurizers/Structs.h"

                #include "SharedLibrary_Common.hpp"

                """,
            ).format(
                name=items[0].name,
            ),
        )

        for item, type_info_data in zip(items, all_type_info_data):
            template = getattr(item, "template", None)
            if template:
                suffix = "_{}_".format(template)
                type_desc = " <{}>".format(template)
                cpp_template_suffix = "<{}>".format(
                    type_info_data.InputTypeInfo.CppType,
                )
            else:
                suffix = "_"
                type_desc = ""
                cpp_template_suffix = ""

            if type_info_data.ConfigurationParamTypeInfos:
                constructor_template_params = ", typename... ConstructorArgTs"
                constructor_params = ",\n    ConstructorArgTs &&... constructor_args"
                constructor_args = "std::forward<ConstructorArgTs>(constructor_args)..., "
            else:
                constructor_template_params = ""
                constructor_params = ""
                constructor_args = ""

            transform_input_args = type_info_data.InputTypeInfo.GetTransformInputArgs()

            if item.has_dynamic_output:
                output_statement_info = type_info_data.DynamicOutputTypeInfo.GetOutputInfo()
                flush = ",\n    bool flush=true"
            else:
                output_statement_info = type_info_data.OutputTypeInfo.GetOutputInfo()
                flush = ""

            # Write the training statements
            f.write(
                textwrap.dedent(
                    """\
                    /* ---------------------------------------------------------------------- */
                    /* |  {name}{type_desc} */
                    template <typename VectorInputT{constructor_template_params}>
                    void {name}{suffix}Test(
                        std::vector<VectorInputT> const &training_input,
                        std::vector<VectorInputT> const &inference_input,
                        std::function<bool (std::vector<{vector_result_type}> const &)> const &verify_func{constructor_params}{flush}
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
                                TrainingState trainingState(0);

                                REQUIRE({name}{suffix}GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
                                REQUIRE(pErrorInfo == nullptr);

                                if(trainingState != Training)
                                    break;

                                FitResult result(0);
                                auto const & input(*iter);

                                REQUIRE({name}{suffix}Fit(pEstimatorHandle, {fit_input_args}, &result, &pErrorInfo));
                                REQUIRE(pErrorInfo == nullptr);

                                if(result == ResetAndContinue) {{
                                    iter = training_input.begin();
                                    continue;
                                }}

                                ++iter;
                                if(iter == training_input.end()) {{
                                    REQUIRE({name}{suffix}OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                                    REQUIRE(pErrorInfo == nullptr);

                                    iter = training_input.begin();
                                }}
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

                    """,
                ).format(
                    name=item.name,
                    type_desc=type_desc,
                    suffix=suffix,
                    vector_result_type=output_statement_info.VectorResultType,
                    constructor_template_params=constructor_template_params,
                    constructor_params=constructor_params,
                    flush=flush,
                    constructor_args=constructor_args,
                    fit_input_args=transform_input_args,
                ),
            )

            # Write the inferencing statements
            if type_info_data.InputTypeInfo.TypeName == "bool":
                # vector<bool> isn't actually a bool, so we can't take a direct reference to it
                for_loop = "for(bool input : inference_input)"
            else:
                for_loop = "for(auto const & input : inference_input)"

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

            if item.has_dynamic_output:
                f.write(
                    StringHelpers.LeftJustify(
                        textwrap.dedent(
                            """\
                            // Inference
                            std::vector<{vector_result_type}> results;

                            {for_loop} {{
                                {transform_vars}

                                REQUIRE({name}{suffix}Transform(pTransformerHandle, {transform_input_args}, {transform_output_args}, &pErrorInfo));
                                REQUIRE(pErrorInfo == nullptr);

                                {transform_statement}
                                {inline_destroy_statement}
                            }}

                            if(flush) {{
                                {transform_vars}

                                REQUIRE({name}{suffix}Flush(pTransformerHandle, {transform_output_args}, &pErrorInfo));
                                REQUIRE(pErrorInfo == nullptr);

                                {transform_statement}
                                {inline_destroy_statement}
                            }}
                            """,
                        ).format(
                            name=item.name,
                            suffix=suffix,
                            vector_result_type=output_statement_info.VectorResultType,
                            for_loop=for_loop,
                            transform_vars=StringHelpers.LeftJustify(
                                output_statement_info.TransformVars.rstrip(),
                                4,
                            ),
                            transform_input_args=transform_input_args,
                            transform_output_args=output_statement_info.TransformOutputVars,
                            transform_statement=StringHelpers.LeftJustify(
                                output_statement_info.AppendResultStatement.rstrip(),
                                4,
                            ),
                            inline_destroy_statement=StringHelpers.LeftJustify(
                                inline_destroy_statement.rstrip(),
                                4,
                            ),
                        ),
                        4,
                        skip_first_line=False,
                    ),
                )
            else:
                f.write(
                    StringHelpers.LeftJustify(
                        textwrap.dedent(
                            """\
                            // Inference
                            std::vector<{vector_result_type}> results;

                            results.reserve(inference_input.size());

                            {for_loop} {{
                                {transform_vars}

                                REQUIRE({name}{suffix}Transform(pTransformerHandle, {transform_input_args}, {transform_output_args}, &pErrorInfo));
                                REQUIRE(pErrorInfo == nullptr);

                                {transform_statement}
                                {inline_destroy_statement}
                            }}
                            """,
                        ).format(
                            name=item.name,
                            suffix=suffix,
                            vector_result_type=output_statement_info.VectorResultType,
                            for_loop=for_loop,
                            transform_vars=StringHelpers.LeftJustify(
                                output_statement_info.TransformVars.rstrip(),
                                4,
                            ),
                            transform_input_args=transform_input_args,
                            transform_output_args=output_statement_info.TransformOutputVars,
                            transform_statement=StringHelpers.LeftJustify(
                                output_statement_info.AppendResultStatement.rstrip(),
                                4,
                            ),
                            inline_destroy_statement=StringHelpers.LeftJustify(
                                inline_destroy_statement.rstrip(),
                                4,
                            ),
                        ),
                        4,
                        skip_first_line=False,
                    ),
                )

            f.write(
                textwrap.dedent(
                    """\

                        REQUIRE(verify_func(results));

                        {trailing_destroy_statement}

                        // Destroy the transformer
                        REQUIRE({name}{suffix}DestroyTransformer(pTransformerHandle, &pErrorInfo));
                        REQUIRE(pErrorInfo == nullptr);
                    }}
                    """,
                ).format(
                    name=item.name,
                    suffix=suffix,
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
    def __init__(self, item, global_custom_structs, global_custom_enums):
        # Create the custom enums
        custom_enums = OrderedDict()

        for custom_enum in itertools.chain(global_custom_enums, getattr(item, "custom_enums", [])):
            if isinstance(custom_enum.underlying_type, six.string_types):
                type_info = self._CreateTypeInfo(custom_enum.underlying_type)
                assert type_info, custom_enum.underlying_type

                custom_enum.underlying_type_info = type_info

            custom_enums[custom_enum.name] = custom_enum

        # Create the custom structs
        custom_structs = OrderedDict()

        for custom_struct in itertools.chain(global_custom_structs, getattr(item, "custom_structs", [])):
            members = OrderedDict()

            for member in custom_struct.members:
                type_info = self._CreateTypeInfo(member.type)
                assert type_info, member.type

                assert member.name not in members, member.name
                members[member.name] = type_info

            custom_structs[custom_struct.name] = members

        # Create the configuration param type infos
        configuration_param_type_infos = []

        for configuration_param in getattr(item, "configuration_params", []):
            if configuration_param.type in custom_enums:
                type_info = custom_enums[configuration_param.type].underlying_type_info
                configuration_param.is_enum = True

            else:
                type_info = self._CreateTypeInfo(
                    configuration_param.type,
                    custom_structs=custom_structs,
                    custom_enums=custom_enums,
                )
                assert type_info, configuration_param.type

            configuration_param_type_infos.append(type_info)

        input_type_info = self._CreateTypeInfo(
            item.input_type,
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )
        assert input_type_info, item.input_type

        output_type_info = self._CreateTypeInfo(
            item.output_type,
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )
        assert output_type_info, item.output_type

        dynamic_output_info = self._CreateTypeInfo(
            "vector<{}>".format(item.output_type),
            custom_structs=custom_structs,
            custom_enums=custom_enums,
        )

        # Commit the results
        self.CustomStructs                  = custom_structs
        self.ConfigurationParamTypeInfos    = configuration_param_type_infos
        self.InputTypeInfo                  = input_type_info
        self.OutputTypeInfo                 = output_type_info
        self.DynamicOutputTypeInfo          = dynamic_output_info

    # ----------------------------------------------------------------------
    # |
    # |  Private Data
    # |
    # ----------------------------------------------------------------------
    _type_info_classes                      = None

    # ----------------------------------------------------------------------
    # |
    # |  Private Methods
    # |
    # ----------------------------------------------------------------------
    @classmethod
    def _CreateTypeInfo(cls, the_type, *args, **kwargs):
        if cls._type_info_classes is None:
            from Plugins.SharedLibraryTestsPluginImpl.DatetimeTypeInfo import DatetimeTypeInfo
            from Plugins.SharedLibraryTestsPluginImpl.MatrixTypeInfo import MatrixTypeInfo
            from Plugins.SharedLibraryTestsPluginImpl import ScalarTypeInfos
            from Plugins.SharedLibraryTestsPluginImpl.SingleValueSparseVectorTypeInfo import SingleValueSparseVectorTypeInfo
            from Plugins.SharedLibraryTestsPluginImpl.SparseVectorTypeInfo import SparseVectorTypeInfo
            from Plugins.SharedLibraryTestsPluginImpl.StringTypeInfo import StringTypeInfo
            from Plugins.SharedLibraryTestsPluginImpl import StructTypeInfos
            from Plugins.SharedLibraryTestsPluginImpl.TupleTypeInfo import TupleTypeInfo
            from Plugins.SharedLibraryTestsPluginImpl.UniqueIdTypeInfo import UniqueIdTypeInfo
            from Plugins.SharedLibraryTestsPluginImpl.VectorTypeInfo import VectorTypeInfo

            type_info_classes = [
                DatetimeTypeInfo,
                MatrixTypeInfo,
                SingleValueSparseVectorTypeInfo,
                SparseVectorTypeInfo,
                StringTypeInfo,
                TupleTypeInfo,
                UniqueIdTypeInfo,
                VectorTypeInfo,
            ]

            for compound_module in [ScalarTypeInfos, StructTypeInfos]:
                for obj_name in dir(compound_module):
                    if (
                        obj_name.startswith("_")
                        or not obj_name.endswith("TypeInfo")
                        or obj_name == "TypeInfo"
                    ):
                        continue

                    type_info_classes.append(getattr(compound_module, obj_name))

            # Associate the type infos with the class rather than the instance
            # so that we only need to perform this initialization once.
            cls._type_info_classes = type_info_classes

        is_optional = False

        if the_type.endswith("?"):
            the_type = the_type[:-1]
            is_optional = True

        type_info_class = None

        for this_type_info_class in cls._type_info_classes:
            if isinstance(this_type_info_class.TypeName, six.string_types):
                if this_type_info_class.TypeName == the_type:
                    type_info_class = this_type_info_class
                    break

            elif hasattr(this_type_info_class.TypeName, "match"):
                if this_type_info_class.TypeName.match(the_type):
                    type_info_class = this_type_info_class
                    break

        if type_info_class is None:
            return None

        return type_info_class(
            *args,
            member_type=the_type,
            is_optional=is_optional,
            create_type_info_func=cls._CreateTypeInfo,
            **kwargs
        )
