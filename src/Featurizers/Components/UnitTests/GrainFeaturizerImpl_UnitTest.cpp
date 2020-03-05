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
        "Test",
        pAllColumnAnnotations,
        [](NS::AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return SumTrainingOnlyEstimator<>(std::move(pAllColumnAnnotationsParam), 0);
        }
    );

    SECTION("Single grain") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);
    }

    SECTION("Multiple grains") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("two", 100),
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20),
                    std::make_tuple("two", 200),
                    std::make_tuple("three", 2000),
                    std::make_tuple("three", 1000)
                )
            )
        );

        REQUIRE(annotations.size() == 3);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 300);

        REQUIRE(annotations.find("three") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("three")->second).Value == 3000);
    }
}

TEST_CASE("Estimator - limited total training items") {
    // ----------------------------------------------------------------------
    using ThisSumTrainingOnlyEstimator      = SumTrainingOnlyEstimator<>;
    using Estimator                         = Components::GrainEstimatorImpl<std::string, ThisSumTrainingOnlyEstimator, 3>;
    using GrainEstimatorAnnotation          = Components::GrainEstimatorAnnotation<std::string>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    Estimator                               estimator(
        "Test",
        pAllColumnAnnotations,
        [](NS::AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return ThisSumTrainingOnlyEstimator(std::move(pAllColumnAnnotationsParam), 0);
        }
    );

    SECTION("Single grain, equal number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20),
                    std::make_tuple("one", 30)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 60);
    }

    SECTION("Single grain, smaller number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);
    }

    SECTION("Single grain, larger number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20),
                    std::make_tuple("one", 30),
                    std::make_tuple("one", 40)          // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 60);
    }

    // When the number of training items is limited at the grain level, it applies to all input regardless of grain
    SECTION("Multiple grain, small number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("two", 100)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 10);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 100);
    }

    SECTION("Multiple grain, equal number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("two", 100),
                    std::make_tuple("one", 20)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 100);
    }

    SECTION("Multiple grain, larger number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("two", 100),
                    std::make_tuple("one", 20),
                    std::make_tuple("two", 200)         // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 100);
    }

    SECTION("Multiple grain, larger number of items (new item after cutoff)") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("two", 100),
                    std::make_tuple("one", 20),
                    std::make_tuple("A New Grain!!", 0) // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 100);
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
        "Test",
        pAllColumnAnnotations,
        [](NS::AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return ThisSumTrainingOnlyEstimator(std::move(pAllColumnAnnotationsParam), 0);
        }
    );

    SECTION("Single grain, equal number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);
    }

    SECTION("Single grain, smaller number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10)
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 10);
    }

    SECTION("Single grain, larger number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20),
                    std::make_tuple("one", 30)          // This will be ignored
                )
            )
        );

        REQUIRE(annotations.size() == 1);
        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);
    }

    SECTION("Multiple grain, small number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("two", 100)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 10);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 100);
    }

    SECTION("Multiple grain, equal number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("two", 100),
                    std::make_tuple("one", 20),
                    std::make_tuple("two", 200)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 300);
    }

    SECTION("Multiple grain, larger number of items") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20),
                    std::make_tuple("two", 100),
                    std::make_tuple("one", 30),         // This will be ignored
                    std::make_tuple("two", 200)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);

        REQUIRE(annotations.find("two") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("two")->second).Value == 300);
    }

    SECTION("Multiple grain, larger number of items (new item after cutoff)") {
        GrainEstimatorAnnotation::AnnotationMap annotations(
            Test(
                estimator,
                NS::TestHelpers::make_vector<typename Estimator::InputType>(
                    std::make_tuple("one", 10),
                    std::make_tuple("one", 20),
                    std::make_tuple("one", 30),         // This will be ignored
                    std::make_tuple("A New Grain!!", 0)
                )
            )
        );

        REQUIRE(annotations.size() == 2);

        REQUIRE(annotations.find("one") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("one")->second).Value == 30);

        REQUIRE(annotations.find("A New Grain!!") != annotations.end());
        CHECK(ThisSumTrainingOnlyEstimator::get_annotation_data(*annotations.find("A New Grain!!")->second).Value == 0);
    }
}

template <typename TransformerT>
void Execute(TransformerT &transformer, std::string const &grain, std::uint64_t const &input, std::uint64_t expected) {
    transformer.execute(
        std::make_tuple(grain, input),
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
    Estimator                               estimator("Test", pAllColumnAnnotations);

    SECTION("Single grain") {
        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                std::make_tuple("one", 10),
                std::make_tuple("one", 20)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        Execute(*pTransformer, "one", 1, 31);
        Execute(*pTransformer, "one", 100, 130);
    }

    SECTION("Multi grain") {
        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                std::make_tuple("one", 10),
                std::make_tuple("two", 100),
                std::make_tuple("two", 200),
                std::make_tuple("one", 20)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        Execute(*pTransformer, "one", 1, 31);
        Execute(*pTransformer, "one", 100, 130);

        Execute(*pTransformer, "two", 1, 301);
        Execute(*pTransformer, "two", 1000, 1300);
    }

    SECTION("New Grain") {
        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                std::make_tuple("one", 10)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        CHECK_THROWS_WITH(
            pTransformer->execute(
                std::make_tuple("A New Grain!!", 100),
                [](std::tuple<std::string, std::uint64_t>) {}
            ),
            "Grain not found"
        );

        Execute(*pTransformer, "one", 1, 11);
        Execute(*pTransformer, "one", 100, 110);
    }

    SECTION("Archive") {
        Test(
            estimator,
            NS::TestHelpers::make_vector<typename Estimator::InputType>(
                std::make_tuple("one", 10),
                std::make_tuple("two", 100),
                std::make_tuple("two", 200),
                std::make_tuple("one", 20)
            ),
            false
        );

        typename Estimator::TransformerUniquePtr const  pTransformer(estimator.create_transformer());

        Execute(*pTransformer, "one", 1, 31);
        Execute(*pTransformer, "one", 100, 130);

        Execute(*pTransformer, "two", 1, 301);
        Execute(*pTransformer, "two", 1000, 1300);

        NS::Archive                         outArchive;

        pTransformer->save(outArchive);

        NS::Archive                         inArchive(outArchive.commit());

        Components::GrainTransformer<std::string, DeltaEstimator>           otherTransformer(inArchive);

        Execute(otherTransformer, "one", 1, 31);
        Execute(otherTransformer, "one", 100, 130);

        Execute(otherTransformer, "two", 1, 301);
        Execute(otherTransformer, "two", 1000, 1300);
    }
}

TEST_CASE("GrainTransformer - deserialization errors") {
    // ----------------------------------------------------------------------
    using GrainTransformer                  = Components::GrainTransformer<int, DeltaEstimator>;
    // ----------------------------------------------------------------------

    SECTION("Invalid number of items") {
        NS::Archive                         outArchive;

        NS::Traits<std::uint64_t>::serialize(outArchive, 0);

        NS::Archive                         inArchive(outArchive.commit());

        CHECK_THROWS_WITH(
            GrainTransformer(inArchive),
            "Invalid elements"
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
    using GrainTransformer                  = Components::GrainTransformer<int, DeltaEstimator>;
    // ----------------------------------------------------------------------

    CHECK_THROWS_WITH(
        GrainTransformer(typename GrainTransformer::TransformerMap()),
        "transformers"
    );
}

TEST_CASE("GrainEstimatorImpl - construct errors") {
    // ----------------------------------------------------------------------
    using GrainEstimator                    = Components::GrainEstimatorImpl<int, DeltaEstimator>;
    // ----------------------------------------------------------------------

    CHECK_THROWS_WITH(
        GrainEstimator("Test", NS::CreateTestAnnotationMapsPtr(1), typename GrainEstimator::CreateEstimatorFunc()),
        "createFunc"
    );
}
