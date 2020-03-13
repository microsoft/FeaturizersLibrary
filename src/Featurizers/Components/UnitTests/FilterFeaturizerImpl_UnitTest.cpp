// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include <ostream>
#include <tuple>

template <size_t IndexV, typename...Ts>
void PrintTupleElement(std::ostream &os, std::tuple<Ts...> const &value, typename std::enable_if<IndexV + 1 == sizeof...(Ts)>::type * =nullptr) {
    os << std::get<IndexV>(value);
}

template <size_t IndexV, typename... Ts>
void PrintTupleElement(std::ostream &os, std::tuple<Ts...> const &value, typename std::enable_if<IndexV + 1 != sizeof...(Ts)>::type * =nullptr) {
    os << std::get<IndexV>(value);
    os << ",";
    PrintTupleElement<IndexV + 1>(os, value);
}

template <typename... Ts>
std::ostream& operator <<(std::ostream& os, std::tuple<Ts...> const &value) {
    os << "<";

    PrintTupleElement<0>(os, value);

    os << ">";
    return os;
}

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
    using InputType                         = std::tuple<char const &, int const &>;

    using FilterTransformer =
        Components::FilterTransformer<
            SimpleSumTransformer,
            InputType,
            1
        >;

    using Results =                         std::vector<std::tuple<char const &, int const &, int>>;
    // ----------------------------------------------------------------------

    Results                                 results;
    auto const                              callback(
        [&results](typename Results::value_type output) {
            results.emplace_back(std::move(output));
        }
    );

    char const                              a('a');
    char const                              b('b');
    int const                               value10(10);
    int const                               value20(20);

    SECTION("Default constructor") {
        FilterTransformer                   transformer;

        transformer.execute(InputType(a, value10), callback);
        transformer.execute(InputType(b, value20), callback);

        CHECK(
            results == Results{
                typename Results::value_type(a, value10, 10),
                typename Results::value_type(b, value20, 20)
            }
        );
    }

    SECTION("Delta") {
        FilterTransformer                   transformer(100);

        transformer.execute(InputType(a, value10), callback);
        transformer.execute(InputType(b, value20), callback);

        CHECK(
            results == Results{
                typename Results::value_type(a, value10, 110),
                typename Results::value_type(b, value20, 120)
            }
        );
    }
}

TEST_CASE("SimpleSumTransformer - Serialization") {
    // ----------------------------------------------------------------------
    using FilterTransformer =
        Components::FilterTransformer<
            SimpleSumTransformer,
            std::tuple<char const &, int const &>,
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
    using InputType                         = std::tuple<int const &, char const &>;

    using FilterTransformer =
        Components::FilterTransformer<
            TupleOutTransformer,
            InputType,
            0
        >;

    using Results                           = std::vector<std::tuple<int const &, char const &, int, int>>;
    // ----------------------------------------------------------------------

    Results                                 results;
    auto const                              callback(
        [&results](typename Results::value_type value) {
            results.emplace_back(std::move(value));
        }
    );

    char const                              a('a');
    char const                              b('b');
    char const                              c('c');
    int const                               value10(10);
    int const                               value20(20);
    int const                               value30(30);

    FilterTransformer                       transformer;

    transformer.execute(InputType(value10, a), callback);
    transformer.execute(InputType(value20, b), callback);
    transformer.execute(InputType(value30, c), callback);

    CHECK(
        results == Results{
            typename Results::value_type(value10, a, 10, 10),
            typename Results::value_type(value20, b, 20, 20),
            typename Results::value_type(value30, c, 30, 30)
        }
    );
}

class TupleIdentityTransformer : public NS::StandardTransformer<std::tuple<char const &, int const &>, std::tuple<char, int>> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::StandardTransformer<std::tuple<char const &, int const &>, std::tuple<char, int>>;

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
    using InputType                         = std::tuple<int const &, int const &, char const &>;

    using FilterTransformer =
        Components::FilterTransformer<
            TupleIdentityTransformer,
            InputType,
            2, 1
        >;

    using Results                           = std::vector<std::tuple<int const &, int const &, char const &, char, int>>;
    // ----------------------------------------------------------------------

    Results                                 results;
    auto const                              callback(
        [&results](typename Results::value_type value) {
            results.emplace_back(std::move(value));
        }
    );

    char const                              a('a');
    char const                              b('b');
    char const                              c('c');
    int const                               value10(10);
    int const                               value20(20);
    int const                               value30(30);
    int const                               value40(40);
    int const                               value50(50);
    int const                               value60(60);

    FilterTransformer                       transformer;

    transformer.execute(InputType(value10, value20, a), callback);
    transformer.execute(InputType(value30, value40, b), callback);
    transformer.execute(InputType(value50, value60, c), callback);

    CHECK(
        results == Results{
            typename Results::value_type(value10, value20, a, 'a', 20),
            typename Results::value_type(value30, value40, b, 'b', 40),
            typename Results::value_type(value50, value60, c, 'c', 60)
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
    using InputType                         = std::tuple<char const &, int const &>;

    using FilterEstimator =
        Components::FilterEstimatorImpl<
            SimpleEstimator,
            InputType,
            1
        >;

    // ----------------------------------------------------------------------

    SECTION("No Constructor Args") {
        FilterEstimator                     estimator(NS::CreateTestAnnotationMapsPtr(1));

        CHECK(strcmp(estimator.Name, "FilterSimpleEstimator") == 0);

        estimator.begin_training();
        CHECK(estimator.get_estimator().LastValue == 0);

        estimator.fit(InputType('a', 10));
        CHECK(estimator.get_estimator().LastValue == 10);

        estimator.fit(InputType('b', 20));
        CHECK(estimator.get_estimator().LastValue == 20);
    }

    SECTION("Constructor Args") {
        FilterEstimator                     estimator(NS::CreateTestAnnotationMapsPtr(1), 999);

        CHECK(strcmp(estimator.Name, "FilterSimpleEstimator") == 0);

        estimator.begin_training();
        CHECK(estimator.get_estimator().LastValue == 999);

        estimator.fit(InputType('a', 10));
        CHECK(estimator.get_estimator().LastValue == 10);

        estimator.fit(InputType('b', 20));
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
    using InputType                         = std::tuple<int const &, char const &>;

    using FilterEstimator =
        Components::FilterEstimatorImpl<
            SimpleSumTransformerEstimator,
            InputType,
            0
        >;

    using Results                       = std::vector<std::tuple<int const &, char const &, int>>;
    // ----------------------------------------------------------------------

    char const                              a('a');
    char const                              b('b');
    char const                              c('c');
    char const                              d('d');
    int const                               value10(10);
    int const                               value20(20);
    int const                               value100(100);
    int const                               value200(200);
    int const                               value300(300);
    int const                               value400(400);

    // All transformations will be incremented by the sum of all values
    // encountered during training.
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            FilterEstimator(NS::CreateTestAnnotationMapsPtr(1)),
            {
                InputType(value10, a),
                InputType(value20, b)
            },
            {
                InputType(value100, a),
                InputType(value200, b),
                InputType(value300, c),
                InputType(value400, d)
            }
        ) == Results{
            typename Results::value_type(value100, a, 130),
            typename Results::value_type(value200, b, 230),
            typename Results::value_type(value300, c, 330),
            typename Results::value_type(value400, d, 430)
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
    using InputType                         = std::tuple<char const &, int const &>;

    using FilterEstimator =
        Components::FilterEstimatorImpl<
            TupleOutTransformerEstimator,
            InputType,
            1
        >;

    using Results                       = std::vector<std::tuple<char const &, int const &, int, int>>;
    // ----------------------------------------------------------------------

    char const                              a('a');
    char const                              b('b');
    char const                              c('c');
    char const                              d('d');
    int const                               value100(100);
    int const                               value200(200);
    int const                               value300(300);
    int const                               value400(400);

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            FilterEstimator(NS::CreateTestAnnotationMapsPtr(1)),
            std::vector<std::tuple<char const &, int const &>>(),
            {
                InputType(a, value100),
                InputType(b, value200),
                InputType(c, value300),
                InputType(d, value400)
            }
        ) == Results{
            typename Results::value_type(a, value100, 100, 100),
            typename Results::value_type(b, value200, 200, 200),
            typename Results::value_type(c, value300, 300, 300),
            typename Results::value_type(d, value400, 400, 400)
        }
    );
}

class TupleIdentityTransformerEstimator : public NS::TransformerEstimator<std::tuple<char const &, int const &>, std::tuple<char, int>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = NS::TransformerEstimator<std::tuple<char const &, int const &>, std::tuple<char, int>>;
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
    using InputType                         = std::tuple<char const &, char const &, int const &>;

    using FilterEstimator =
        Components::FilterEstimatorImpl<
            TupleIdentityTransformerEstimator,
            InputType,
            1, 2
        >;

    using Results                       = std::vector<std::tuple<char const &, char const &, int const &, char, int>>;
    // ----------------------------------------------------------------------

    char const                              a('a');
    char const                              b('b');
    char const                              c('c');
    char const                              d('d');
    char const                              e('e');
    char const                              f('f');
    char const                              g('g');
    char const                              h('h');
    int const                               value100(100);
    int const                               value200(200);
    int const                               value300(300);
    int const                               value400(400);

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            FilterEstimator(NS::CreateTestAnnotationMapsPtr(1)),
            std::vector<std::tuple<char const &, char const &, int const &>>(),
            {
                InputType(a, b, value100),
                InputType(c, d, value200),
                InputType(e, f, value300),
                InputType(g, h, value400)
            }
        ) == Results{
            typename Results::value_type(a, b, value100, 'b', 100),
            typename Results::value_type(c, d, value200, 'd', 200),
            typename Results::value_type(e, f, value300, 'f', 300),
            typename Results::value_type(g, h, value400, 'h', 400)
        }
    );
}
