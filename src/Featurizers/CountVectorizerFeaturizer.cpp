// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "CountVectorizerFeaturizer.h"
#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

// ----------------------------------------------------------------------
// |
// |  CountVectorizerTransformer
// |
// ----------------------------------------------------------------------
CountVectorizerTransformer::CountVectorizerTransformer(TfidfEstimator::TransformerUniquePtr pTfidfTransformer) :
    _pTfidfTransformer(std::move(pTfidfTransformer)) {
}

CountVectorizerTransformer::CountVectorizerTransformer(Archive &ar) :
    CountVectorizerTransformer(
        [&ar](void) {
            using TransformerUniquePtr = std::unique_ptr<Microsoft::Featurizer::Featurizers::TfidfVectorizerTransformer>;
            return CountVectorizerTransformer(
                TransformerUniquePtr(new Microsoft::Featurizer::Featurizers::TfidfVectorizerTransformer(ar))
            );
        }()
    ) {
}

bool CountVectorizerTransformer::operator==(CountVectorizerTransformer const &other) const {
    return dynamic_cast<TfidfVectorizerTransformer const &>(*_pTfidfTransformer) == dynamic_cast<TfidfVectorizerTransformer const &>(*other._pTfidfTransformer);
}

void CountVectorizerTransformer::save(Archive &ar) const {
    _pTfidfTransformer->save(ar);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void CountVectorizerTransformer::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {

    _pTfidfTransformer->execute(
        input,
        [&callback](SparseVectorEncoding<std::float_t> obj) {

            std::vector<SparseVectorEncoding<std::uint32_t>::ValueEncoding> values;
            values.reserve(obj.Values.size());
            for (SparseVectorEncoding<std::float_t>::ValueEncoding const & item : obj.Values)
                values.emplace_back(SparseVectorEncoding<std::uint32_t>::ValueEncoding(static_cast<std::uint32_t>(item.Value), item.Index));

            callback(SparseVectorEncoding<std::uint32_t>(obj.NumElements, std::move(values)));
        }
    );
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
