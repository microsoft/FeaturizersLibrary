// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#pragma once

#include <array>
#include <cmath>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Shared/optional.h"

namespace Microsoft {
namespace Featurizer {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdocumentation"
#endif

/////////////////////////////////////////////////////////////////////////
///  \struct        Traits
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
///                 `T` is a `std::int8_t` and call the appropriate template specialization.
///
template <typename T>
struct Traits {
    // Each specialization should implement the following types and methods
    //
    //   // Types
    //   - nullable_type
    //
    //   // Methods
    //   - static nullable_type CreateNullValue(void);
    //   - static bool IsNull(nullable_type const &value);
    //   - static std::string ToString(T const &value);
    //   - template <typename ArchiveT> static ArchiveT & serialize(ArchiveT &ar, T const &value);
    //   - template <typename ArchiveT> static T deserialize(ArchiveT &ar);
    //
};

/////////////////////////////////////////////////////////////////////////
///  \struct        TraitsImpl
///  \brief         When using partial template specialization, if the compiler
///                 cannot find a more specific implementation of the template
///                 it will fall back to the base template and use whatever is
///                 defined there. If you have methods defined in that base template,
///                 it makes it very difficult to debug what is going on. By
///                 putting no implementation in the `Traits<>` template and
///                 having the real base struct be `TraitsImpl<>`, if you try and
///                 specify a trait that doesn't have a specialization, the compiler
///                 can detect that and throw an error during compilation.
///
///                 Example: There is no template `Traits<char>`. If you try and use it
///                 the compiler will fall back to the `Traits<>` struct which has no methods
///                 defined. Trying to then use `Traits<char>` will cause a compile time error
///                 letting you know something isn't correct.
///
template <typename T>
struct TraitsImpl {
    using nullable_type = nonstd::optional<T>;

    static nullable_type CreateNullValue(void) {
        return nullable_type();
    }

    static bool IsNull(nullable_type const& value) {
        return !value.has_value();
    }
};

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

template <>
struct Traits<bool> : public TraitsImpl<bool> {
    static std::string const & ToString(bool const& value) {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

        static std::string const _TRUE_VALUE("True");
        static std::string const _FALSE_VALUE("False");

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

        return value != 0 ? _TRUE_VALUE : _FALSE_VALUE;
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, bool const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static bool deserialize(ArchiveT &ar) {
        return ar.template deserialize<bool>();
    }
};

template <>
struct Traits<std::int8_t> : public TraitsImpl<std::int8_t> {
    static std::string ToString(std::int8_t const& value) {
        return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::int8_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::int8_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::int8_t>();
    }
};

template <>
struct Traits<std::int16_t> : public TraitsImpl<std::int16_t> {
    static std::string ToString(std::int16_t const& value) {
        return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::int16_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::int16_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::int16_t>();
    }
};

template <>
struct Traits<std::int32_t> : public TraitsImpl<std::int32_t> {
    static std::string ToString(std::int32_t const& value) {
        return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::int32_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::int32_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::int32_t>();
    }
};

template <>
struct Traits<std::int64_t> : public TraitsImpl<std::int64_t> {
    static std::string ToString(std::int64_t const& value) {
        return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::int64_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::int64_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::int64_t>();
    }
};

template <>
struct Traits<std::uint8_t> : public TraitsImpl<std::uint8_t> {
    static std::string ToString(std::uint8_t const& value) {
        return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::uint8_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::uint8_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::uint8_t>();
    }
};

template <>
struct Traits<std::uint16_t> : public TraitsImpl<std::uint16_t> {
    static std::string ToString(std::uint16_t const& value) {
         return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::uint16_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::uint16_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::uint16_t>();
    }
};

template <>
struct Traits<std::uint32_t> : public TraitsImpl<std::uint32_t> {
    static std::string ToString(std::uint32_t const& value) {
        return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::uint32_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::uint32_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::uint32_t>();
    }
};

template <>
struct Traits<std::uint64_t> : public TraitsImpl<std::uint64_t> {
    static std::string ToString(std::uint64_t const& value) {
        return std::to_string(value);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::uint64_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::uint64_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::uint64_t>();
    }
};

template <>
struct Traits<std::float_t> {
    using nullable_type = std::float_t;

    static nullable_type CreateNullValue(void) {
        // Note that std::numeric_limits doesn't seem to be specialized for std::float_t
        // on some systems - using float_t instead.
        return std::numeric_limits<float_t>::quiet_NaN();
    }

    static bool IsNull(nullable_type const& value) {
        return std::isnan(value);
    }

    static std::float_t const & GetValue(nullable_type const& value) {
        if (IsNull(value))
            throw std::runtime_error("GetValue attempt on float_t null.");

        return value;
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

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::float_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::float_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::float_t>();
    }
};

template <>
struct Traits<std::double_t>  {
    using nullable_type = std::double_t;

    static nullable_type CreateNullValue(void) {
        return std::numeric_limits<std::double_t>::quiet_NaN();
    }

    static bool IsNull(nullable_type const& value) {
        return std::isnan(value);
    }

    static std::double_t const & GetValue(nullable_type const& value) {
        if (IsNull(value))
            throw std::runtime_error("GetValue attempt on double_t null.");

        return value;
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

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::double_t const &value) {
        return ar.serialize(value);
    }

    template <typename ArchiveT>
    static std::double_t deserialize(ArchiveT &ar) {
        return ar.template deserialize<std::double_t>();
    }
};

template <>
struct Traits<std::string> : public TraitsImpl<std::string> {
    static std::string const & ToString(std::string const& value) {
        return value;
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::string const &value) {
        ar.serialize(static_cast<std::uint32_t>(value.size()));

        if(value.empty() == false)
            ar.serialize(reinterpret_cast<unsigned char const *>(value.data()), value.size());

        return ar;
    }

    template <typename ArchiveT>
    static std::string deserialize(ArchiveT &ar) {
        std::string                         result;
        std::uint32_t const                 size(ar.template deserialize<std::uint32_t>());

        if(size != 0) {
            char const * const     pBuffer(reinterpret_cast<char const *>(ar.get_buffer_ptr()));

            ar.update_buffer_ptr(size);

            std::copy(pBuffer, pBuffer + size, std::back_inserter(result));
        }

        return result;
    }
};

namespace {

template <typename T>
std::string ToStringImpl(T const *pBuffer, size_t cBuffer) {
    std::ostringstream streamObj;

    streamObj << "[";

    if(cBuffer != 0) {
        T const * const                     pNextToLastElement(pBuffer + cBuffer - 1);

        while(pBuffer != pNextToLastElement) {
            streamObj << Traits<T>::ToString(*pBuffer) << ",";
            ++pBuffer;
        }

        streamObj << Traits<T>::ToString(*pBuffer);
    }

    streamObj << "]";
    return streamObj.str();
}

} // anonymous namespace

template <typename T, size_t ArrayV>
struct Traits<std::array<T, ArrayV>> : public TraitsImpl<std::array<T, ArrayV>> {
    static std::string ToString(std::array<T, ArrayV> const& value) {
        return ToStringImpl(value.data(), value.size());
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::array<T, ArrayV> const &value) {
        for(auto const &item : value) {
            Traits<T>::serialize(ar, item);
        }

        return ar;
    }

    template <typename ArchiveT>
    static std::array<T, ArrayV> deserialize(ArchiveT &ar) {
        std::array<T, ArrayV>               result;

        for(auto &item : result) {
            item = Traits<T>::deserialize(ar);
        }

        return result;
    }
};

template <typename T, typename AllocatorT>
struct Traits<std::vector<T, AllocatorT>> : public TraitsImpl<std::vector<T, AllocatorT>> {
    static std::string ToString(std::vector<T, AllocatorT> const& value) {
        return ToStringImpl(value.data(), value.size());
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::vector<T, AllocatorT> const &value) {
        ar.serialize(static_cast<std::uint32_t>(value.size()));

        for(auto const &item: value) {
            Traits<T>::serialize(ar, item);
        }

        return ar;
    }

    template <typename ArchiveT>
    static std::vector<T, AllocatorT> deserialize(ArchiveT &ar) {
        std::vector<T, AllocatorT>          result;
        std::uint32_t                       size(ar.template deserialize<std::uint32_t>());

        if(size != 0) {
            result.reserve(size);

            while(size) {
                result.emplace_back(Traits<T>::deserialize(ar));
                --size;
            }
        }

        return result;
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

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::map<KeyT, T, CompareT, AllocatorT> const &value) {
        ar.serialize(static_cast<std::uint32_t>(value.size()));

        for(auto const &kvp : value) {
            Traits<KeyT>::serialize(ar, kvp.first);
            Traits<T>::serialize(ar, kvp.second);
        }

        return ar;
    }

    template <typename ArchiveT>
    static std::map<KeyT, T, CompareT, AllocatorT> deserialize(ArchiveT &ar) {
        using MapType                       = std::map<KeyT, T, CompareT, AllocatorT>;

        MapType                             result;
        std::uint32_t                       size(ar.template deserialize<std::uint32_t>());

        while(size) {
            result.emplace(
                [&ar](void) -> std::pair<KeyT, T> {
                    KeyT                    key(Traits<KeyT>::deserialize(ar));
                    T                       value(Traits<T>::deserialize(ar));

                    return std::make_pair(std::move(key), std::move(value));
                }()
            );

            --size;
        }

        return result;
    }
};

template <typename T>
struct Traits<nonstd::optional<T>>  {
    using nullable_type = nonstd::optional<T>;

    static nullable_type CreateNullValue(void) {
        return nullable_type();
    }

    static bool IsNull(nullable_type const& value) {
        return !value.has_value();
    }

    static std::string ToString(nullable_type const& value) {
        if (value) {
            return Traits<T>::ToString(*value);
        }
        return "NULL";
    }

    static T const & GetValue(nullable_type const& value) {
        if (value){
            return value.value();
        }
        else
            throw std::runtime_error("GetValue attempt on Optional type null.");
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, nonstd::optional<T> const &value) {
        ar.serialize(static_cast<bool>(value));

        if(value)
            Traits<T>::serialize(ar, *value);

        return ar;
    }

    template <typename ArchiveT>
    static nonstd::optional<T> deserialize(ArchiveT &ar) {
        nonstd::optional<T>                 result;

        if(ar.template deserialize<bool>())
            result = Traits<T>::deserialize(ar);

        return result;
    }
};

template <typename... Types>
struct Traits<std::tuple<Types...>> : public TraitsImpl<std::tuple<Types...>> {
    static std::string ToString(std::tuple<Types ...> const& value) {
        std::ostringstream streamObj;
        streamObj << "(";
        ToStringHelper<0>(value, streamObj);
        streamObj << ")";
        return streamObj.str();
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::tuple<Types...> const &value) {
        SerializeHelper<0>(ar, value);
        return ar;
    }

    template <typename ArchiveT>
    static std::tuple<Types...> deserialize(ArchiveT &ar) {
        std::tuple<Types...>                result;

        DeserializeHelper<0>(ar, result);
        return result;
    }

private:
    template<std::size_t N> static inline std::enable_if_t<N < sizeof...(Types) - 1> ToStringHelper(std::tuple<Types...> const& value, std::ostringstream& streamObj) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        streamObj << Traits<type>::ToString(std::get<N>(value)) << ",";
        ToStringHelper<N + 1>(value, streamObj);
    }

    template<std::size_t N> static inline std::enable_if_t<N == (sizeof...(Types) - 1)> ToStringHelper(std::tuple<Types...> const& value, std::ostringstream& streamObj) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        streamObj << Traits<type>::ToString(std::get<N>(value));
    }

    template <std::size_t N, typename ArchiveT> static inline std::enable_if_t<N < sizeof...(Types) - 1> SerializeHelper(ArchiveT &ar, std::tuple<Types...> const &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        Traits<type>::serialize(ar, std::get<N>(value));
        SerializeHelper<N + 1>(ar, value);
    }

    template <std::size_t N, typename ArchiveT> static inline std::enable_if_t<N == sizeof...(Types) - 1> SerializeHelper(ArchiveT &ar, std::tuple<Types...> const &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        Traits<type>::serialize(ar, std::get<N>(value));
    }

    template <std::size_t N, typename ArchiveT> static inline std::enable_if_t<N < sizeof...(Types) - 1> DeserializeHelper(ArchiveT &ar, std::tuple<Types...> &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        std::get<N>(value) = Traits<type>::deserialize(ar);
        DeserializeHelper<N + 1>(ar, value);
    }

    template <std::size_t N, typename ArchiveT> static inline std::enable_if_t<N == sizeof...(Types) - 1> DeserializeHelper(ArchiveT &ar, std::tuple<Types...> &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        std::get<N>(value) = Traits<type>::deserialize(ar);
    }
};

// TODO: ONNX (Sparse) Tensor
// TODO: Apache Arrow

} // namespace Featurizer
} // namespace Microsoft
