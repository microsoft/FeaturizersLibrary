// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../FilterFeaturizerImpl.h"

#include "../../TestHelpers.h"
#include "../../../Archive.h"

namespace NS                                = Microsoft::Featurizer;
namespace Components                        = Microsoft::Featurizer::Featurizers::Components;

class SimpleSumTransformer : public NS::StandardTransformer<int, int> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::StandardTransformer<int, int>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    SimpleSumTransformer(int delta=0) : _delta(delta) {}
    SimpleSumTransformer(Archive &ar) : SimpleSumTransformer(NS::Traits<int>::deserialize(ar)) {}
    ~SimpleSumTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleSumTransformer);

    bool operator==(SimpleSumTransformer const &other) const {
        return _delta == other._delta;
    }

    bool operator!=(SimpleSumTransformer const &other) const {
        return (*this == other) == false;
    }

    void save(Archive &ar) const override {
        NS::Traits<int>::serialize(ar, _delta);
    }

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    int const                               _delta;

    // ----------------------------------------------------------------------
    // |  Private Methods
    void execute_impl(typename BaseType::InputType const &value, typename BaseType::CallbackFunction const &callback) override {
        callback(value + _delta);
    }
};

TEST_CASE("SimpleSumTransformer") {
    // ----------------------------------------------------------------------
    using FilterTransformer =
        Components::FilterTransformer<
            SimpleSumTransformer,
            std::tuple<char, int>,
            1
        >;

    using Results =                         std::vector<std::tuple<char, int, int>>;
    // ----------------------------------------------------------------------

    Results                                 results;
    auto const                              callback(
        [&results](std::tuple<char, int, int> output) {
            results.emplace_back(std::move(output));
        }
    );

    SECTION("Default constructor") {
        FilterTransformer                   transformer;

        transformer.execute(std::make_tuple('a', 10), callback);
        transformer.execute(std::make_tuple('b', 20), callback);

        CHECK(
            results == Results{
                typename Results::value_type('a', 10, 10),
                typename Results::value_type('b', 20, 20)
            }
        );
    }

    SECTION("Delta") {
        FilterTransformer                   transformer(100);

        transformer.execute(std::make_tuple('a', 10), callback);
        transformer.execute(std::make_tuple('b', 20), callback);

        CHECK(
            results == Results{
                typename Results::value_type('a', 10, 110),
                typename Results::value_type('b', 20, 120)
            }
        );
    }
}

TEST_CASE("SimpleSumTransformer - Serialization") {
    // ----------------------------------------------------------------------
    using FilterTransformer =
        Components::FilterTransformer<
            SimpleSumTransformer,
            std::tuple<char, int>,
            1
        >;

    // ----------------------------------------------------------------------

    FilterTransformer const                 transformer(10);

    CHECK(transformer == FilterTransformer(10));
    CHECK(transformer != FilterTransformer());

    NS::Archive                             out;

    transformer.save(out);

    NS::Archive::ByteArray const            bytes(out.commit());
    NS::Archive                             in(bytes);

    FilterTransformer const                 other(in);

    CHECK(other == transformer);
}

class TupleOutTransformer : public NS::StandardTransformer<int, std::tuple<int, int>> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::StandardTransformer<int, std::tuple<int, int>>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    TupleOutTransformer(void) = default;
    ~TupleOutTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TupleOutTransformer);

    void save(NS::Archive &) const override {}

private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(std::make_tuple(input, input));
    }
};

TEST_CASE("TupleOutTransformer") {
    // ----------------------------------------------------------------------
    using FilterTransformer =
        Components::FilterTransformer<
            TupleOutTransformer,
            std::tuple<int, char>,
            0
        >;

    using Results                           = std::vector<std::tuple<int, char, int, int>>;
    // ----------------------------------------------------------------------

    Results                                 results;
    auto const                              callback(
        [&results](typename Results::value_type value) {
            results.emplace_back(std::move(value));
        }
    );

    FilterTransformer                       transformer;

    transformer.execute(std::make_tuple(10, 'a'), callback);
    transformer.execute(std::make_tuple(20, 'b'), callback);
    transformer.execute(std::make_tuple(30, 'c'), callback);

    CHECK(
        results == Results{
            typename Results::value_type(10, 'a', 10, 10),
            typename Results::value_type(20, 'b', 20, 20),
            typename Results::value_type(30, 'c', 30, 30)
        }
    );
}

class TupleIdentityTransformer : public NS::StandardTransformer<std::tuple<char, int>, std::tuple<char, int>> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::StandardTransformer<std::tuple<char, int>, std::tuple<char, int>>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    TupleIdentityTransformer(void) = default;
    ~TupleIdentityTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TupleIdentityTransformer);

    void save(NS::Archive &) const override {}

private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(input);
    }
};

TEST_CASE("TupleIdentityTransformer") {
    // ----------------------------------------------------------------------
    using FilterTransformer =
        Components::FilterTransformer<
            TupleIdentityTransformer,
            std::tuple<int, int, char>,
            2, 1
        >;

    using Results                           = std::vector<std::tuple<int, int, char, char, int>>;
    // ----------------------------------------------------------------------

    Results                                 results;
    auto const                              callback(
        [&results](typename Results::value_type value) {
            results.emplace_back(std::move(value));
        }
    );

    FilterTransformer                       transformer;

    transformer.execute(std::make_tuple(10, 20, 'a'), callback);
    transformer.execute(std::make_tuple(30, 40, 'b'), callback);
    transformer.execute(std::make_tuple(50, 60, 'c'), callback);

    CHECK(
        results == Results{
            typename Results::value_type(10, 20, 'a', 'a', 20),
            typename Results::value_type(30, 40, 'b', 'b', 40),
            typename Results::value_type(50, 60, 'c', 'c', 60)
        }
    );
}

class SimpleEstimator : public NS::FitEstimator<int> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::FitEstimator<int>;

    // ----------------------------------------------------------------------
    // |  Public Data
    int                                     LastValue;

    // ----------------------------------------------------------------------
    // |  Public Methods
    SimpleEstimator(NS::AnnotationMapsPtr pAnnotations, int initialValue=0) :
        BaseType("SimpleEstimator", std::move(pAnnotations)),
        LastValue(initialValue) {
    }

    ~SimpleEstimator(void) override = default;

private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    bool begin_training_impl(void) override { return true; }
    NS::FitResult fit_impl(typename BaseType::InputType const *pItems, size_t cItems) override {
        typename BaseType::InputType const * const      pEnd(pItems + cItems);

        while(pItems != pEnd)
            LastValue = *pItems++;

        return NS::FitResult::Continue;
    }
    void complete_training_impl(void) override {}
};

TEST_CASE("SimpleEstimator") {
    // ----------------------------------------------------------------------
    using FilterEstimator =
        Components::FilterEstimatorImpl<
            SimpleEstimator,
            std::tuple<char, int>,
            1
        >;

    // ----------------------------------------------------------------------

    SECTION("No Constructor Args") {
        FilterEstimator                     estimator(NS::CreateTestAnnotationMapsPtr(1));

        CHECK(strcmp(estimator.Name, "FilterSimpleEstimator") == 0);

        estimator.begin_training();
        CHECK(estimator.get_estimator().LastValue == 0);

        estimator.fit(std::make_tuple('a', 10));
        CHECK(estimator.get_estimator().LastValue == 10);

        estimator.fit(std::make_tuple('b', 20));
        CHECK(estimator.get_estimator().LastValue == 20);
    }

    SECTION("Constructor Args") {
        FilterEstimator                     estimator(NS::CreateTestAnnotationMapsPtr(1), 999);

        CHECK(strcmp(estimator.Name, "FilterSimpleEstimator") == 0);

        estimator.begin_training();
        CHECK(estimator.get_estimator().LastValue == 999);

        estimator.fit(std::make_tuple('a', 10));
        CHECK(estimator.get_estimator().LastValue == 10);

        estimator.fit(std::make_tuple('b', 20));
        CHECK(estimator.get_estimator().LastValue == 20);
    }
}

class SimpleSumTransformerEstimator : public NS::TransformerEstimator<int, int> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = NS::TransformerEstimator<int, int>;
    using TransformerType                   = SimpleSumTransformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SimpleSumTransformerEstimator(NS::AnnotationMapsPtr pAnnotations, int delta=0) :
        BaseType("SimpleSumTransformerEstimtor", std::move(pAnnotations)),
        _delta(delta)
    {}

    ~SimpleSumTransformerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleSumTransformerEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    int                                     _delta;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override { return true; }
    void complete_training_impl(void) override {}

    NS::FitResult fit_impl(typename BaseType::InputType const *pItems, size_t cItems) override {
        typename BaseType::InputType const * const      pEnd(pItems + cItems);

        while(pItems != pEnd)
            _delta += *pItems++;

        return NS::FitResult::Continue;
    }

    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType(std::move(_delta)));
    }
};

TEST_CASE("SimpleSumTransformerEstimator") {
    // ----------------------------------------------------------------------
    using FilterEstimator =
        Components::FilterEstimatorImpl<
            SimpleSumTransformerEstimator,
            std::tuple<int, char>,
            0
        >;

    using Results                       = std::vector<std::tuple<int, char, int>>;
    // ----------------------------------------------------------------------

    // All transformations will be incremented by the sum of all values
    // encountered during training.
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            FilterEstimator(NS::CreateTestAnnotationMapsPtr(1)),
            {
                std::make_tuple(10, 'a'),
                std::make_tuple(20, 'b')
            },
            {
                std::make_tuple(100, 'a'),
                std::make_tuple(200, 'b'),
                std::make_tuple(300, 'c'),
                std::make_tuple(400, 'd')
            }
        ) == Results{
            typename Results::value_type(100, 'a', 130),
            typename Results::value_type(200, 'b', 230),
            typename Results::value_type(300, 'c', 330),
            typename Results::value_type(400, 'd', 430)
        }
    );
}

class TupleOutTransformerEstimator : public NS::TransformerEstimator<int, std::tuple<int, int>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = NS::TransformerEstimator<int, std::tuple<int, int>>;
    using TransformerType                   = TupleOutTransformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TupleOutTransformerEstimator(NS::AnnotationMapsPtr pAnnotations) :
        BaseType("TupleOutTransformerEstimator", std::move(pAnnotations))
    {}

    ~TupleOutTransformerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TupleOutTransformerEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override { return false; }
    void complete_training_impl(void) override {}

    NS::FitResult fit_impl(typename BaseType::InputType const *, size_t) override {
        throw std::runtime_error("This will never be called");
    }

    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType());
    }
};

TEST_CASE("TupleOutTransformerEstimator") {
    // ----------------------------------------------------------------------
    using FilterEstimator =
        Components::FilterEstimatorImpl<
            TupleOutTransformerEstimator,
            std::tuple<char, int>,
            1
        >;

    using Results                       = std::vector<std::tuple<char, int, int, int>>;
    // ----------------------------------------------------------------------

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            FilterEstimator(NS::CreateTestAnnotationMapsPtr(1)),
            std::vector<std::tuple<char, int>>(),
            {
                std::make_tuple('a', 100),
                std::make_tuple('b', 200),
                std::make_tuple('c', 300),
                std::make_tuple('d', 400)
            }
        ) == Results{
            typename Results::value_type('a', 100, 100, 100),
            typename Results::value_type('b', 200, 200, 200),
            typename Results::value_type('c', 300, 300, 300),
            typename Results::value_type('d', 400, 400, 400)
        }
    );
}

class TupleIdentityTransformerEstimator : public NS::TransformerEstimator<std::tuple<char, int>, std::tuple<char, int>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = NS::TransformerEstimator<std::tuple<char, int>, std::tuple<char, int>>;
    using TransformerType                   = TupleIdentityTransformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TupleIdentityTransformerEstimator(NS::AnnotationMapsPtr pAnnotations) :
        BaseType("TupleIdentityTransformerEstimator", std::move(pAnnotations))
    {}

    ~TupleIdentityTransformerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TupleIdentityTransformerEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override { return false; }
    void complete_training_impl(void) override {}

    NS::FitResult fit_impl(typename BaseType::InputType const *, size_t) override {
        throw std::runtime_error("This will never be called");
    }

    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType());
    }
};

TEST_CASE("TupleIdentityTransformerEstimator") {
    // ----------------------------------------------------------------------
    using FilterEstimator =
        Components::FilterEstimatorImpl<
            TupleIdentityTransformerEstimator,
            std::tuple<char, char, int>,
            1, 2
        >;

    using Results                       = std::vector<std::tuple<char, char, int, char, int>>;
    // ----------------------------------------------------------------------

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            FilterEstimator(NS::CreateTestAnnotationMapsPtr(1)),
            std::vector<std::tuple<char, char, int>>(),
            {
                std::make_tuple('a', 'b', 100),
                std::make_tuple('c', 'd', 200),
                std::make_tuple('e', 'f', 300),
                std::make_tuple('g', 'h', 400)
            }
        ) == Results{
            typename Results::value_type('a', 'b', 100, 'b', 100),
            typename Results::value_type('c', 'd', 200, 'd', 200),
            typename Results::value_type('e', 'f', 300, 'f', 300),
            typename Results::value_type('g', 'h', 400, 'h', 400)
        }
    );
}
