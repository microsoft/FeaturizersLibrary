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
CountVectorizerTransformer::CountVectorizerTransformer(IndexMapType map, bool binary, bool lower, AnalyzerMethod analyzer, std::string regex, std::uint32_t ngram_min, std::uint32_t ngram_max) :
    _labels(
        std::move([&map](void) ->  IndexMapType & {
            if (map.size() == 0) {
                throw std::invalid_argument("Index map is empty!");
            }
            return map;
        }()
        )),
    _binary(std::move(binary)),
    _lower(std::move(lower)),
    _analyzer(std::move(analyzer)),
    _regex(std::move(regex)),
    _ngram_min(
        std::move(
            [&ngram_min](void) -> std::uint32_t & {
                if(ngram_min == 0)
                    throw std::invalid_argument("ngramRangeMin");

                return ngram_min;
            }()
        )),
    _ngram_max(
        std::move(
            [&ngram_max](void) -> std::uint32_t & {
                if(ngram_max == 0)
                    throw std::invalid_argument("ngramRangeMax");

                return ngram_max;
            }()
        )),
    _parse_func(DocumentParseFuncGenerator(_analyzer, _regex, _ngram_min, _ngram_max)) {
}

CountVectorizerTransformer::CountVectorizerTransformer(Archive &ar) :
    CountVectorizerTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            IndexMapType           labels(Traits<IndexMapType>::deserialize(ar));
            bool                   binary(Traits<bool>::deserialize(ar));

            bool                   lower(Traits<bool>::deserialize(ar));
            AnalyzerMethod         analyzer(static_cast<AnalyzerMethod>(Traits<std::uint8_t>::deserialize(ar)));
            std::string            regex(Traits<std::string>::deserialize(ar));
            std::uint32_t          ngram_min(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t          ngram_max(Traits<std::uint32_t>::deserialize(ar));

            return CountVectorizerTransformer(std::move(labels), std::move(binary), std::move(lower), std::move(analyzer), std::move(regex), std::move(ngram_min), std::move(ngram_max));
        }()
    ) {
}

void CountVectorizerTransformer::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_labels)>::serialize(ar, _labels);
    Traits<decltype(_binary)>::serialize(ar, _binary);
    Traits<decltype(_lower)>::serialize(ar, _lower);
    Traits<std::underlying_type<AnalyzerMethod>::type>::serialize(ar, static_cast<std::underlying_type<AnalyzerMethod>::type>(_analyzer));
    Traits<decltype(_regex)>::serialize(ar, _regex);
    Traits<decltype(_ngram_min)>::serialize(ar, _ngram_min);
    Traits<decltype(_ngram_max)>::serialize(ar, _ngram_max);
}

bool CountVectorizerTransformer::operator==(CountVectorizerTransformer const &other) const {
    return _labels == other._labels
        && _binary == other._binary
        && _lower == other._lower
        && _analyzer == other._analyzer
        && _regex == other._regex
        && _ngram_min == other._ngram_min
        && _ngram_max == other._ngram_max;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void CountVectorizerTransformer::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    AppearanceMapType appearanceMap;

    std::string processedInput(Components::DocumentDecorator(input, _lower, _analyzer, _regex, _ngram_min, _ngram_max));

    _parse_func(
        processedInput,
        [&appearanceMap] (std::string::const_iterator iter_start, std::string::const_iterator iter_end) {

            AppearanceMapType::iterator iter_apperance(appearanceMap.find(std::make_tuple(iter_start, iter_end)));

            if (iter_apperance != appearanceMap.end()) {
                ++iter_apperance->second;
            } else {
                appearanceMap.insert(std::make_pair(std::make_tuple(iter_start, iter_end), 1));
            }
        }
    );

    std::vector<SparseVectorEncoding<std::uint32_t>::ValueEncoding> result;

    for (auto const & wordAppearance : appearanceMap) {
        std::string const word = std::string(std::get<0>(wordAppearance.first), std::get<1>(wordAppearance.first));

        typename IndexMapType::const_iterator const      iter_label(_labels.find(word));

        if (iter_label != _labels.end()) {
            if (_binary) {
                result.emplace_back(SparseVectorEncoding<std::uint32_t>::ValueEncoding(1, iter_label->second));
            } else {
                result.emplace_back(SparseVectorEncoding<std::uint32_t>::ValueEncoding(wordAppearance.second, iter_label->second));
            }
        }
    }
    // SparseVectorEncoding requires ValueEncoding to be in order
    // so we sort result before creating SparseVectorEncoding
    std::sort(result.begin(), result.end(),
        [](SparseVectorEncoding<std::uint32_t>::ValueEncoding const &a, SparseVectorEncoding<std::uint32_t>::ValueEncoding const &b) {
            return a.Index < b.Index;
        }
    );
    callback(SparseVectorEncoding<std::uint32_t>(_labels.size(), std::move(result)));

}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
