#include "../../Featurizers/DateTimeFeaturizer.h"

#if defined(_MSC_VER)
#   define FEATURIZER_MLNET_LIBRARY_API __declspec(dllexport)
#elif defined(__GNUC__)
#   define FEATURIZER_MLNET_LIBRARY_API __attribute__((visibility("default")))
#else
#   error unsupported!
#endif

extern "C" {
    FEATURIZER_MLNET_LIBRARY_API inline Microsoft::Featurizer::DateTimeTransformer* CreateDateTimeTransformer(void) {
        // This method is called across DLL boundaries by C#. As such, we cannot use any smart pointers and have to return a raw pointer.
        Microsoft::Featurizer::DateTimeTransformer* transformer = new Microsoft::Featurizer::DateTimeTransformer();
        return transformer;
    }

    FEATURIZER_MLNET_LIBRARY_API inline bool DeleteDateTimeTransformer(Microsoft::Featurizer::DateTimeTransformer* transformer) {
        // C# cannot clean up memory allocated in C++ so this method will be called by C# when its done with the transformer
        delete transformer;
        return true;
    }

    FEATURIZER_MLNET_LIBRARY_API inline bool CreateDateTimeTransformProxy(std::int64_t ticks, Microsoft::Featurizer::DateTimeTransformer* transformer, Microsoft::Featurizer::TimePoint** timePoint) {
        // This method is called across DLL boundaries by C#. As such, we cannot use any smart pointers and have to return a raw pointer.
        
        // Ratio to convert C# ML.NET DateTime ticks for use with std::chrono::system_clock::time_point
        using tick = std::chrono::duration<std::int64_t, std::ratio_multiply<std::ratio<100>, std::nano>>;

        *timePoint = new Microsoft::Featurizer::TimePoint(transformer->execute(std::chrono::system_clock::time_point{ tick{ticks} }));
        return true;
    }

    FEATURIZER_MLNET_LIBRARY_API inline bool DeleteDateTimeTransformProxy(Microsoft::Featurizer::TimePoint* timePoint) {
        // C# cannot clean up memory allocated in C++ so this method will be called by C# when its done with the transformer
        delete timePoint;
        return true;
    }
}
