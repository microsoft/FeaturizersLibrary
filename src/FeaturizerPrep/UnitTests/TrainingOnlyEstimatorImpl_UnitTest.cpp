// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../TrainingOnlyEstimatorImpl.h"

namespace NS = Microsoft::Featurizer;

struct CountEstimatorPolicyBase {
    static std::string const                EstimatorName;
};

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wglobal-constructors"
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

std::string const CountEstimatorPolicyBase::EstimatorName("CountEstimatorPolicy");

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

/////////////////////////////////////////////////////////////////////////
///  \class         CountEstimatorPolicy
///  \brief         Counts distinct values.
///
template <typename T, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class CountEstimatorPolicy : public CountEstimatorPolicyBase {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using InputType                         = T;

    struct Results {
        using CountMap                      = std::map<T, std::uint32_t>;

        CountMap const                      Counts;

        Results(CountMap counts) : Counts(std::move(counts)) {}

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Results);
    };

    // ----------------------------------------------------------------------
    // |  Public Data
    static size_t const                     MaxNumTrainingItems = MaxNumTrainingItemsV;

    // ----------------------------------------------------------------------
    // |  Public Methods
    template <typename FitBufferInputTypeT>
    void fit_items(FitBufferInputTypeT const *pBuffer, size_t cItems) {
        FitBufferInputTypeT const * const   pEndBuffer(pBuffer + cItems);

        while(pBuffer != pEndBuffer) {
            InputType const &                           input(*pBuffer++);
            std::uint32_t &                             count(
                [this, &input](void) -> std::uint32_t & {
                    typename Results::CountMap::iterator const              i(_counts.find(input));

                    if(i != _counts.end())
                        return i->second;

                    std::pair<typename Results::CountMap::iterator, bool> const     result(_counts.emplace(std::make_pair(input, 0)));

                    return result.first->second;
                }()
            );

            count += 1;
        }
    }

    void fit_nulls(std::uint64_t const &) {
    }

    Results complete_training(void) {
        return Results(std::move(_counts));
    }

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    typename Results::CountMap              _counts;
};

template <typename EstimatorPolicyT>
std::map<typename EstimatorPolicyT::InputType, std::uint32_t> Test(
    std::vector<std::vector<typename EstimatorPolicyT::InputType>> const &inputBatches
) {
    using FitResult                         = NS::Estimator::FitResult;
    using Batches                           = std::vector<std::vector<typename EstimatorPolicyT::InputType>>;

    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Details::TrainingOnlyEstimatorImpl<EstimatorPolicyT, 0>             estimator(pAllColumnAnnotations);

    typename Batches::const_iterator                                        iter(inputBatches.begin());

    while(true) {
        FitResult const                     result(estimator.fit(iter->data(), iter->size()));

        if(result == FitResult::Complete)
            break;

        ++iter;

        if(iter == inputBatches.end()) {
            FitResult const                 completeResult(estimator.complete_training());

            if(completeResult != FitResult::Complete)
                throw std::runtime_error("Unexpected fit result");

            break;
        }
    }

    assert(estimator.is_training_complete());

    typename EstimatorPolicyT::Results const &          results(estimator.get_annotation_data());

    return results.Counts;
}

TEST_CASE("Ints") {
    std::map<int, std::uint32_t> const      counts(Test<CountEstimatorPolicy<int>>({{1, 2, 3}, {4, 5}, {3, 5}}));

    CHECK(counts == std::map<int, std::uint32_t>{{1, 1}, {2, 1}, {3, 2}, {4, 1}, {5, 2}});
}

TEST_CASE("Limited Ints") {
    std::map<int, std::uint32_t> const      counts(Test<CountEstimatorPolicy<int, 4>>({{1, 2, 3}, {4, 5}, {3, 5}}));

    CHECK(counts == std::map<int, std::uint32_t>{{1, 1}, {2, 1}, {3, 1}, {4, 1}});
}

TEST_CASE("Strings") {
    std::map<std::string, std::uint32_t> const          counts(Test<CountEstimatorPolicy<std::string>>({{"one", "two", "three"}, {"three", "two"}, {"four"}}));

    CHECK(counts == std::map<std::string, std::uint32_t>{{"one", 1}, {"two", 2}, {"three", 2}, {"four", 1}});
}
