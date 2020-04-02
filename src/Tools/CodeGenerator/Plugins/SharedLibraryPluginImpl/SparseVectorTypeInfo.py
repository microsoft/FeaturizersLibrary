# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the SparseVectorTypeInfo object"""

import os
import re
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class SparseVectorTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"sparse_vector\<(?P<type>\S+)\>"))
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

        super(SparseVectorTypeInfo, self).__init__(*args, **kwargs)

        match = self.TypeName.match(member_type)
        assert match, member_type

        the_type = match.group("type")

        type_info = create_type_info_func(the_type)
        if not hasattr(type_info, "CType"):
            raise Exception("'{}' is a type that can't be directly expressed in C and therefore cannot be used with a sparse_vector".format(the_type))

        if type_info.IsOptional:
            raise Exception("SparseVector types do not currently support optional values ('{}')".format(the_type))

        self._type_info                 = type_info

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        raise NotImplementedError("This structure is only used during output")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(
        self,
        arg_name,
        invocation_template,
        items_var_name=None,
    ):
        raise NotImplementedError("This structure is only used during output")

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
                self.Type("uint64_t *", "{}_numElements".format(arg_name)),
                self.Type("uint64_t *", "{}_numValues".format(arg_name)),
                self.Type("{} **".format(self._type_info.CType, arg_name), "{}_values".format(arg_name)),
                self.Type("uint64_t **", "{}_indexes".format(arg_name)),
            ],
            textwrap.dedent(
                """\
                if({name}_numElements == nullptr) throw std::invalid_argument("'{name}_numElements' is null");
                if({name}_numValues == nullptr) throw std::invalid_argument("'{name}_numValues' is null");
                if({name}_values == nullptr) throw std::invalid_argument("'{name}_values' is null");
                if({name}_indexes == nullptr) throw std::invalid_argument("'{name}_indexes' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                std::unique_ptr<{type} []> pValues(new {type} [{result}.Values.size()]);
                std::unique_ptr<uint64_t []> pIndexes(new uint64_t [{result}.Values.size()]);

                {type} * pValue(pValues.get());
                uint64_t * pIndex(pIndexes.get());

                for(auto const & encoding : {result}.Values) {{
                    *pValue++ = encoding.Value;
                    *pIndex++ = encoding.Index;
                }}

                {pointer}{name}_numElements = {result}.NumElements;
                {pointer}{name}_numValues = {result}.Values.size();

                {pointer}{name}_values = pValues.release();
                {pointer}{name}_indexes = pIndexes.release();
                """,
            ).format(
                name=arg_name,
                result=result_name,
                type=self._type_info.CppType,
                pointer="" if suppress_pointer else "*",
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
                self.Type("uint64_t", "{}_numElements".format(arg_name)),
                self.Type("uint64_t", "{}_numValues".format(arg_name)),
                self.Type("{} const *".format(self._type_info.CType), "{}_values".format(arg_name)),
                self.Type("uint64_t const *", "{}_indexes".format(arg_name)),
            ],
            textwrap.dedent(
                """\
                if({name}_numElements == 0) throw std::invalid_argument("'{name}_numElements' is 0");
                if({name}_numValues == 0) throw std::invalid_argument("'{name}_numValues' is 0");
                if({name}_values == nullptr) throw std::invalid_argument("'{name}_values' is null");
                if({name}_indexes == nullptr) throw std::invalid_argument("'{name}_indexes' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                delete [] {name}_values;
                delete [] {name}_indexes;
                """,
            ).format(
                name=arg_name,
            ),
        )
