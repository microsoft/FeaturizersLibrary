// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../PipelineExecutionEstimatorImpl.h"
#include "../InferenceOnlyFeaturizerImpl.h"
#include "../../TestHelpers.h"
#include "../../../Archive.h"

namespace NS = Microsoft::Featurizer;

template <typename T>
struct NonCopyable {
    using Type = T;

    T                                       Value;

    NonCopyable(T value) : Value(std::move(value)) {}
    ~NonCopyable(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NonCopyable);

    bool operator ==(NonCopyable const &other) const {
        return Value == other.Value;
    }
};

template <typename T>
NonCopyable<T> make_noncopyable(T value) {
    return NonCopyable<T>(std::move(value));
}

template <typename T>
class MyAnnotation : public NS::Annotation {
public:
    T const                                 Value;

    MyAnnotation(T value) :
        Value(std::move(value)) {
    }

    ~MyAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyAnnotation);
};

template <typename T, size_t ColIndexV, size_t MaxRowsV=100000>
class MyAnnotationEstimator : public NS::FitEstimator<T> {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    MyAnnotationEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations) :
        NS::FitEstimator<T>("MyAnnotationEstimator", std::move(pAllColumnAnnotations)),
        _remaining(MaxRowsV) {
    }

    T const & GetMostCommonValue(void) const {
        T const * const                     ptr(GetMostCommonValueNoThrow());

        if(ptr == nullptr)
            throw std::runtime_error("The annotation does not exist");

        return *ptr;
    }

    T const * GetMostCommonValueNoThrow(void) const {
        MyAnnotation<T> const * const       ptr(BaseType::template get_annotation_impl<MyAnnotation<T>>(ColIndexV));

        if(ptr == nullptr)
            return nullptr;

        return &ptr->Value;
    }

private:
    // ----------------------------------------------------------------------
    // |  Private Types
    template <typename U>
    struct InternalValueTraits {
        using Type = U;

        static U const & get_value(U const &value) { return value; }
    };

    template <typename U>
    struct InternalValueTraits<NonCopyable<U>> {
        using Type = U;

        static U const & get_value(NonCopyable<U> const &value) { return value.Value; }
    };

    using BaseType                          = NS::FitEstimator<T>;
    using CountMap                          = std::map<typename InternalValueTraits<T>::Type, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |  Private Data
    size_t                                  _remaining;
    CountMap                                _map;

    // ----------------------------------------------------------------------
    // |  Private Methods
    bool begin_training_impl(void) override {
        return true;
    }

    NS::FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t cBuffer) override {
        typename BaseType::InputType const * const      pEndBuffer(pBuffer + cBuffer);

        while(pBuffer != pEndBuffer) {
            T const &                                   input(*pBuffer++);
            typename CountMap::iterator const           iter(
                [this, &input](void) -> typename CountMap::iterator {
                    typename CountMap::iterator const   i(_map.find(InternalValueTraits<T>::get_value(input)));

                    if(i != _map.end())
                        return i;

                    std::pair<typename CountMap::iterator, bool> const      result(_map.insert(std::make_pair(InternalValueTraits<T>::get_value(input), 0)));

                    return result.first;
                }()
            );

            iter->second += 1;

            if(--_remaining == 0)
                return NS::FitResult::Complete;
        }

        return NS::FitResult::Continue;
    }

    void complete_training_impl(void) override {
        // Find the most common value in the map
        typename CountMap::iterator         iMostCommon(_map.end());

        for(typename CountMap::iterator iter=_map.begin(); iter != _map.end(); ++iter) {
            if(iMostCommon == _map.end() || iter->second >= iMostCommon->second) {
                iMostCommon = iter;
            }
        }
        assert(iMostCommon != _map.end());

        BaseType::add_annotation(std::make_shared<MyAnnotation<T>>(iMostCommon->first), ColIndexV);

        _map.clear();
    }
};

class StringToIntTransformer : public NS::Featurizers::Components::InferenceOnlyTransformerImpl<NonCopyable<std::string>, NonCopyable<size_t>> {
private:
    void execute_impl(InputType const &input, CallbackFunction const &callback) override {
        callback(input.Value.size());
    }
};

class StringToIntEstimator : public NS::Featurizers::Components::InferenceOnlyEstimatorImpl<StringToIntTransformer> {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    StringToIntEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations) :
        NS::Featurizers::Components::InferenceOnlyEstimatorImpl<StringToIntTransformer>("StringToIntEstimator", std::move(pAllColumnAnnotations)) {
    }

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StringToIntEstimator);
};

class IntToStringTransformer : public NS::Featurizers::Components::InferenceOnlyTransformerImpl<NonCopyable<size_t>, NonCopyable<std::string>> {
private:
    void execute_impl(InputType const &input, CallbackFunction const &callback) override {
        callback(std::to_string(input.Value));
    }
};

class IntToStringEstimator : public NS::Featurizers::Components::InferenceOnlyEstimatorImpl<IntToStringTransformer> {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    IntToStringEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations) :
        NS::Featurizers::Components::InferenceOnlyEstimatorImpl<IntToStringTransformer>("IntToStringEstimator", std::move(pAllColumnAnnotations)) {
    }

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(IntToStringEstimator);
};

TEST_CASE("Single Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        StringToIntEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            NS::TestHelpers::make_vector<std::vector<NonCopyable<std::string>>>(),
            NS::TestHelpers::make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == NS::TestHelpers::make_vector<NonCopyable<size_t>>(3, 3, 5)
    );
    CHECK((*pAllColumnAnnotations)[0].empty());
}

TEST_CASE("Annotation, Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        MyAnnotationEstimator<NonCopyable<std::string>, 0>,
        StringToIntEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            NS::TestHelpers::make_vector<std::vector<NonCopyable<std::string>>>(
                NS::TestHelpers::make_vector<NonCopyable<std::string>>("one", "two", "two", "one", "one")
            ),
            NS::TestHelpers::make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == NS::TestHelpers::make_vector<NonCopyable<size_t>>(3, 3, 5)
    );

    NS::AnnotationMap const &               annotations((*pAllColumnAnnotations)[0]);

    REQUIRE(annotations.size() == 1);

    NS::AnnotationMap::const_iterator const             iterAnnotations(annotations.find("MyAnnotationEstimator"));

    REQUIRE(iterAnnotations != annotations.end());
    REQUIRE(iterAnnotations->second.size() == 1);

    NS::Annotation const &                  annotation(*iterAnnotations->second[0]);

    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation));

    MyAnnotation<NonCopyable<std::string>> const &      myAnnotation(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation));

    CHECK(myAnnotation.Value.Value == "one");
}

TEST_CASE("Annotation, Annotation, Annotation, Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        MyAnnotationEstimator<NonCopyable<std::string>, 0>,
        MyAnnotationEstimator<NonCopyable<std::string>, 0, 4>,
        MyAnnotationEstimator<NonCopyable<std::string>, 0>,
        StringToIntEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            NS::TestHelpers::make_vector<std::vector<NonCopyable<std::string>>>(
                // Note that the values have been carefully selected to ensure that batches are properly reset
                // when an estimator reports that it no longer needs any data (which will happen
                // in this test when the 2nd estimator sees the first 4 items).
                NS::TestHelpers::make_vector<NonCopyable<std::string>>("three", "one", "two", "one", "three", "three", "three"),
                NS::TestHelpers::make_vector<NonCopyable<std::string>>("two", "two")
            ),
            NS::TestHelpers::make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == NS::TestHelpers::make_vector<NonCopyable<size_t>>(3, 3, 5)
    );

    NS::AnnotationMap const &               annotations((*pAllColumnAnnotations)[0]);

    REQUIRE(annotations.size() == 1);

    NS::AnnotationMap::const_iterator const             iter(annotations.find("MyAnnotationEstimator"));

    REQUIRE(iter != annotations.end());

    // There are 2 annotation instances. The first is configured to look at all the
    // training data while the second is only looking at the first 3 times. They
    // will get different results because of this.
    REQUIRE(iter->second.size() == 3);

    NS::Annotation const &                  annotation1(*iter->second[0]);
    NS::Annotation const &                  annotation2(*iter->second[1]);
    NS::Annotation const &                  annotation3(*iter->second[2]);

    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation1));
    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation2));
    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation3));

    MyAnnotation<NonCopyable<std::string>> const &      mine1(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation1));
    MyAnnotation<NonCopyable<std::string>> const &      mine2(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation2));
    MyAnnotation<NonCopyable<std::string>> const &      mine3(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation3));

    CHECK(mine1.Value.Value == "three");
    CHECK(mine2.Value.Value == "one");
    CHECK(mine3.Value.Value == "three"); // This test will fail if batches aren't being properly reset
}

TEST_CASE("Transformer, Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        StringToIntEstimator,
        IntToStringEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            NS::TestHelpers::make_vector<std::vector<NonCopyable<std::string>>>(),
            NS::TestHelpers::make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == NS::TestHelpers::make_vector<NonCopyable<std::string>>("3", "3", "5")
    );
    CHECK((*pAllColumnAnnotations)[0].empty());
}

TEST_CASE("Transformer, Annotation, Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        IntToStringEstimator,
        MyAnnotationEstimator<NonCopyable<std::string>, 0>,
        StringToIntEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            NS::TestHelpers::make_vector<std::vector<NonCopyable<size_t>>>(
                NS::TestHelpers::make_vector<NonCopyable<size_t>>(1000, 200, 30, 4),
                NS::TestHelpers::make_vector<NonCopyable<size_t>>(1111, 222, 33, 4)
            ),
            NS::TestHelpers::make_vector<NonCopyable<size_t>>(1000, 200, 30, 4)
             // The output will be the lengths of each number string
        ) == NS::TestHelpers::make_vector<NonCopyable<size_t>>(4, 3, 2, 1)
    );

    NS::AnnotationMap const &               annotations((*pAllColumnAnnotations)[0]);

    REQUIRE(annotations.size() == 1);

    NS::AnnotationMap::const_iterator const             iterAnnotations(annotations.find("MyAnnotationEstimator"));

    REQUIRE(iterAnnotations != annotations.end());
    REQUIRE(iterAnnotations->second.size() == 1);

    NS::Annotation const &                  annotation(*iterAnnotations->second[0]);

    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation));

    MyAnnotation<NonCopyable<std::string>> const &      myAnnotation(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation));

    CHECK(myAnnotation.Value.Value == "4");
}

TEST_CASE("Transformer, Annotation") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        IntToStringEstimator,
        MyAnnotationEstimator<NonCopyable<std::string>, 0>
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            NS::TestHelpers::make_vector<std::vector<NonCopyable<size_t>>>(
                NS::TestHelpers::make_vector<NonCopyable<size_t>>(1000, 200, 30, 4),
                NS::TestHelpers::make_vector<NonCopyable<size_t>>(1111, 222, 33, 4)
            ),
            NS::TestHelpers::make_vector<NonCopyable<size_t>>(1000, 200, 30, 4)
        ) == NS::TestHelpers::make_vector<NonCopyable<std::string>>("1000", "200", "30", "4")
    );

    NS::AnnotationMap const &               annotations((*pAllColumnAnnotations)[0]);

    REQUIRE(annotations.size() == 1);

    NS::AnnotationMap::const_iterator const             iterAnnotations(annotations.find("MyAnnotationEstimator"));

    REQUIRE(iterAnnotations != annotations.end());
    REQUIRE(iterAnnotations->second.size() == 1);

    NS::Annotation const &                  annotation(*iterAnnotations->second[0]);

    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation));

    MyAnnotation<NonCopyable<std::string>> const &      myAnnotation(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation));

    CHECK(myAnnotation.Value.Value == "4");
}

TEST_CASE("Annotation, Annotation, Transformer, Annotation") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        MyAnnotationEstimator<NonCopyable<size_t>, 0>,
        MyAnnotationEstimator<NonCopyable<size_t>, 0, 3>,
        IntToStringEstimator,
        MyAnnotationEstimator<NonCopyable<std::string>, 0>
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            NS::TestHelpers::make_vector<std::vector<NonCopyable<size_t>>>(
                NS::TestHelpers::make_vector<NonCopyable<size_t>>(1000, 200, 30, 4),
                NS::TestHelpers::make_vector<NonCopyable<size_t>>(111, 222, 33, 4)
            ),
            NS::TestHelpers::make_vector<NonCopyable<size_t>>(1000, 200, 30, 4)
        ) == NS::TestHelpers::make_vector<NonCopyable<std::string>>("1000", "200", "30", "4")
    );

    NS::AnnotationMap const &               annotations((*pAllColumnAnnotations)[0]);

    REQUIRE(annotations.size() == 1);

    NS::AnnotationMap::const_iterator const             iterAnnotations(annotations.find("MyAnnotationEstimator"));

    REQUIRE(iterAnnotations != annotations.end());

    // There are 3 annotation instances.
    REQUIRE(iterAnnotations->second.size() == 3);

    NS::Annotation const &                  annotation1(*iterAnnotations->second[0]);
    NS::Annotation const &                  annotation2(*iterAnnotations->second[1]);
    NS::Annotation const &                  annotation3(*iterAnnotations->second[2]);

    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<size_t>> const *>(&annotation1));
    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<size_t>> const *>(&annotation2));
    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation3));

    MyAnnotation<NonCopyable<size_t>> const &           myAnnotation1(static_cast<MyAnnotation<NonCopyable<size_t>> const &>(annotation1));
    MyAnnotation<NonCopyable<size_t>> const &           myAnnotation2(static_cast<MyAnnotation<NonCopyable<size_t>> const &>(annotation2));
    MyAnnotation<NonCopyable<std::string>> const &      myAnnotation3(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation3));

    CHECK(myAnnotation1.Value.Value == 4);
    CHECK(myAnnotation2.Value.Value == 1000);
    CHECK(myAnnotation3.Value.Value == "4");
}

class SimpleEstimator : public NS::TransformerEstimator<int, double> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::TransformerEstimator<int, double>;

    class Transformer : public NS::Transformer<int, double> {
    public:
        Transformer(double delta) : _delta(delta) {}
        Transformer(Archive &) {}

        void save(Archive &) const override {}

    private:
        double                              _delta;

        void execute_impl(InputType const &input, CallbackFunction const &func) override {
            func(input + _delta);
        }

        void flush_impl(CallbackFunction const &) override {
        }
    };

    using TransformerType                   = Transformer;

    // ----------------------------------------------------------------------
    // |  Public Methods
    SimpleEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType("SimpleEstimator", std::move(pAllColumnAnnotations)) {
    }

    ~SimpleEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleEstimator);

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    std::int64_t                            _total = 0;
    std::uint32_t                           _count = 0;

    double                                  _result;

    // ----------------------------------------------------------------------
    // |  Private Methods
    bool begin_training_impl(void) override {
        return true;
    }

    NS::FitResult fit_impl(InputType const *pBuffer, size_t cBuffer) override {
        InputType const * const             pEndBuffer(pBuffer + cBuffer);

        while(pBuffer != pEndBuffer) {
            _total += *pBuffer++;
            ++_count;
        }

        return NS::FitResult::Continue;
    }

    void complete_training_impl(void) override {
        assert(_count);
        _result = static_cast<double>(_total) / _count;
    }

    TransformerUniquePtr create_transformer_impl(void) override {
        return std::make_unique<Transformer>(_result);
    }
};

TEST_CASE("Transformer with Training") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        MyAnnotationEstimator<int, 0>,
        SimpleEstimator,
        MyAnnotationEstimator<double, 0>
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            Estimator("Estimator", pAllColumnAnnotations),
            {{1, 2, 3, 4}, {5, 6, 7, 8}},
            {10, 20, 30, 40, 50}
        ) == std::vector<double>{14.5, 24.5, 34.5, 44.5, 54.5}
    );

    NS::AnnotationMap const &               annotations((*pAllColumnAnnotations)[0]);

    REQUIRE(annotations.size() == 1);

    NS::AnnotationMap::const_iterator const             iter(annotations.find("MyAnnotationEstimator"));

    REQUIRE(iter != annotations.end());

    // There are 2 annotation instances. The first is configured to look at all the
    // training data while the second is only looking at the first 3 times. They
    // will get different results because of this.
    REQUIRE(iter->second.size() == 2);

    NS::Annotation const &                  annotation1(*iter->second[0]);
    NS::Annotation const &                  annotation2(*iter->second[1]);

    REQUIRE(dynamic_cast<MyAnnotation<int> const *>(&annotation1));
    REQUIRE(dynamic_cast<MyAnnotation<double> const *>(&annotation2));

    MyAnnotation<int> const &               mine1(static_cast<MyAnnotation<int> const &>(annotation1));
    MyAnnotation<double> const &            mine2(static_cast<MyAnnotation<double> const &>(annotation2));

    CHECK(mine1.Value == 8);

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    // The last training value + the calculated delta.
    // Note that this value is calculated at training time and
    // has nothing to do with the data send during inferencing.
    CHECK(mine2.Value == 8 + 4.5);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

// ----------------------------------------------------------------------
// |
// |  Custom Constructor Tests
// |
// ----------------------------------------------------------------------
class CustomComponentTransformer : public NS::Featurizers::Components::InferenceOnlyTransformerImpl<int, int> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::Featurizers::Components::InferenceOnlyTransformerImpl<int, int>;

    // ----------------------------------------------------------------------
    // |  Public Data
    bool const                              OperateOnOdd;
    int const                               Delta;

    // ----------------------------------------------------------------------
    // |  Public Methods
    CustomComponentTransformer(bool operateOnOdd, int delta) :
        OperateOnOdd(std::move(operateOnOdd)),
        Delta(std::move(delta)),
        _executeCtr(0) {
    }

    CustomComponentTransformer(NS::Archive &archive) :
        BaseType(archive),
        OperateOnOdd(NS::Traits<bool>::deserialize(archive)),
        Delta(NS::Traits<int>::deserialize(archive)),
        _executeCtr(NS::Traits<std::uint32_t>::deserialize(archive)) {
    }

    ~CustomComponentTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CustomComponentTransformer);

    void save(NS::Archive &ar) const override {
        BaseType::save(ar);

        NS::Traits<bool>::serialize(ar, OperateOnOdd);
        NS::Traits<int>::serialize(ar, Delta);
        NS::Traits<std::uint32_t>::serialize(ar, _executeCtr);
    }

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    std::uint32_t                           _executeCtr;

    // ----------------------------------------------------------------------
    // |  Private Methods
    void execute_impl(typename BaseType::InputType const &input, CallbackFunction const &func) override {
        bool const                          isOdd(_executeCtr++ & 1);

        if((OperateOnOdd && isOdd) == false && (OperateOnOdd == false && isOdd == false) == false)
            func(input);
        else
            func(input + Delta);
    }
};

class CustomComponentEstimator :
    public NS::TransformerEstimator<
        typename CustomComponentTransformer::InputType,
        typename CustomComponentTransformer::TransformedType
    > {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType = NS::TransformerEstimator<
        typename CustomComponentTransformer::InputType,
        typename CustomComponentTransformer::TransformedType
    >;

    using TransformerType                   = CustomComponentTransformer;

    // ----------------------------------------------------------------------
    // |  Public Data
    bool const                              OperateOnOdd;
    int const                               Delta;

    // ----------------------------------------------------------------------
    // |  Public Methods
    CustomComponentEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations, bool operateOnOdd, int delta) :
        BaseType("CustomComponentEstimator", std::move(pAllColumnAnnotations)),
        OperateOnOdd(operateOnOdd),
        Delta(delta) {
    }

    ~CustomComponentEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CustomComponentEstimator);

private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    bool begin_training_impl(void) override {
        return false;
    }

    NS::FitResult fit_impl(InputType const *, size_t) override {
        throw std::runtime_error("This should never be called as this class will not be used during training");
    }

    void complete_training_impl(void) override {
    }

    inline typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return std::make_unique<CustomComponentTransformer>(OperateOnOdd, Delta);
    }
};

class CustomEstimator :
    public NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        CustomComponentEstimator,
        CustomComponentEstimator
    > {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        CustomComponentEstimator,
        CustomComponentEstimator
    >;

    // ----------------------------------------------------------------------
    // |  Public Methods
    CustomEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations, int oddDelta, int evenDelta) :
        BaseType(
            "CustomEstimator",
            pAllColumnAnnotations,
            [&pAllColumnAnnotations, &oddDelta](void) { return CustomComponentEstimator(pAllColumnAnnotations, true, oddDelta); },
            [&pAllColumnAnnotations, &evenDelta](void) { return CustomComponentEstimator(pAllColumnAnnotations, false, evenDelta); }
        ) {

        begin_training();
        complete_training();
    }

    ~CustomEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CustomEstimator);
};

TEST_CASE("Custom Constructor") {
    CustomEstimator                                     estimator(NS::CreateTestAnnotationMapsPtr(1), 10, 200);
    CustomEstimator::TransformerUniquePtr const         pTransformer(estimator.create_transformer());
    int                                                 result;
    auto const                                          callback(
        [&result](int output) {
            result = output;
        }
    );

    pTransformer->execute(1, callback);
    CHECK(result == 201);

    pTransformer->execute(2, callback);
    CHECK(result == 12);

    pTransformer->execute(3, callback);
    CHECK(result == 203);

    pTransformer->execute(4, callback);
    CHECK(result == 14);
}
