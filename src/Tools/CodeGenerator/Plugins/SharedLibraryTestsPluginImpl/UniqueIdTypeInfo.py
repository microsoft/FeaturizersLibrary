# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the UniqueIdTypeInfo object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class UniqueIdTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("unique_id")
    CppType                                 = Interface.DerivedProperty("std::vector<std::string>")

    # ----------------------------------------------------------------------
    @Interface.override
    @staticmethod
    def CreateHelperMethods(output_stream):
        output_stream.write(
            textwrap.dedent(
                """\
                std::vector<std::string> CreateUniqueId(char const * const *strings, size_t items) {
                    if(strings == nullptr) throw std::invalid_argument("strings");
                    if(items == 0) throw std::invalid_argument("items");

                    std::vector<std::string> result;

                    result.reserve(items);

                    while(result.size() < items) {
                        char const * const ptr(*strings++);

                        if(ptr == nullptr) throw std::invalid_argument("'strings' element is null");

                        result.emplace_back(ptr);
                    }

                    return result;
                }

                """,
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        return (
            "{name}_buffer.data(), {name}_buffer.size()".format(
                name=input_name,
            ),
            textwrap.dedent(
                """\
                std::vector<char const *> {name}_buffer;

                {name}_buffer.reserve({name}.size());

                for(std::string const &value : {name})
                    {name}_buffer.emplace_back(value.c_str());

                """,
            ).format(
                name=input_name,
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        invocation_template,
        result_name="result",
    ):
        return self.Result(
            self.CppType,
            [
                self.Type("char **", "{}_ptr".format(result_name)),
                self.Type("size_t", "{}_items".format(result_name)),
            ],
            invocation_template.format(
                "CreateUniqueId({name}_ptr, {name}_items)".format(
                    name=result_name,
                ),
            ),
            "{name}_ptr, {name}_items".format(
                name=result_name,
            ),
            destroy_inline=True,
        )
