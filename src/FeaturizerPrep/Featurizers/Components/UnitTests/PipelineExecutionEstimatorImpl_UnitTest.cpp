// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../PipelineExecutionEstimatorImpl.h"
#include "../InferenceOnlyFeaturizerImpl.h"

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

namespace {

template <typename T, typename ArgT>
void make_vector(std::vector<T> & v, ArgT && arg) {
    v.emplace_back(std::forward<ArgT>(arg));
}

template <typename T, typename ArgT, typename... ArgsT>
void make_vector(std::vector<T> &v, ArgT && arg, ArgsT &&...args) {
    make_vector(v, std::forward<ArgT>(arg));
    make_vector(v, std::forward<ArgsT>(args)...);
}

} // anonymous namespace

template <typename T, typename... ArgsT>
std::vector<T> make_vector(ArgsT &&... args) {
    std::vector<T>                          result;

    result.reserve(sizeof...(ArgsT));

    make_vector(result, std::forward<ArgsT>(args)...);
    return result;
}

template <typename T>
std::vector<T> make_vector(void) {
    return std::vector<T>();
}

template <typename T>
class MyAnnotation : public NS::Annotation {
public:
    T const                                 Value;

    MyAnnotation(T value) :
        NS::Annotation(this),
        Value(std::move(value)) {
    }

    ~MyAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyAnnotation);
};

template <typename T, size_t ColIndexV, size_t MaxRowsV=100000>
class MyAnnotationEstimator : public NS::AnnotationEstimator<T const &> {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    MyAnnotationEstimator(NS::AnnotationMapsPtr pAllColumnAnnotations) :
        NS::AnnotationEstimator<T const &>("MyAnnotationEstimator", std::move(pAllColumnAnnotations)),
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

    using BaseType                          = NS::AnnotationEstimator<T const &>;
    using CountMap                          = std::map<typename InternalValueTraits<T>::Type, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |  Private Data
    size_t                                  _remaining;
    CountMap                                _map;

    // ----------------------------------------------------------------------
    // |  Private Methods
    NS::Estimator::FitResult fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) override {
        typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer);

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
                return NS::Estimator::FitResult::Complete;
        }

        return NS::Estimator::FitResult::Continue;
    }

    NS::Estimator::FitResult complete_training_impl(void) override {
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

        return NS::Estimator::FitResult::Complete;
    }
};

class StringToIntTransformer : public NS::Featurizers::Components::InferenceOnlyTransformerImpl<NonCopyable<std::string> const &, NonCopyable<size_t>> {
public:
    TransformedType execute(InputType input) override {
        return input.Value.size();
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

class IntToStringTransformer : public NS::Featurizers::Components::InferenceOnlyTransformerImpl<NonCopyable<size_t> const &, NonCopyable<std::string>> {
public:
    TransformedType execute(InputType input) override {
        return std::to_string(input.Value);
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

template <typename PipelineT>
std::vector<typename PipelineT::TransformedType> Test(
    PipelineT pipeline,
    std::vector<std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>>> const &inputBatches,
    std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>> const &data
) {
    using FitResult                         = typename NS::Estimator::FitResult;
    using Batches                           = std::vector<std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>>>;

    if(inputBatches.empty() == false) {
        // Train the pipeline
        typename Batches::const_iterator        iter(inputBatches.begin());

        while(true) {
            FitResult const                     result(pipeline.fit(iter->data(), iter->size()));

            if(result == FitResult::Complete)
                break;
            else if(result == FitResult::ResetAndContinue)
                iter = inputBatches.begin();
            else if(result == FitResult::Continue) {
                ++iter;

                if(iter == inputBatches.end()) {
                    if(pipeline.complete_training() == FitResult::Complete)
                        break;

                    iter = inputBatches.begin();
                }
            }
        }
    }

    assert(pipeline.is_training_complete());

    typename PipelineT::TransformerUniquePtr            pTransformer(pipeline.create_transformer());
    std::vector<typename PipelineT::TransformedType>    output;

    output.reserve(data.size());

    for(auto const &item : data)
        output.emplace_back(pTransformer->execute(item));

    return output;
}

TEST_CASE("Single Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        StringToIntEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        Test(
            Estimator("Estimator", pAllColumnAnnotations),
            make_vector<std::vector<NonCopyable<std::string>>>(),
            make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == make_vector<NonCopyable<size_t>>(3, 3, 5)
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
        Test(
            Estimator("Estimator", pAllColumnAnnotations),
            make_vector<std::vector<NonCopyable<std::string>>>(
                make_vector<NonCopyable<std::string>>("one", "two", "two", "one", "one")
            ),
            make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == make_vector<NonCopyable<size_t>>(3, 3, 5)
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

TEST_CASE("Annotation, Annotation, Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        MyAnnotationEstimator<NonCopyable<std::string>, 0>,
        MyAnnotationEstimator<NonCopyable<std::string>, 0, 3>,
        StringToIntEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        Test(
            Estimator("Estimator", pAllColumnAnnotations),
            make_vector<std::vector<NonCopyable<std::string>>>(
                make_vector<NonCopyable<std::string>>("one", "two", "two", "one", "one")
            ),
            make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == make_vector<NonCopyable<size_t>>(3, 3, 5)
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

    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation1));
    REQUIRE(dynamic_cast<MyAnnotation<NonCopyable<std::string>> const *>(&annotation2));

    MyAnnotation<NonCopyable<std::string>> const &      mine1(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation1));
    MyAnnotation<NonCopyable<std::string>> const &      mine2(static_cast<MyAnnotation<NonCopyable<std::string>> const &>(annotation2));

    CHECK(mine1.Value.Value == "one");
    CHECK(mine2.Value.Value == "two");
}

TEST_CASE("Transformer, Transformer") {
    using Estimator = NS::Featurizers::Components::PipelineExecutionEstimatorImpl<
        StringToIntEstimator,
        IntToStringEstimator
    >;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        Test(
            Estimator("Estimator", pAllColumnAnnotations),
            make_vector<std::vector<NonCopyable<std::string>>>(),
            make_vector<NonCopyable<std::string>>("one", "two", "three")
        ) == make_vector<NonCopyable<std::string>>("3", "3", "5")
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
        Test(
            Estimator("Estimator", pAllColumnAnnotations),
            make_vector<std::vector<NonCopyable<size_t>>>(
                make_vector<NonCopyable<size_t>>(1000, 200, 30, 4),
                make_vector<NonCopyable<size_t>>(1111, 222, 33, 4)
            ),
            make_vector<NonCopyable<size_t>>(1000, 200, 30, 4)
             // The output will be the lengths of each number string
        ) == make_vector<NonCopyable<size_t>>(4, 3, 2, 1)
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
        Test(
            Estimator("Estimator", pAllColumnAnnotations),
            make_vector<std::vector<NonCopyable<size_t>>>(
                make_vector<NonCopyable<size_t>>(1000, 200, 30, 4),
                make_vector<NonCopyable<size_t>>(1111, 222, 33, 4)
            ),
            make_vector<NonCopyable<size_t>>(1000, 200, 30, 4)
        ) == make_vector<NonCopyable<std::string>>("1000", "200", "30", "4")
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
        Test(
            Estimator("Estimator", pAllColumnAnnotations),
            make_vector<std::vector<NonCopyable<size_t>>>(
                make_vector<NonCopyable<size_t>>(1000, 200, 30, 4),
                make_vector<NonCopyable<size_t>>(111, 222, 33, 4)
            ),
            make_vector<NonCopyable<size_t>>(1000, 200, 30, 4)
        ) == make_vector<NonCopyable<std::string>>("1000", "200", "30", "4")
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

class SimpleEstimator : public NS::TransformerEstimator<int const &, double> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = NS::TransformerEstimator<int const &, double>;

    class Transformer : public BaseType::Transformer {
    public:
        Transformer(double delta) : _delta(delta) {}
        Transformer(Archive &) {}

        TransformedType execute(InputType input) override {
            return input + _delta;
        }

        void save(Archive &) const override {}

    private:
        double                              _delta;
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
    NS::Estimator::FitResult fit_impl(FitBufferInputType *pBuffer, size_t cBuffer) override {
        FitBufferInputType const * const    pEndBuffer(pBuffer + cBuffer);

        while(pBuffer != pEndBuffer) {
            _total += *pBuffer++;
            ++_count;
        }

        return NS::Estimator::FitResult::Continue;
    }
    NS::Estimator::FitResult complete_training_impl(void) override {
        assert(_count);
        _result = static_cast<double>(_total) / _count;

        return NS::Estimator::FitResult::Complete;
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
        Test(
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