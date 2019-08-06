// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#pragma once
#include <vector>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <map>
#include <array>
#include <string>

namespace Microsoft {
namespace Featurizer {
namespace Traits {

/////////////////////////////////////////////////////////////////////////
///  \namespace     Traits
///  \brief         We have a range of of types we are dealing with. Many types
///                 have different ways to represent what a `NULL` value is
///                 (float has NAN for example) as well as different ways to
///                 convert the value to a string representation. By using 
///                 templates combined with partial template specialization
///                 we can handle scenarios like these that vary based on the data type.
///                 
///                 Example: This allows us to do things like `Traits<std::int8_t>::IsNull()`
///                 and `Traits<float>::IsNull()` and let the trait itself deal with the
///                 actual implementation and allows us as developers to not worry about that.
///                 
///                 This benefit is magnified because we are also using templates for our 
///                 transformers. When we declare that a transformer has type T = std::int8_t,
///                 we can then also use `Traits<T>::IsNull()` and the compiler will know that 
///                 `T` is a `std::int8_t` and call the appropate template specialization.
///
template <typename T>
struct Traits {};

/////////////////////////////////////////////////////////////////////////
///  \namespace     Traits
///  \brief         When using partial template specilization, if the compiler
///                 cannot find a more specfic implementation of the template
///                 it will fall back to the base template and use whatever is
///                 defined there. If you have methods defined in that base template,
///                 it makes it very difficult to debug what is going on. By
///                 putting no implementation in the `Traits<>` template and
///                 having the real base struct be `TraitsImpl<>`, if you try and 
///                 specify a trait that doesn't have a specilization, the compiler
///                 can detect that and throw an error during compilation.
///
///                 Example: There is no template `Traits<char>`. If you try and use it
///                 the compiler will fall back to the `Traits<>` struct which has no methods
///                 defined. Trying to then use `Traits<char>` will cause a compile time error
///                 letting you know something isn't correct.
///
template <typename T>
struct TraitsImpl {
    using nullable_type = boost::optional<T>;
    static bool IsNull(nullable_type const& value) {
        return !value.is_initialized();
    }
};

template <>
struct Traits<bool> : public TraitsImpl<bool> {
    static std::string const & ToString(bool const& value) {
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wexit-time-destructors"
        static std::string const _TRUE_VALUE("True");
        static std::string const _FALSE_VALUE("False");
        #pragma clang diagnostic pop
        return value != 0 ? _TRUE_VALUE : _FALSE_VALUE;
    }
};

template <>
struct Traits<std::int8_t> : public TraitsImpl<std::int8_t> {
    static std::string ToString(std::int8_t const& value) {
        return std::to_string(value);
    }
};

template <>
struct Traits<std::int16_t> : public TraitsImpl<std::int16_t> {
    static std::string ToString(std::int16_t const& value) {
        return std::to_string(value);
    }
};

template <>
struct Traits<std::int32_t> : public TraitsImpl<std::int32_t> {
    static std::string ToString(std::int32_t const& value) {
        return std::to_string(value);
    }
};

template <>
struct Traits<std::int64_t> : public TraitsImpl<std::int64_t> {
    static std::string ToString(std::int64_t const& value) {
        return std::to_string(value);
    }
};

template <>
struct Traits<std::uint8_t> : public TraitsImpl<std::uint8_t> {
    static std::string ToString(std::uint8_t const& value) {
        return std::to_string(value);
    }
};

template <>
struct Traits<std::uint16_t> : public TraitsImpl<std::uint16_t> {
    static std::string ToString(std::uint16_t const& value) {
         return std::to_string(value);
    }
};

template <>
struct Traits<std::uint32_t> : public TraitsImpl<std::uint32_t> {
    static std::string ToString(std::uint32_t const& value) {
        return std::to_string(value);
    }
};

template <>
struct Traits<std::uint64_t> : public TraitsImpl<std::uint64_t> {
    static std::string ToString(std::uint64_t const& value) {
        return std::to_string(value);
    }
};

template <>
struct Traits<std::float_t> : public TraitsImpl<std::float_t> {
    using nullable_type = std::float_t;
    static bool IsNull(nullable_type const& value) {
        return isnan(value);
    }

    static std::string ToString(nullable_type const& value) {
        if (IsNull(value))
        {
            return "NaN";
        }
        std::ostringstream streamObj;
        streamObj << value;
        return streamObj.str();
    }
};

template <>
struct Traits<std::double_t> : public TraitsImpl<std::double_t> {
    using nullable_type = std::double_t;
    static bool IsNull(nullable_type const& value) {
        return isnan(value);
    }

    static std::string ToString(nullable_type const& value) {
        if (IsNull(value))
        {
            return "NaN";
        }
        std::ostringstream streamObj;
        streamObj << value;
        return streamObj.str();
    }
};

template <>
struct Traits<std::string> : public TraitsImpl<std::string> {
    static std::string const & ToString(std::string const& value) {
        return value;
    }
};

//TODO:unify vector and array
template <typename T, size_t size>
struct Traits <std::array<T, size>> : public TraitsImpl<std::array<T, size>> {
    static std::string ToString(std::array<T, size> const& value) {
        std::ostringstream streamObj;
        streamObj << "[";
        
        for (unsigned int count = 0; count < size - 1; ++count)
        {
            streamObj << Traits<T>::ToString (value[count]) << ",";
        }
        streamObj << Traits<T>::ToString (value.back()) << "]";
        return streamObj.str();
    }
};

//TODO:unify vector and array
template <typename T, typename AllocatorT>
struct Traits<std::vector<T, AllocatorT>> : public TraitsImpl<std::vector<T, AllocatorT>> {
    static std::string ToString(std::vector<T, AllocatorT> const& value) {
        std::ostringstream streamObj;
        streamObj << "[";
       
        for (unsigned int count = 0; count < value.size() - 1; ++count)
        {
            streamObj << Traits<T>::ToString(value.at(count)) << ",";
        }
        streamObj << Traits<T>::ToString(value.back()) << "]";
        return streamObj.str();
    }
};

template <typename KeyT, typename T, typename CompareT, typename AllocatorT>
struct Traits<std::map<KeyT, T, CompareT, AllocatorT>> : public TraitsImpl<std::map<KeyT, T, CompareT, AllocatorT>> {
    static std::string ToString(std::map<KeyT, T, CompareT, AllocatorT> const& value) {
        std::ostringstream streamObj;
        streamObj << "{";
       
        for (auto it = value.cbegin(); it != value.cend(); ++it)
        {
            streamObj << Traits<KeyT>::ToString(it->first) << ":" <<  Traits<T>::ToString(it->second);
            if (std::next(it) != value.cend()) 
            {
                streamObj << ",";
            }
        }
        streamObj << "}";
        return streamObj.str();
    }
};

template <typename ... Types>
struct Traits <std::function<Types...>> : public TraitsImpl<std::function<Types...>> {
    // static std::string ToString(std::function<Types ...> const& value) {
    //     // Decide what to return here
    //     throw std::logic_error("Function not yet implemented");
    // }
};

template <typename T>
struct Traits <boost::optional<T>> : public TraitsImpl<boost::optional<T>> {
    using nullable_type = boost::optional<T>;
    static std::string ToString(nullable_type const& value) {
    if (value) {
        return Traits<T>::ToString(value.get());
    }   
        return "NULL";
    }
};

//TODO:Tuple implementation
template <typename ... Types>
struct Traits <std::tuple<Types...>> : public TraitsImpl<std::tuple<Types...>> {
    //static std::string ToString(std::tuple<Types ...> const& value) {
         
    //}
};

} // namespace Traits
} // namespace Featurizer
} // namespace Microsoft
