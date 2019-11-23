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

namespace NS = Microsoft::Featurizer;
// ----------------------------------------------------------------------

class MyAnnotation : public Microsoft::Featurizer::Annotation {
public:
    // ----------------------------------------------------------------------
    // |  Public Data
    int const                               State;

    // ----------------------------------------------------------------------
    // |  Public Methods
    MyAnnotation(int state) :
        State(std::move(state)) {
    }

    ~MyAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyAnnotation);
};

TEST_CASE("Annotation") {
    MyAnnotation const                                                      annotation(10);

    CHECK(annotation.State == 10);
}

class MyEstimator : public Microsoft::Featurizer::Estimator {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    MyEstimator(char const *name, AnnotationMapsPtr pAllColumnAnnotations) :
        Microsoft::Featurizer::Estimator(name, std::move(pAllColumnAnnotations)) {
    }

    ~MyEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyEstimator);

    void add_annotation(size_t colIndex, int state, bool invalidAdd=false) const {
        Microsoft::Featurizer::Estimator::add_annotation(invalidAdd ? AnnotationPtr() : std::make_shared<MyAnnotation>(state), colIndex);
    }

    MyAnnotation * get_annotation(size_t colIndex) const {
        return get_annotation_impl<MyAnnotation>(get_column_annotations(), colIndex, Name);
    }
};

TEST_CASE("Estimator - Invalid construction") {
    CHECK_THROWS_WITH(MyEstimator(nullptr, CreateTestAnnotationMapsPtr(1)), "name");
    CHECK_THROWS_WITH(MyEstimator("", CreateTestAnnotationMapsPtr(1)), "name");
    CHECK_THROWS_WITH(MyEstimator("Name", AnnotationMapsPtr()), "pAllColumnAnnotations");
    CHECK_THROWS_WITH(MyEstimator("Name", CreateTestAnnotationMapsPtr(0)), "pAllColumnAnnotations");

}

TEST_CASE("Estimator") {
    AnnotationMapsPtr const                 pAllAnnotations(CreateTestAnnotationMapsPtr(2));
    MyEstimator const                       estimator("MyNewEstimator", pAllAnnotations);

    CHECK(strcmp(estimator.Name, "MyNewEstimator") == 0);
    CHECK(&estimator.get_column_annotations() == pAllAnnotations.get());

    CHECK(!estimator.get_annotation(0));
    CHECK(!estimator.get_annotation(1));

    estimator.add_annotation(1, 100);

    CHECK(!estimator.get_annotation(0));
    CHECK(estimator.get_annotation(1)->State == 100);

    // Annotation-related errors
    CHECK_THROWS_WITH(estimator.add_annotation(0, 200, true), "pAnnotation");
    CHECK_THROWS_WITH(estimator.add_annotation(99999, 200), "colIndex");

    CHECK_THROWS_WITH(estimator.get_annotation(99999), "colIndex");
}

class MyFitEstimator : public Microsoft::Featurizer::FitEstimator<int> {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    MyFitEstimator(bool complete_on_begin, bool complete_on_fit, bool prevent_finished) :
        Microsoft::Featurizer::FitEstimator<int>("Name", CreateTestAnnotationMapsPtr(2)),
        _complete_on_begin(complete_on_begin),
        _complete_on_fit(complete_on_fit),
        _prevent_finished(prevent_finished) {
    }

    ~MyFitEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyFitEstimator);

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    bool const                              _complete_on_begin;
    bool const                              _complete_on_fit;
    bool const                              _prevent_finished;

    // ----------------------------------------------------------------------
    // |  Private Methods
    bool begin_training_impl(void) override {
        return _complete_on_begin == false;
    }

    NS::FitResult fit_impl(InputType const *, size_t) override {
        return _complete_on_fit ? NS::FitResult::Complete : NS::FitResult::Continue;
    }

    bool on_data_completed_impl(void) override {
        return _prevent_finished == false;
    }

    void complete_training_impl(void) override {
    }
};

TEST_CASE("FitEstimator - Standard") {
    MyFitEstimator                          estimator(false, false, false);

    CHECK(estimator.get_state() == NS::TrainingState::Pending);
    CHECK_THROWS_WITH(estimator.fit(1), Catch::Contains("should not be invoked on an estimator that is not training or is already finished/complete"));
    CHECK_THROWS_WITH(estimator.on_data_completed(), Catch::Contains("should not be invoked on an estimator that is not training or is already complete"));
    CHECK_THROWS_WITH(estimator.complete_training(), Catch::Contains("should not be invoked on an estimator that is not training or is already complete"));

    estimator.begin_training();

    CHECK(estimator.get_state() == NS::TrainingState::Training);
    CHECK_THROWS_WITH(estimator.begin_training(), Catch::Contains("should not be invoked on an estimator that is already training or completed"));

    estimator.fit(1);
    CHECK(estimator.get_state() == NS::TrainingState::Training);

    estimator.fit(2);
    CHECK(estimator.get_state() == NS::TrainingState::Training);

    estimator.on_data_completed();
    CHECK(estimator.get_state() == NS::TrainingState::Finished);

    estimator.complete_training();

    CHECK(estimator.get_state() == NS::TrainingState::Completed);
    CHECK_THROWS_WITH(estimator.begin_training(), Catch::Contains("should not be invoked on an estimator that is already training or completed"));
    CHECK_THROWS_WITH(estimator.fit(3), Catch::Contains("should not be invoked on an estimator that is not training or is already finished/complete"));
    CHECK_THROWS_WITH(estimator.on_data_completed(), Catch::Contains("should not be invoked on an estimator that is not training or is already complete"));
    CHECK_THROWS_WITH(estimator.complete_training(), Catch::Contains("should not be invoked on an estimator that is not training or is already complete"));
}

TEST_CASE("FitEstimator - Finished on Begin") {
    MyFitEstimator                          estimator(true, false, false);

    CHECK(estimator.get_state() == NS::TrainingState::Pending);

    estimator.begin_training();
    CHECK(estimator.get_state() == NS::TrainingState::Finished);
    CHECK_THROWS_WITH(estimator.fit(1), Catch::Contains("should not be invoked on an estimator that is not training or is already finished/complete"));

    estimator.on_data_completed();
    CHECK(estimator.get_state() == NS::TrainingState::Finished);

    estimator.complete_training();
    CHECK(estimator.get_state() == NS::TrainingState::Completed);
}

TEST_CASE("FitEstimator - Finished on Fit") {
    MyFitEstimator                          estimator(false, true, false);

    CHECK(estimator.get_state() == NS::TrainingState::Pending);

    estimator.begin_training();
    CHECK(estimator.get_state() == NS::TrainingState::Training);

    estimator.fit(1);
    CHECK(estimator.get_state() == NS::TrainingState::Finished);
    CHECK_THROWS_WITH(estimator.fit(2), Catch::Contains("should not be invoked on an estimator that is not training or is already finished/complete"));

    estimator.on_data_completed();
    CHECK(estimator.get_state() == NS::TrainingState::Finished);

    estimator.complete_training();
    CHECK(estimator.get_state() == NS::TrainingState::Completed);
}

TEST_CASE("FitEstimator - No Finished") {
    MyFitEstimator                          estimator(false, false, true);

    CHECK(estimator.get_state() == NS::TrainingState::Pending);

    estimator.begin_training();
    CHECK(estimator.get_state() == NS::TrainingState::Training);

    estimator.fit(1);
    CHECK(estimator.get_state() == NS::TrainingState::Training);

    estimator.on_data_completed();
    CHECK(estimator.get_state() == NS::TrainingState::Training);

    estimator.complete_training();
    CHECK(estimator.get_state() == NS::TrainingState::Completed);
}

class MyTransformerEstimator : public Microsoft::Featurizer::TransformerEstimator<int, bool> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    class  MyTransformer : public Microsoft::Featurizer::StandardTransformer<int, bool> {
    public:
        MyTransformer(void) = default;
        ~MyTransformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyTransformer);

        void save(Microsoft::Featurizer::Archive &) const override {
            // Nothing to do here
        }

    private:
        void execute_impl(int const &value, CallbackFunction const &callback) override {
            callback(value & 1);
        }
    };

    // ----------------------------------------------------------------------
    // |  Public Methods
    MyTransformerEstimator(bool auto_complete, bool return_invalid_transformer) :
        Microsoft::Featurizer::TransformerEstimator<int, bool>("Name", CreateTestAnnotationMapsPtr(2)),
        _return_invalid_transformer(return_invalid_transformer) {

            if(auto_complete) {
                begin_training();
                complete_training();
            }
    }

    ~MyTransformerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyTransformerEstimator);

private:
    // ----------------------------------------------------------------------
    // |  Private Data
    bool const                              _return_invalid_transformer;

    // ----------------------------------------------------------------------
    // |  Private Methods
    bool begin_training_impl(void) override {
        return true;
    }

    NS::FitResult fit_impl(InputType const *, size_t) override {
        throw std::runtime_error("This should never be called");
    }

    bool on_data_completed_impl(void) override {
        return true;
    }

    void complete_training_impl(void) override {
    }

    TransformerUniquePtr create_transformer_impl(void) override {
        return _return_invalid_transformer ? TransformerUniquePtr() : std::make_unique<MyTransformer>();
    }
};

TEST_CASE("TransformerEstimator") {
    CHECK_THROWS_WITH(MyTransformerEstimator(false, true).create_transformer(), Catch::Contains("should not be invoked on an estimator that is not yet complete"));

    MyTransformerEstimator                  estimator(true, false);

    CHECK(estimator.get_state() == NS::TrainingState::Completed);
    CHECK(estimator.create_transformer());
    CHECK_THROWS_WITH(estimator.create_transformer(), Catch::Contains("should not be invoked on an estimator that has been used to create a"));

    CHECK_THROWS_WITH(MyTransformerEstimator(true, true).create_transformer(), "Invalid result");
}
