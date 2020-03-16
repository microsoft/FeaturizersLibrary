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

#include "../FilterDecoratorFeaturizer.h"

#include "../../TestHelpers.h"
#include "../../../Archive.h"

namespace NS                                = Microsoft::Featurizer;
namespace Components                        = Microsoft::Featurizer::Featurizers::Components;

TEST_CASE("Single element transformer") {
    // ----------------------------------------------------------------------
    using InputType                         = std::tuple<int const &, char>;

    using FilterDecoratorTransformer =
        Components::FilterDecoratorTransformer<
            InputType,
            1
        >;
    // ----------------------------------------------------------------------

    static_assert(std::is_same<typename FilterDecoratorTransformer::TransformedType, char>::value, "");

    FilterDecoratorTransformer              transformer;

    CHECK(transformer.execute(InputType(1, 'a')) == 'a');
    CHECK(transformer.execute(InputType(2, 'b')) == 'b');
}

TEST_CASE("Multi element transformer") {
    // ----------------------------------------------------------------------
    using InputType                         = std::tuple<int const &, int, char, char>;

    using FilterDecoratorTransformer =
        Components::FilterDecoratorTransformer<
            InputType,
            1, 3, 2
        >;
    // ----------------------------------------------------------------------

    static_assert(std::is_same<typename FilterDecoratorTransformer::TransformedType, std::tuple<int, char, char>>::value, "");

    FilterDecoratorTransformer              transformer;

    CHECK(transformer.execute(InputType(10, 20, 'a', 'b')) == std::make_tuple(20, 'b', 'a'));
    CHECK(transformer.execute(InputType(30, 40, 'c', 'd')) == std::make_tuple(40, 'd', 'c'));
}

TEST_CASE("Estimator") {
    // ----------------------------------------------------------------------
    using InputType                         = std::tuple<int const &, char, char>;

    using FilterDecoratorEstimator =
        Components::FilterDecoratorEstimator<
            InputType,
            2
        >;

    using Results                           = std::vector<typename FilterDecoratorEstimator::TransformedType>;
    // ----------------------------------------------------------------------

    FilterDecoratorEstimator                estimator(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(strcmp(estimator.Name, "FilterDecoratorEstimator") == 0);

    CHECK(estimator.get_state() == NS::TrainingState::Pending);

    estimator.begin_training();
    CHECK(estimator.get_state() == NS::TrainingState::Finished);

    estimator.complete_training();
    CHECK(estimator.get_state() == NS::TrainingState::Completed);

    auto                                    pTransformer(estimator.create_transformer());
    Results                                 results;
    auto const                              callback(
        [&results](typename Results::value_type value) {
            results.emplace_back(std::move(value));
        }
    );

    pTransformer->execute(InputType(10, 'a', 'b'), callback);
    pTransformer->execute(InputType(20, 'c', 'd'), callback);
    pTransformer->execute(InputType(30, 'e', 'f'), callback);

    CHECK(results == Results{'b', 'd', 'f'});
}
