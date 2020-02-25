// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "ShortGrainDropperFeaturizer.h"
#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

// ----------------------------------------------------------------------
// |
// |  ShortGrainDropperTransformer
// |
// ----------------------------------------------------------------------
ShortGrainDropperTransformer::ShortGrainDropperTransformer(GrainsSet grainsToDrop) :
    //grainsToDrop can be empty
    _grainsToDrop(std::move(grainsToDrop)) {
}

ShortGrainDropperTransformer::ShortGrainDropperTransformer(Archive &ar) :
    ShortGrainDropperTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            GrainsSet                       grainsToDrop(Traits<GrainsSet>::deserialize(ar));

            return ShortGrainDropperTransformer(std::move(grainsToDrop));
        }()
    ) {
}

bool ShortGrainDropperTransformer::operator==(ShortGrainDropperTransformer const &other) const {
    return this->_grainsToDrop == other._grainsToDrop;
}

void ShortGrainDropperTransformer::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_grainsToDrop)>::serialize(ar, _grainsToDrop);
}

void ShortGrainDropperTransformer::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    callback(_grainsToDrop.find(input) != _grainsToDrop.end());
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
