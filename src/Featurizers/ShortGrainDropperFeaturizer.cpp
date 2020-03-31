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
ShortGrainDropperTransformer::ShortGrainDropperTransformer(GrainsSet grainsToKeep) :
    //grainsToKeep can be empty
    _grainsToKeep(std::move(grainsToKeep)) {
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
            GrainsSet                       grainsToKeep(Traits<GrainsSet>::deserialize(ar));

            return ShortGrainDropperTransformer(std::move(grainsToKeep));
        }()
    ) {
}

bool ShortGrainDropperTransformer::operator==(ShortGrainDropperTransformer const &other) const {
    return this->_grainsToKeep == other._grainsToKeep;
}

void ShortGrainDropperTransformer::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_grainsToKeep)>::serialize(ar, _grainsToKeep);
}

void ShortGrainDropperTransformer::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    // Generate true to drop, false to keep
    callback(_grainsToKeep.find(input) == _grainsToKeep.end());
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
