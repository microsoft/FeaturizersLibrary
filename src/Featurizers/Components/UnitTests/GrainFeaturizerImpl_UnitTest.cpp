// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../GrainFeaturizerImpl.h"
#include "../InferenceOnlyFeaturizerImpl.h"
#include "../TrainingOnlyEstimatorImpl.h"

#include "../../TestHelpers.h"

namespace NS                                = Microsoft::Featurizer;
namespace Components                        = Microsoft::Featurizer::Featurizers::Components;

namespace Impl {

static constexpr char const * const         SumTrainingOnlyEstimatorPolicyName("SumTest");

/////////////////////////////////////////////////////////////////////////
///  \class         SumTrainingOnlyEstimatorPolicy
///  \brief         Simple Estimator that adds all of the values observed
///                 during training.
///
class SumTrainingOnlyEstimatorPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = std::uint32_t;

    struct Data {
        std::uint64_t const                 Value;

        Data(std::uint64_t value) : Value(std::move(value)) {}
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = SumTrainingOnlyEstimatorPolicyName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SumTrainingOnlyEstimatorPolicy(void) :
        _total(0) {
    }

    void fit(InputType const &item) {
        _total += item;
    }

    Data complete_training(void) {
        return _total;
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint64_t                           _total;
};

} // namespace Impl

template <
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using SumTrainingOnlyEstimator              = Components::TrainingOnlyEstimatorImpl<Impl::SumTrainingOnlyEstimatorPolicy, MaxNumTrainingItemsV>;

/////////////////////////////////////////////////////////////////////////
///  \class         DeltaTransformer
///  \brief         Transformer that adds a delta (which is considered to
///                 be the Transformer's state) to each incoming value.
///
class DeltaTransformer : public NS::StandardTransformer<std::uint64_t, std::uint64_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = NS::StandardTransformer<std::uint64_t, std::uint64_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DeltaTransformer(std::uint64_t delta) :
        _delta(std::move(delta)) {
    }

    DeltaTransformer(NS::Archive &ar) :
        DeltaTransformer(NS::Traits<std::uint64_t>::deserialize(ar)) {
    }

    ~DeltaTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DeltaTransformer);

    void save(Archive &ar) const override {
        NS::Traits<std::uint64_t>::serialize(ar, _delta);
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint64_t const                     _delta;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(input + _delta);
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         DeltaEstimator
///  \brief         Estimator that creates the DeltaTransformer.
///
class DeltaEstimator : public NS::TransformerEstimator<std::uint64_t, std::uint64_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformerType                   = DeltaTransformer;

    using BaseType                          = NS::TransformerEstimator<std::uint64_t, std::uint64_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DeltaEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType("DeltaEstimator", std::move(pAllColumnAnnotations)),
        _runningTotal(0) {
    }

    ~DeltaEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DeltaEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint64_t                           _runningTotal;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override {
        return true;
    }

    NS::FitResult fit_impl(InputType const *pItems, size_t cItems) override {
        InputType const * const             pEndItems(pItems + cItems);

        while(pItems != pEndItems)
            _runningTotal += *pItems++;

        return NS::FitResult::Continue;
    }

    void complete_training_impl(void) override {
        // Nothing to do here
    }

    TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new DeltaTransformer(std::move(_runningTotal)));
    }
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename GrainEstimatorT, typename InputT>
typename Components::GrainEstimatorAnnotation<typename GrainEstimatorT::GrainType>::AnnotationMap
Test(
    GrainEstimatorT &estimator,
    std::vector<InputT> const &inputs,
    bool createsAnnotations=true,
    size_t colIndex=0
) {
    // ----------------------------------------------------------------------
    using GrainEstimatorAnnotation          = typename GrainEstimatorT::GrainEstimatorAnnotation;
    // ----------------------------------------------------------------------

    estimator.begin_training();
    estimator.fit(inputs.data(), inputs.size());
    estimator.complete_training();

    if(createsAnnotations == false)
        return typename GrainEstimatorAnnotation::AnnotationMap();

    NS::AnnotationMaps const &              allAnnotations(estimator.get_column_annotations());
    GrainEstimatorAnnotation const &        thisAnnotation(GrainEstimatorT::get_annotation(allAnnotations, colIndex, estimator.Name));

    return thisAnnotation.Annotations;
}

TEST_CASE("Estimator") {
    // ----------------------------------------------------------------------
    using ThisSumTrainingOnlyEstimator      = SumTrainingOnlyEstimator<>;
    using Estimator                         = Components::GrainEstimatorImpl<std::string, ThisSumTrainingOnlyEstimator>;
    using GrainEstimatorAnnotation          = Components::GrainEstimatorAnnotation<std::string>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    Estimator                               estimator(
        pAllColumnAnnotations,
        [](NS::AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return SumTrainingOnlyEstimator<>(std::move(pAllColumnAnnotationsParam), 0);
        }
    );

    CHECK(strcmp(estimator.Name, "GrainSumTest") == 0);

    std::string const                       grain1("one");
    std::string const                       grain2("two");
    std::string const                       grain3("three");
    std::uint32_t const                     value10(10);
    std::uint32_t const                     value20(20);

    SECTION("Single grain") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);
    }

    SECTION("Multiple grains") {
        std::uint32_t const                 value100(100);
        std::uint32_t const                 value200(200);
        std::uint32_t const                 value1000(1000);
        std::uint32_t const                 value2000(2000);

        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain2, value100),
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain2, value200),
                    typename Estimator::InputType(grain3, value2000),
                    typename Estimator::InputType(grain3, value1000)
                )
            )
        );

        REQUIRE(annotations.size() == 3);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 300);

        REQUIRE(annotations.find(grain3) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain3)->second).Value == 3000);
    }
}

TEST_CASE("Estimator - limited total training items") {
    // ----------------------------------------------------------------------
    using ThisSumTrainingOnlyEstimator      = SumTrainingOnlyEstimator<>;
    using Estimator                         = Components::GrainEstimatorImpl<std::string, ThisSumTrainingOnlyEstimator, Components::StandardGrainImplPolicy, 3>;
    using GrainEstimatorAnnotation          = Components::GrainEstimatorAnnotation<std::string>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    Estimator                               estimator(
        pAllColumnAnnotations,
        [](NS::AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return ThisSumTrainingOnlyEstimator(std::move(pAllColumnAnnotationsParam), 0);
        }
    );
    std::string const                       grain1("one");
    std::string const                       grain2("two");
    std::uint32_t const                     value10(10);
    std::uint32_t const                     value20(20);
    std::uint32_t const                     value30(30);
    std::uint32_t const                     value40(40);

    SECTION("Single grain, equal number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain1, value30)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 60);
    }

    SECTION("Single grain, smaller number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);
    }

    SECTION("Single grain, larger number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain1, value30),
                    typename Estimator::InputType(grain1, value40)    // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 60);
    }

    // When the number of training items is limited at the grain level, it applies to all input regardless of grain
    SECTION("Multiple grain, small number of items") {
        std::uint32_t const                 value100(100);

        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain2, value100)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 10);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 100);
    }

    SECTION("Multiple grain, equal number of items") {
        std::uint32_t const                 value100(100);

        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain2, value100),
                    typename Estimator::InputType(grain1, value20)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 100);
    }

    SECTION("Multiple grain, larger number of items") {
        std::uint32_t const                 value100(100);
        std::uint32_t const                 value200(200);

        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain2, value100),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain2, value200)   // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 100);
    }

    SECTION("Multiple grain, larger number of items (new item after cutoff)") {
        std::string const                   newGrain("A New Grain!!");
        std::uint32_t const                 value100(100);
        std::uint32_t const                 value0(0);

        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain2, value100),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(newGrain, value0) // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 100);
    }
}

TEST_CASE("Estimator - limited individual training items") {
    // ----------------------------------------------------------------------
    using ThisSumTrainingOnlyEstimator      = SumTrainingOnlyEstimator<2>;
    using Estimator                         = Components::GrainEstimatorImpl<std::string, ThisSumTrainingOnlyEstimator>;
    using GrainEstimatorAnnotation          = Components::GrainEstimatorAnnotation<std::string>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    Estimator                               estimator(
        pAllColumnAnnotations,
        [](NS::AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return ThisSumTrainingOnlyEstimator(std::move(pAllColumnAnnotationsParam), 0);
        }
    );
    std::string const                       grain1("one");
    std::string const                       grain2("two");
    std::uint32_t const                     value0(0);
    std::uint32_t const                     value10(10);
    std::uint32_t const                     value20(20);
    std::uint32_t const                     value30(30);
    std::uint32_t const                     value100(100);
    std::uint32_t const                     value200(200);

    SECTION("Single grain, equal number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);
    }

    SECTION("Single grain, smaller number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 10);
    }

    SECTION("Single grain, larger number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain1, value30) // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);
    }

    SECTION("Multiple grain, small number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain2, value100)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 10);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 100);
    }

    SECTION("Multiple grain, equal number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain2, value100),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain2, value200)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 300);
    }

    SECTION("Multiple grain, larger number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain2, value100),
                    typename Estimator::InputType(grain1, value30), // This will be ignored
                    typename Estimator::InputType(grain2, value200)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);

        REQUIRE(annotations.find(grain2) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain2)->second).Value == 300);
    }

    SECTION("Multiple grain, larger number of items (new item after cutoff)") {
        std::string const                   newGrain("A New Grain!!");

        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    typename Estimator::InputType(grain1, value10),
                    typename Estimator::InputType(grain1, value20),
                    typename Estimator::InputType(grain1, value30), // This will be ignored
                    typename Estimator::InputType(newGrain, value0)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find(grain1) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(grain1)->second).Value == 30);

        REQUIRE(annotations.find(newGrain) != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find(newGrain)->second).Value == 0);
    }
}

TEST_CASE("Estimator - no training items") {
    // ----------------------------------------------------------------------
    using Estimator                         = Components::GrainEstimatorImpl<std::string, DeltaEstimator>;
    // ----------------------------------------------------------------------

    SECTION("No transformer creation func") {
        Estimator                           estimator(NS::CreateTestAnnotationMapsPtr(1));

        estimator.begin_training();
        estimator.complete_training();

        CHECK_THROWS_WITH(
            estimator.create_transformer(),
            "`_createTransformerFunc` must be provided when no grains were encountered during training"
        );
    }

    SECTION("With transformer creation func") {
        Estimator                           estimator(
            NS::CreateTestAnnotationMapsPtr(1),
            [](void) {
                return typename Estimator::TransformerType::GrainTransformerTypeUniquePtr(new DeltaTransformer(0));
            }
        );

        estimator.begin_training();
        CHECK(estimator.get_state() == NS::TrainingState::Training);

        estimator.complete_training();
        CHECK(estimator.get_state() == NS::TrainingState::Completed);

        estimator.create_transformer();
    }

    SECTION("With transformer creation func, no training required") {
        Estimator                           estimator(
            NS::CreateTestAnnotationMapsPtr(1),
            [](void) {
                return typename Estimator::TransformerType::GrainTransformerTypeUniquePtr(new DeltaTransformer(0));
            },
            true // isInferenceOnlyEstimator
        );

        estimator.begin_training();
        CHECK(estimator.get_state() == NS::TrainingState::Finished);

        estimator.complete_training();
        CHECK(estimator.get_state() == NS::TrainingState::Completed);

        estimator.create_transformer();
    }
}

template <typename TransformerT>
void Execute(TransformerT &transformer, std::string const &grain, std::uint64_t const &input, std::uint64_t expected) {
    transformer.execute(
        std::tuple<std::string const &, std::uint64_t const &>(grain, input),
        [&grain, &expected](std::tuple<std::string, std::uint64_t> value) {
            CHECK(std::get<0>(value) == grain);
            CHECK(std::get<1>(value) == expected);
        }
    );
}

TEST_CASE("Transformer") {
    // ----------------------------------------------------------------------
    using Estimator                         = Components::GrainEstimatorImpl<std::string, DeltaEstimator>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    Estimator                               estimator(pAllColumnAnnotations);
    std::string const                       grain1("one");
    std::string const                       grain2("two");

    SECTION("Single grain") {
        std::uint64_t const                 value10(10);
        std::uint64_t const                 value20(20);

        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                typename Estimator::InputType(grain1, value10),
                typename Estimator::InputType(grain1, value20)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        Execute(*pTransformer, grain1, 1, 31);
        Execute(*pTransformer, grain1, 100, 130);
    }

    SECTION("Multi grain") {
        std::uint64_t const                 value10(10);
        std::uint64_t const                 value20(20);
        std::uint64_t const                 value100(100);
        std::uint64_t const                 value200(200);

        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                typename Estimator::InputType(grain1, value10),
                typename Estimator::InputType(grain2, value100),
                typename Estimator::InputType(grain2, value200),
                typename Estimator::InputType(grain1, value20)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        Execute(*pTransformer, grain1, 1, 31);
        Execute(*pTransformer, grain1, 100, 130);

        Execute(*pTransformer, grain2, 1, 301);
        Execute(*pTransformer, grain2, 1000, 1300);
    }

    SECTION("New Grain") {
        std::uint64_t const                 value10(10);

        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                typename Estimator::InputType(grain1, value10)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        std::string const                   grain("A New Grain!!");
        std::uint64_t const                 value(100);

        CHECK_THROWS_WITH(
            pTransformer->execute(
                typename Estimator::InputType(grain, value),
                [](std::tuple<std::string, std::uint64_t>) {}
            ),
            "Grain not found"
        );

        Execute(*pTransformer, grain1, 1, 11);
        Execute(*pTransformer, grain1, 100, 110);
    }

    SECTION("Archive") {
        std::uint64_t const                 value10(10);
        std::uint64_t const                 value20(20);
        std::uint64_t const                 value100(100);
        std::uint64_t const                 value200(200);

        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                typename Estimator::InputType(grain1, value10),
                typename Estimator::InputType(grain2, value100),
                typename Estimator::InputType(grain2, value200),
                typename Estimator::InputType(grain1, value20)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        Execute(*pTransformer, grain1, 1, 31);
        Execute(*pTransformer, grain1, 100, 130);

        Execute(*pTransformer, grain2, 1, 301);
        Execute(*pTransformer, grain2, 1000, 1300);

        NS::Archive                         outArchive;

        pTransformer->save(outArchive);

        NS::Archive                         inArchive(outArchive.commit());

        Components::GrainTransformer<std::string, DeltaEstimator, Components::StandardGrainImplPolicy>  otherTransformer(inArchive);

        Execute(otherTransformer, grain1, 1, 31);
        Execute(otherTransformer, grain1, 100, 130);

        Execute(otherTransformer, grain2, 1, 301);
        Execute(otherTransformer, grain2, 1000, 1300);
    }
}

TEST_CASE("GrainTransformer - deserialization errors") {
    // ----------------------------------------------------------------------
    using GrainTransformer                  = Components::GrainTransformer<int, DeltaEstimator, Components::StandardGrainImplPolicy>;
    // ----------------------------------------------------------------------

    SECTION("Invalid number of items") {
        NS::Archive                         outArchive;

        NS::Traits<std::uint64_t>::serialize(outArchive, 0);
        NS::Traits<bool>::serialize(outArchive, false);

        NS::Archive                         inArchive(outArchive.commit());

        CHECK_THROWS_WITH(
            GrainTransformer(inArchive),
            "A `createFunc` must be provided to the serializing object when there aren't any transformers in the transformer map"
        );
    }

    SECTION("Duplicate grain") {
        NS::Archive                         outArchive;

        NS::Traits<std::uint64_t>::serialize(outArchive, 3);

        NS::Traits<int>::serialize(outArchive, 1);
        DeltaTransformer(10).save(outArchive);

        NS::Traits<int>::serialize(outArchive, 2);
        DeltaTransformer(20).save(outArchive);

        NS::Traits<int>::serialize(outArchive, 1);
        DeltaTransformer(30).save(outArchive);

        NS::Archive                         inArchive(outArchive.commit());

        CHECK_THROWS_WITH(
            GrainTransformer(inArchive),
            "Invalid insertion"
        );
    }
}

TEST_CASE("GrainEstimatorAnnotation - construct errors") {
    // ----------------------------------------------------------------------
    using GrainEstimatorAnnotation          = Components::GrainEstimatorAnnotation<int>;
    // ----------------------------------------------------------------------

    CHECK_THROWS_WITH(
        GrainEstimatorAnnotation(typename GrainEstimatorAnnotation::AnnotationMap()),
        "annotations"
    );
}

TEST_CASE("GrainTransformer - construct errors") {
    // ----------------------------------------------------------------------
    using GrainTransformer                  = Components::GrainTransformer<int, DeltaEstimator, Components::StandardGrainImplPolicy>;
    // ----------------------------------------------------------------------

    CHECK_THROWS_WITH(
        GrainTransformer(typename GrainTransformer::TransformerMap()),
        "transformers"
    );
}

TEST_CASE("GrainEstimatorImpl - construct errors") {
    // ----------------------------------------------------------------------
    using GrainEstimator                    = Components::GrainEstimatorImpl<int, DeltaEstimator, Components::StandardGrainImplPolicy>;
    // ----------------------------------------------------------------------

    CHECK_THROWS_WITH(
        GrainEstimator(NS::CreateTestAnnotationMapsPtr(1), typename GrainEstimator::CreateEstimatorFunc()),
        "createFunc"
    );
    CHECK_THROWS_WITH(
        GrainEstimator(NS::CreateTestAnnotationMapsPtr(1), typename GrainEstimator::CreateTransformerFunc()),
        "createTransformerFunc"
    );
    CHECK_THROWS_WITH(
        GrainEstimator(
            NS::CreateTestAnnotationMapsPtr(1),
            [](NS::AnnotationMapsPtr pAnnotationMaps) {
                return DeltaEstimator(std::move(pAnnotationMaps));
            },
            typename GrainEstimator::CreateTransformerFunc()
        ),
        "createTransformerFunc"
    );
}

TEST_CASE("Transformer - construct errors") {
    // ----------------------------------------------------------------------
    using GrainTransformer                  = Components::GrainTransformer<int, DeltaEstimator, Components::StandardGrainImplPolicy>;
    // ----------------------------------------------------------------------

    CHECK_THROWS_WITH(
        GrainTransformer(typename GrainTransformer::CreateTransformerFunc()),
        "`createFunc` is empty"
    );
}

TEST_CASE("Transformer without training") {
    // ----------------------------------------------------------------------
    using GrainTransformer                  = Components::GrainTransformer<std::string, DeltaEstimator, Components::StandardGrainImplPolicy>;
    // ----------------------------------------------------------------------

    GrainTransformer                        transformer(
        [](void) {
            return typename GrainTransformer::GrainTransformerTypeUniquePtr(new DeltaTransformer(100));
        }
    );

    std::string const                       grain1("1");
    std::string const                       grain2("2");
    std::uint64_t const                     value10(10);
    std::uint64_t const                     value20(20);

    Execute(transformer, grain1, value10, 110);
    Execute(transformer, grain1, value20, 120);

    Execute(transformer, grain2, value10, 110);
    Execute(transformer, grain1, value20, 120);

    Execute(transformer, grain2, value10, 110);
}

TEST_CASE("Deserialization of Transformer without training") {
    // ----------------------------------------------------------------------
    using GrainTransformer                  = Components::GrainTransformer<std::string, DeltaEstimator, Components::StandardGrainImplPolicy>;
    // ----------------------------------------------------------------------

    GrainTransformer                        transformer1(
        [](void) {
            return typename GrainTransformer::GrainTransformerTypeUniquePtr(new DeltaTransformer(100));
        }
    );

    NS::Archive                             out;

    transformer1.save(out);

    NS::Archive                             in(out.commit());
    GrainTransformer                        transformer2(in);

    std::string const                       grain1("1");
    std::string const                       grain2("2");
    std::uint64_t const                     value10(10);

    Execute(transformer2, grain1, value10, 110);
    Execute(transformer2, grain2, value10, 110);
}

/////////////////////////////////////////////////////////////////////////
///  \class         DelayDeltaTransformer
///  \brief         Transformer that adds a delta (which is considered to be
///                 the transformer's state) to each incoming value.
///
template <size_t DelayV>
class DelayDeltaTransformer : public NS::Transformer<std::uint64_t, std::uint64_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = NS::Transformer<std::uint64_t, std::uint64_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DelayDeltaTransformer(std::uint64_t delta) :
        _delta(std::move(delta)),
        _buffer(DelayV)
    {}

    DelayDeltaTransformer(NS::Archive &ar) :
        DelayDeltaTransformer(NS::Traits<std::uint64_t>::deserialize(ar))
    {}

    ~DelayDeltaTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DelayDeltaTransformer);

    void save(Archive &ar) const override {
        NS::Traits<std::uint64_t>::serialize(ar, _delta);
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    using CircularBuffer                    = Components::CircularBuffer<std::uint64_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint64_t const                     _delta;
    CircularBuffer                          _buffer;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        if(_buffer.is_full())
            callback(*_buffer.begin());

        _buffer.push(input + _delta);
    }

    void flush_impl(typename BaseType::CallbackFunction const &callback) override {
        CircularBuffer::iterator            ptr(_buffer.begin());
        CircularBuffer::iterator const      pEnd(_buffer.end());

        while(ptr != pEnd)
            callback(*ptr++);
    }
};

template <size_t DelayV>
using GrainedDelayDeltaTransformer          = Components::GrainTransformer<std::string, DelayDeltaTransformer<DelayV>, Components::DelayedGrainImplPolicy>;

TEST_CASE("GrainedDelayDeltaTransformer - single grain, delay 1") {
    // ----------------------------------------------------------------------
    constexpr size_t const Delay            = 1;

    using Transformer                       = DelayDeltaTransformer<Delay>;
    using GrainedTransformer                = GrainedDelayDeltaTransformer<Delay>;
    using Results                           = std::vector<typename GrainedTransformer::TransformedType>;
    // ----------------------------------------------------------------------

    std::string const                       grain("one");
    std::uint64_t const                     value100(100);
    std::uint64_t const                     value200(200);
    std::uint64_t const                     value300(300);
    Results                                 results;

    auto const                              callback(
        [&results](typename GrainedTransformer::TransformedType output) {
            results.emplace_back(std::move(output));
        }
    );

    GrainedTransformer                      transformer(
        [](void) {
            return std::unique_ptr<Transformer>(new Transformer(10));
        },
        Delay
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(0, value100)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(1, value200)), callback);
    CHECK(
        results == Results{
            {grain, GrainedTransformer::PolicyTransformedType(0, 110)}
        }
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(2, value300)), callback);
    CHECK(
        results == Results{
            {grain, GrainedTransformer::PolicyTransformedType(0, 110)},
            {grain, GrainedTransformer::PolicyTransformedType(1, 210)}
        }
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(3000, value200)), callback);
    CHECK(
        results == Results{
            {grain, GrainedTransformer::PolicyTransformedType(0, 110)},
            {grain, GrainedTransformer::PolicyTransformedType(1, 210)},
            {grain, GrainedTransformer::PolicyTransformedType(2, 310)}
        }
    );

    transformer.flush(callback);
    CHECK(
        results == Results{
            {grain, GrainedTransformer::PolicyTransformedType(0, 110)},
            {grain, GrainedTransformer::PolicyTransformedType(1, 210)},
            {grain, GrainedTransformer::PolicyTransformedType(2, 310)},
            {grain, GrainedTransformer::PolicyTransformedType(3000, 210)}
        }
    );
}

TEST_CASE("GrainedDelayDeltaTransformer - single grain, delay 2") {
    // ----------------------------------------------------------------------
    constexpr size_t const Delay            = 2;

    using Transformer                       = DelayDeltaTransformer<Delay>;
    using GrainedTransformer                = GrainedDelayDeltaTransformer<Delay>;
    using Results                           = std::vector<typename GrainedTransformer::TransformedType>;
    // ----------------------------------------------------------------------

    std::string const                       grain("one");
    std::uint64_t const                     value100(100);
    std::uint64_t const                     value200(200);
    std::uint64_t const                     value300(300);
    Results                                 results;

    auto const                              callback(
        [&results](typename GrainedTransformer::TransformedType output) {
            results.emplace_back(std::move(output));
        }
    );

    GrainedTransformer                      transformer(
        [](void) {
            return std::unique_ptr<Transformer>(new Transformer(10));
        },
        Delay
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(0, value100)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(1, value200)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(2, value300)), callback);
    CHECK(
        results == Results{
            {grain, GrainedTransformer::PolicyTransformedType(0, 110)}
        }
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain, GrainedTransformer::PolicyInputType(3000, value200)), callback);
    CHECK(
        results == Results{
            {grain, GrainedTransformer::PolicyTransformedType(0, 110)},
            {grain, GrainedTransformer::PolicyTransformedType(1, 210)}
        }
    );

    transformer.flush(callback);
    CHECK(
        results == Results{
            {grain, GrainedTransformer::PolicyTransformedType(0, 110)},
            {grain, GrainedTransformer::PolicyTransformedType(1, 210)},
            {grain, GrainedTransformer::PolicyTransformedType(2, 310)},
            {grain, GrainedTransformer::PolicyTransformedType(3000, 210)}
        }
    );
}

TEST_CASE("GrainedDelayDeltaTransformer - multi grain, delay 1") {
    // ----------------------------------------------------------------------
    constexpr size_t const Delay            = 1;

    using Transformer                       = DelayDeltaTransformer<Delay>;
    using GrainedTransformer                = GrainedDelayDeltaTransformer<Delay>;
    using Results                           = std::vector<typename GrainedTransformer::TransformedType>;
    // ----------------------------------------------------------------------

    std::string const                       grain1("one");
    std::string const                       grain2("two");
    std::uint64_t const                     value100(100);
    std::uint64_t const                     value200(200);
    std::uint64_t const                     value300(300);
    Results                                 results;

    auto const                              callback(
        [&results](typename GrainedTransformer::TransformedType output) {
            results.emplace_back(std::move(output));
        }
    );

    GrainedTransformer                      transformer(
        [](void) {
            return std::unique_ptr<Transformer>(new Transformer(10));
        },
        Delay
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain1, GrainedTransformer::PolicyInputType(0, value100)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain2, GrainedTransformer::PolicyInputType(1, value300)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain2, GrainedTransformer::PolicyInputType(2, value200)), callback);
    CHECK(
        results == Results{
            {grain2, GrainedTransformer::PolicyTransformedType(1, 310)}
        }
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain1, GrainedTransformer::PolicyInputType(3, value200)), callback);
    CHECK(
        results == Results{
            {grain2, GrainedTransformer::PolicyTransformedType(1, 310)},
            {grain1, GrainedTransformer::PolicyTransformedType(0, 110)}
        }
    );

    transformer.flush(callback);
    CHECK(
        results == Results{
            {grain2, GrainedTransformer::PolicyTransformedType(1, 310)},
            {grain1, GrainedTransformer::PolicyTransformedType(0, 110)},
            // Flush output is grouped by grain, but not necessarily in row order.
            {grain1, GrainedTransformer::PolicyTransformedType(3, 210)},
            {grain2, GrainedTransformer::PolicyTransformedType(2, 210)}
        }
    );
}

TEST_CASE("GrainedDelayDeltaTransformer - multi grain, delay 3") {
    // ----------------------------------------------------------------------
    constexpr size_t const Delay            = 3;

    using Transformer                       = DelayDeltaTransformer<Delay>;
    using GrainedTransformer                = GrainedDelayDeltaTransformer<Delay>;
    using Results                           = std::vector<typename GrainedTransformer::TransformedType>;
    // ----------------------------------------------------------------------

    std::string const                       grain1("one");
    std::string const                       grain2("two");
    std::uint64_t const                     value100(100);
    std::uint64_t const                     value200(200);
    std::uint64_t const                     value300(300);
    std::uint64_t const                     value400(400);
    std::uint64_t const                     value500(500);
    Results                                 results;

    auto const                              callback(
        [&results](typename GrainedTransformer::TransformedType output) {
            results.emplace_back(std::move(output));
        }
    );

    GrainedTransformer                      transformer(
        [](void) {
            return std::unique_ptr<Transformer>(new Transformer(10));
        },
        Delay
    );

    transformer.execute(GrainedTransformer::GrainedInputType(grain1, GrainedTransformer::PolicyInputType(0, value100)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain2, GrainedTransformer::PolicyInputType(1, value500)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain2, GrainedTransformer::PolicyInputType(2, value400)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain2, GrainedTransformer::PolicyInputType(3, value300)), callback);
    CHECK(results.empty());

    transformer.execute(GrainedTransformer::GrainedInputType(grain2, GrainedTransformer::PolicyInputType(4, value200)), callback);
    CHECK(
        results == Results{
            {grain2, GrainedTransformer::PolicyTransformedType(1, 510)}
        }
    );

    SECTION("Early flush") {
        transformer.flush(callback);
        CHECK(
            results == Results{
                {grain2, GrainedTransformer::PolicyTransformedType(1, 510)},
                {grain1, GrainedTransformer::PolicyTransformedType(0, 110)},
                {grain2, GrainedTransformer::PolicyTransformedType(2, 410)},
                {grain2, GrainedTransformer::PolicyTransformedType(3, 310)},
                {grain2, GrainedTransformer::PolicyTransformedType(4, 210)}
            }
        );
    }

    SECTION("Additional grain1 values") {
        transformer.execute(GrainedTransformer::GrainedInputType(grain1, GrainedTransformer::PolicyInputType(5, value200)), callback);
        CHECK(
            results == Results{
                {grain2, GrainedTransformer::PolicyTransformedType(1, 510)}
            }
        );

        transformer.execute(GrainedTransformer::GrainedInputType(grain1, GrainedTransformer::PolicyInputType(6, value300)), callback);
        CHECK(
            results == Results{
                {grain2, GrainedTransformer::PolicyTransformedType(1, 510)}
            }
        );

        transformer.execute(GrainedTransformer::GrainedInputType(grain1, GrainedTransformer::PolicyInputType(7, value400)), callback);
        CHECK(
            results == Results{
                {grain2, GrainedTransformer::PolicyTransformedType(1, 510)},
                {grain1, GrainedTransformer::PolicyTransformedType(0, 110)}
            }
        );

        transformer.execute(GrainedTransformer::GrainedInputType(grain1, GrainedTransformer::PolicyInputType(8, value500)), callback);
        CHECK(
            results == Results{
                {grain2, GrainedTransformer::PolicyTransformedType(1, 510)},
                {grain1, GrainedTransformer::PolicyTransformedType(0, 110)},
                {grain1, GrainedTransformer::PolicyTransformedType(5, 210)}
            }
        );

        transformer.flush(callback);
        CHECK(
            results == Results{
                {grain2, GrainedTransformer::PolicyTransformedType(1, 510)},
                {grain1, GrainedTransformer::PolicyTransformedType(0, 110)},
                {grain1, GrainedTransformer::PolicyTransformedType(5, 210)},
                {grain1, GrainedTransformer::PolicyTransformedType(6, 310)},
                {grain1, GrainedTransformer::PolicyTransformedType(7, 410)},
                {grain1, GrainedTransformer::PolicyTransformedType(8, 510)},
                {grain2, GrainedTransformer::PolicyTransformedType(2, 410)},
                {grain2, GrainedTransformer::PolicyTransformedType(3, 310)},
                {grain2, GrainedTransformer::PolicyTransformedType(4, 210)}
            }
        );
    }
}
