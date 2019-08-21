// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Featurizer.h"

// ----------------------------------------------------------------------
using Microsoft::Featurizer::AnnotationPtr;
using Microsoft::Featurizer::AnnotationMaps;
using Microsoft::Featurizer::AnnotationMapsPtr;
using Microsoft::Featurizer::CreateTestAnnotationMapsPtr;
// ----------------------------------------------------------------------

class MyAnnotation : public Microsoft::Featurizer::Annotation {
public:
    // ----------------------------------------------------------------------
    // |  Public Data
    int const                               State;

    // ----------------------------------------------------------------------
    // |  Public Methods
    MyAnnotation(EstimatorUniqueId id, int state, bool valid_construction=true) :
        Microsoft::Featurizer::Annotation(valid_construction ? id : nullptr),
        State(std::move(state)) {
    }

    ~MyAnnotation(void) override = default;

    MyAnnotation(MyAnnotation const &) = delete;
    MyAnnotation & operator =(MyAnnotation const &) = delete;

    MyAnnotation(MyAnnotation &&) = default;
    MyAnnotation & operator =(MyAnnotation &&) = delete;
};

TEST_CASE("Annotation") {
    Microsoft::Featurizer::Annotation::EstimatorUniqueId const              id(reinterpret_cast<void *>(10));
    MyAnnotation const                                                      annotation(id, 10);

    CHECK(annotation.CreatorId == id);
    CHECK(annotation.State == 10);
    CHECK_THROWS_WITH(MyAnnotation(id, 10, false), Catch::Matches("Invalid id"));
}

class MyEstimator : public Microsoft::Featurizer::Estimator {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    MyEstimator(std::string name, AnnotationMapsPtr pAllColumnAnnotations) :
        Microsoft::Featurizer::Estimator(std::move(name), std::move(pAllColumnAnnotations)) {
    }

    ~MyEstimator(void) override = default;

    MyEstimator(MyEstimator const &) = delete;
    MyEstimator & operator =(MyEstimator const &) = delete;

    MyEstimator(MyEstimator &&) = default;
    MyEstimator & operator =(MyEstimator &&) = delete;

    void add_annotation(size_t col_index, int state, bool invalid_add=false) const {
        Microsoft::Featurizer::Estimator::add_annotation(invalid_add ? AnnotationPtr() : std::make_shared<MyAnnotation>(this, state), col_index);
    }

    MyAnnotation * get_annotation(size_t col_index) const {
        return get_annotation_impl<MyAnnotation>(col_index);
    }
};

TEST_CASE("Estimator - Invalid construction") {
    CHECK_THROWS_WITH(MyEstimator(std::string(), CreateTestAnnotationMapsPtr(1)), "Invalid name");
    CHECK_THROWS_WITH(MyEstimator("Name", AnnotationMapsPtr()), "Empty annotations");
    CHECK_THROWS_WITH(MyEstimator("Name", CreateTestAnnotationMapsPtr(0)), "Empty annotations");

}

TEST_CASE("Estimator") {
    AnnotationMapsPtr const                 pAllAnnotations(CreateTestAnnotationMapsPtr(2));
    MyEstimator const                       estimator("MyNewEstimator", pAllAnnotations);

    CHECK(estimator.Name == "MyNewEstimator");
    CHECK(&estimator.get_column_annotations() == pAllAnnotations.get());

    CHECK(!estimator.get_annotation(0));
    CHECK(!estimator.get_annotation(1));

    estimator.add_annotation(1, 100);

    CHECK(!estimator.get_annotation(0));
    CHECK(estimator.get_annotation(1)->State == 100);

    // Annotation-related errors
    CHECK_THROWS_WITH(estimator.add_annotation(0, 200, true), "Invalid annotation");
    CHECK_THROWS_WITH(estimator.add_annotation(99999, 200), "Invalid annotation index");

    CHECK_THROWS_WITH(estimator.get_annotation(99999), "Invalid annotation index");
}

class MyFitEstimator : public Microsoft::Featurizer::FitEstimatorImpl<int> {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    MyFitEstimator(bool return_complete_from_fit, bool is_training_complete=false) :
        Microsoft::Featurizer::FitEstimatorImpl<int>("Name", CreateTestAnnotationMapsPtr(2), is_training_complete),
        _return_complete_from_fit(return_complete_from_fit) {
    }

    ~MyFitEstimator(void) override = default;

    MyFitEstimator(MyFitEstimator const &) = delete;
    MyFitEstimator & operator =(MyFitEstimator const &) = delete;

    MyFitEstimator(MyFitEstimator &&) = default;
    MyFitEstimator & operator =(MyFitEstimator &&) = delete;

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    bool const                              _return_complete_from_fit;

    // ----------------------------------------------------------------------
    // |  Private Methods
    FitResult fit_impl(InputType const *, size_t, nonstd::optional<std::uint64_t> const &) override {
        return _return_complete_from_fit ? FitResult::Complete : FitResult::Continue;
    }

    FitResult complete_training_impl(void) override {
        return FitResult::Complete;
    }
};

TEST_CASE("FitEstimatorImpl") {
    CHECK(MyFitEstimator(true).is_training_complete() == false);
    CHECK(MyFitEstimator(true, true).is_training_complete());

    MyFitEstimator                          completed(false, true);

    CHECK(completed.is_training_complete());
    CHECK_THROWS_WITH(completed.fit(reinterpret_cast<int *>(&completed), 1), Catch::Contains("should not be invoked on an estimator that is already complete"));

    // Note that in all these cases, the actual value set to fit doesn't matter because the object doesn't
    // do anything with the data.
    MyFitEstimator                          manual_complete(false);

    // Invalid invocation
    CHECK_THROWS_WITH(manual_complete.fit(reinterpret_cast<int *>(&manual_complete), 0), "Invalid buffer");
    CHECK_THROWS_WITH(manual_complete.fit(nullptr, 10), "Invalid buffer");
    CHECK_THROWS_WITH(manual_complete.fit(nullptr, 0), "Invalid invocation");
    CHECK_THROWS_WITH(manual_complete.fit(reinterpret_cast<int *>(&manual_complete), 1, static_cast<std::uint64_t>(0)), "Invalid number of nulls");

    CHECK(manual_complete.fit(reinterpret_cast<int *>(&manual_complete), 1) == MyFitEstimator::FitResult::Continue);
    CHECK(manual_complete.fit(nullptr, 0, static_cast<std::uint64_t>(1)) == MyFitEstimator::FitResult::Continue);

    CHECK(manual_complete.is_training_complete() == false);
    manual_complete.complete_training();
    CHECK(manual_complete.is_training_complete());
    CHECK_THROWS_WITH(manual_complete.fit(reinterpret_cast<int *>(&manual_complete), 1), Catch::Contains("should not be invoked on an estimator that is already complete"));
    CHECK_THROWS_WITH(manual_complete.complete_training(), Catch::Contains("should not be invoked on an estimator that is already complete"));

    MyFitEstimator                          auto_complete(true);

    CHECK(auto_complete.is_training_complete() == false);
    CHECK(auto_complete.fit(reinterpret_cast<int *>(&auto_complete), 1) == MyFitEstimator::FitResult::Complete);
    CHECK(auto_complete.is_training_complete());
    CHECK_THROWS_WITH(auto_complete.fit(reinterpret_cast<int *>(&manual_complete), 1), Catch::Contains("should not be invoked on an estimator that is already complete"));
    CHECK_THROWS_WITH(auto_complete.complete_training(), Catch::Contains("should not be invoked on an estimator that is already complete"));
}

class MyTransformerEstimator : public Microsoft::Featurizer::TransformerEstimator<int, bool> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    struct  MyTransformer : public Transformer {
        MyTransformer(void) = default;
        ~MyTransformer(void) override = default;

        MyTransformer(MyTransformer const &) = delete;
        MyTransformer & operator =(MyTransformer const &) = delete;

        MyTransformer(MyTransformer &&) = default;
        MyTransformer & operator =(MyTransformer &&) = delete;

        bool execute(int value) override {
            return value & 1;
        }

        void save(Microsoft::Featurizer::Archive &) const override {
            // Nothing to do here
        }
    };

    // ----------------------------------------------------------------------
    // |  Public Methods
    MyTransformerEstimator(bool return_invalid_transformer, bool is_training_completed=true) :
        Microsoft::Featurizer::TransformerEstimator<int, bool>("Name", CreateTestAnnotationMapsPtr(2), is_training_completed),
        _return_invalid_transformer(return_invalid_transformer) {
    }

    ~MyTransformerEstimator(void) override = default;

    MyTransformerEstimator(MyTransformerEstimator const &) = delete;
    MyTransformerEstimator & operator =(MyTransformerEstimator const &) = delete;

    MyTransformerEstimator(MyTransformerEstimator &&) = default;
    MyTransformerEstimator & operator =(MyTransformerEstimator &&) = delete;

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    bool const                              _return_invalid_transformer;

    // ----------------------------------------------------------------------
    // |  Private Methods
    FitResult fit_impl(InputType const *, size_t, nonstd::optional<std::uint64_t> const &) override {
        throw std::runtime_error("This should never be called");
    }

    FitResult complete_training_impl(void) override {
        throw std::runtime_error("This should never be called");
    }

    TransformerPtr create_transformer_impl(void) override {
        return _return_invalid_transformer ? TransformerPtr() : std::make_shared<MyTransformer>();
    }
};

TEST_CASE("TransformerEstimator") {
    CHECK_THROWS_WITH(MyTransformerEstimator(false, false).create_transformer(), Catch::Contains("should not be invoked on an estimator that is not yet complete"));

    MyTransformerEstimator                  estimator(false);

    CHECK(estimator.is_training_complete());
    CHECK(estimator.create_transformer());
    CHECK_THROWS_WITH(estimator.create_transformer(), Catch::Contains("should not be invoked on an estimator that has been used to create a"));

    CHECK_THROWS_WITH(MyTransformerEstimator(true).create_transformer(), "Invalid result");
}
