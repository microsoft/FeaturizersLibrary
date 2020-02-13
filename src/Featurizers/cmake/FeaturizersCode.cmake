# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

# This is defined as a function to limit the visibility of _this_path so that
# it doesn't conflict with other cmake modules.
function(Impl)
    include(${_this_path}/../Components/cmake/FeaturizersComponentsCode.cmake)

    add_library(FeaturizersCode STATIC
        ${_this_path}/../../3rdParty/MurmurHash3.cpp

        ${_this_path}/../CatImputerFeaturizer.h
        ${_this_path}/../CountVectorizerFeaturizer.h
        ${_this_path}/../CountVectorizerFeaturizer.cpp
        ${_this_path}/../DateTimeFeaturizer.h
        ${_this_path}/../DateTimeFeaturizer.cpp
        ${_this_path}/../FromStringFeaturizer.h
        ${_this_path}/../HashOneHotVectorizerFeaturizer.h
        ${_this_path}/../ImputationMarkerFeaturizer.h
        ${_this_path}/../L1NormalizeFeaturizer.h
        ${_this_path}/../L2NormalizeFeaturizer.h
        ${_this_path}/../LabelEncoderFeaturizer.h
        ${_this_path}/../MaxAbsScalerFeaturizer.h
        ${_this_path}/../MaxNormalizeFeaturizer.h
        ${_this_path}/../MeanImputerFeaturizer.h
        ${_this_path}/../MedianImputerFeaturizer.h
        ${_this_path}/../MinMaxImputerFeaturizer.h
        ${_this_path}/../MinMaxScalerFeaturizer.h
        ${_this_path}/../MissingDummiesFeaturizer.h
        ${_this_path}/../ModeImputerFeaturizer.h
        ${_this_path}/../NumericalizeFeaturizer.h
        ${_this_path}/../OneHotEncoderFeaturizer.h
        ${_this_path}/../PCAFeaturizer.h
        ${_this_path}/../RobustScalerFeaturizer.h
        ${_this_path}/../SampleAddFeaturizer.h
        ${_this_path}/../SampleAddFeaturizer.cpp
        ${_this_path}/../SampleSequenceSumFeaturizer.h
        ${_this_path}/../StandardScaleWrapperFeaturizer.h
        ${_this_path}/../StringFeaturizer.h
        ${_this_path}/../Structs.h
        ${_this_path}/../TestHelpers.h
        ${_this_path}/../TfidfVectorizerFeaturizer.h
        ${_this_path}/../TfidfVectorizerFeaturizer.cpp
        ${_this_path}/../TimeSeriesImputerFeaturizer.h

        ${_this_path}/../Base/NormalizeFeaturizer.h
    )

    target_link_libraries(FeaturizersCode PRIVATE
        FeaturizersComponentsCode
    )

    file(GLOB JSON_DATA "${_this_path}/../DateTimeFeaturizerData/GeneratedCode/*.json")

    foreach(df ${JSON_DATA})
        file(COPY ${df} DESTINATION Data/DateTimeFeaturizer)
    endforeach()
endfunction()

Impl()
