// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <array>
#include <chrono>
#include <cmath>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#if (!defined ISLITTLEENDIAN)
# define ISLITTLEENDIAN 1
#endif

static bool constexpr is_little_endian = bool(ISLITTLEENDIAN);

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wshift-sign-overflow"
#endif

#include "3rdParty/date.h"

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

#include "3rdParty/optional.h"

namespace Microsoft {
namespace Featurizer {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdocumentation"
#endif


enum class TypeId : uint32_t {
    // Enumeration values are in the following format:
    //
    //      0xVTTTXXXX
    //        ^^^^^^^^
    //        ||  |- Id
    //        ||- Number of trailing types
    //        |- Has trailing types
    //
    String = 0x00000001,
    Int8,
    Int16,
    Int32,
    Int64,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
    Float16,
    Float32,
    Float64,
    Complex64,
    Complex128,
    BFloat16,
    Bool,
    Timepoint,
    Duration,

    LastStaticValue,

    // The following values have N number of trailing types
    Tensor = 0x1001 | (LastStaticValue + 1),
    SparseTensor = 0x1001 | (LastStaticValue + 2),
    Tabular = 0x1001 | (LastStaticValue + 3),

    Nullable = 0x1001 | (LastStaticValue + 4),
    Vector = 0x1001 | (LastStaticValue + 5),
    Map = 0x1002 | (LastStaticValue + 6)
};

inline bool IsValid(TypeId id) {
    return id == TypeId::String
        || id == TypeId::Int8
        || id == TypeId::Int16
        || id == TypeId::Int32
        || id == TypeId::Int64
        || id == TypeId::UInt8
        || id == TypeId::UInt16
        || id == TypeId::UInt32
        || id == TypeId::UInt64
        || id == TypeId::Float16
        || id == TypeId::Float32
        || id == TypeId::Float64
        || id == TypeId::Complex64
        || id == TypeId::Complex128
        || id == TypeId::BFloat16
        || id == TypeId::Bool
        || id == TypeId::Timepoint
        || id == TypeId::Duration
        || id == TypeId::Tensor
        || id == TypeId::SparseTensor
        || id == TypeId::Tabular
        || id == TypeId::Nullable
        || id == TypeId::Vector
        || id == TypeId::Map;
}

/////////////////////////////////////////////////////////////////////////
///  \struct        Traits
///  \brief         We have a range of of types we are dealing with. Many types
///                 have different ways to represent what a 'NULL' value is
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
    //   // "Data"
    //   static constexpr bool const        IsNullableType;
    //   static constexpr bool const        IsNativeNullableType;
    //
    //   // Methods
    //   - static nullable_type CreateNullValue(void);
    //   - static bool IsNull(nullable_type const &value);
    //   - static T const & GetNullableValue(nullable_type const &value);
    //   - static T & GetNullableValue(nullable_type &value);
    //   - static std::string ToString(T const &value);
    //   - static T FromString(std::string const &value);
    //   - template <typename ArchiveT> static ArchiveT & serialize(ArchiveT &ar, T const &value);
    //   - template <typename ArchiveT> static T deserialize(ArchiveT &ar);
    //
};

/////////////////////////////////////////////////////////////////////////
///  \class         Traits
///  \brief         Strips references from types.
///
template <typename T> struct Traits<T &> : public Traits<T> {};

/////////////////////////////////////////////////////////////////////////
///  \class         Traits
///  \brief         Strips const from types
///
template <typename T> struct Traits<T const> : public Traits<T> {};

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
    static constexpr bool const             IsNullableType = false;
    static constexpr bool const             IsNativeNullableType = false;

    using nullable_type = nonstd::optional<T>;

    static nullable_type CreateNullValue(void) {
        return nullable_type();
    }
    static bool IsNull(T const&) {
        return false;
    }
    static bool IsNull(nullable_type const& value) {
        return !value.has_value();
    }

    static T const & GetNullableValue(nullable_type const &value) {
        if (IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a null value.");
        return *value;
    }

    static T & GetNullableValue(nullable_type &value) {
        if(IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a null value.");

        return *value;
    }
};

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

namespace {
template <typename T>
static T swap_endian(T u)
{
    unsigned char* source(reinterpret_cast<unsigned char*>(&u));
    unsigned char dest[sizeof(T)];

    for (size_t k = 0; k < sizeof(T); k++)
        dest[k] = *(source+sizeof(T) - k - 1);

    return *reinterpret_cast<T*>(dest);
}


template <typename ArchiveT, typename TypeT>
static ArchiveT & serialize_impl(ArchiveT &ar, TypeT const &value, std::true_type) {
    return ar.serialize(value);
}
template <typename ArchiveT, typename TypeT>
static ArchiveT & serialize_impl(ArchiveT &ar, TypeT const &value, std::false_type) {
    return ar.serialize(swap_endian<TypeT>(value));
}
template <typename ArchiveT, typename TypeT>
static TypeT deserialize_impl(ArchiveT &ar, std::true_type) {
    return ar.template deserialize<TypeT>();
}
template <typename ArchiveT, typename TypeT>
static TypeT deserialize_impl(ArchiveT &ar, std::false_type) {
    return swap_endian<TypeT>(ar.template deserialize<TypeT>());
}

} //anonymous namespace


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

    static bool FromString(std::string const &value) {
        return value == "True";
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

    static std::int8_t FromString(std::string const &value) {
        int                                 v(std::stoi(value.c_str()));

        if(v < std::numeric_limits<std::int8_t>::min() || v > std::numeric_limits<std::int8_t>::max())
            throw std::invalid_argument("Invalid conversion");

        return static_cast<std::int8_t>(v);
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

    static std::int16_t FromString(std::string const &value) {
        int                                 v(std::stoi(value.c_str()));

        if(v < std::numeric_limits<std::int16_t>::min() || v > std::numeric_limits<std::int16_t>::max())
            throw std::invalid_argument("Invalid conversion");

        return static_cast<std::int16_t>(v);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::int16_t const &value) {
        return serialize_impl<ArchiveT, std::int16_t>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static std::int16_t deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, std::int16_t>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::int32_t> : public TraitsImpl<std::int32_t> {
    static std::string ToString(std::int32_t const& value) {
        return std::to_string(value);
    }

    static std::int32_t FromString(std::string const &value) {
        static_assert(sizeof(std::int32_t) == sizeof(int), "This code expects that an int is 32 bits");
        return std::stoi(value.c_str());
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::int32_t const &value) {
        return serialize_impl<ArchiveT, std::int32_t>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static std::int32_t deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, std::int32_t>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::int64_t> : public TraitsImpl<std::int64_t> {
    static std::string ToString(std::int64_t const& value) {
        return std::to_string(value);
    }

    static std::int64_t FromString(std::string const &value) {
        static_assert(sizeof(std::int64_t) <= sizeof(long long), "This code expects that long long >= 64 bits");

        long long                           v(std::stoll(value.c_str()));

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wtautological-type-limit-compare"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127) // Conditional expression is constant
#endif

        if(sizeof(long long) > sizeof(std::int64_t)) {
            if(v < std::numeric_limits<std::int64_t>::min() || v > std::numeric_limits<std::int64_t>::max())
                throw std::invalid_argument("Invalid conversion");
        }

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

        return static_cast<std::int64_t>(v);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::int64_t const &value) {
        return serialize_impl<ArchiveT, std::int64_t>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static std::int64_t deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, std::int64_t>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::uint8_t> : public TraitsImpl<std::uint8_t> {
    static std::string ToString(std::uint8_t const& value) {
        return std::to_string(value);
    }

    static std::uint8_t FromString(std::string const &value) {
        unsigned long                       v(std::stoul(value.c_str()));

        if(v > std::numeric_limits<std::uint8_t>::max())
            throw std::invalid_argument("Invalid conversion");

        return static_cast<std::uint8_t>(v);
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

    static std::uint16_t FromString(std::string const &value) {
        unsigned long                       v(std::stoul(value.c_str()));

        if(v > std::numeric_limits<std::uint16_t>::max())
            throw std::invalid_argument("Invalid conversion");

        return static_cast<std::uint16_t>(v);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::uint16_t const &value) {
        return serialize_impl<ArchiveT, std::uint16_t>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static std::uint16_t deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, std::uint16_t>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::uint32_t> : public TraitsImpl<std::uint32_t> {
    static std::string ToString(std::uint32_t const& value) {
        return std::to_string(value);
    }

    static std::uint32_t FromString(std::string const &value) {
        static_assert(sizeof(std::uint32_t) <= sizeof(unsigned long), "This code assumes that a long is more 32 bits");

        unsigned long                       v(std::stoul(value.c_str()));

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wtautological-type-limit-compare"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127) // Conditional expression is constant
#endif

        if(sizeof(unsigned long) > sizeof(std::uint32_t)) {
            if(v > std::numeric_limits<std::uint32_t>::max())
                throw std::invalid_argument("Invalid conversion");
        }

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

        return static_cast<std::uint32_t>(v);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::uint32_t const &value) {
        return serialize_impl<ArchiveT, std::uint32_t>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static std::uint32_t deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, std::uint32_t>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::uint64_t> : public TraitsImpl<std::uint64_t> {
    static std::string ToString(std::uint64_t const& value) {
        return std::to_string(value);
    }

    static std::uint64_t FromString(std::string const &value) {
        static_assert(sizeof(std::uint64_t) <= sizeof(unsigned long long), "This code expects that unsigned long long >= 64 bits");

        unsigned long long                  v(std::stoull(value.c_str()));

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wtautological-type-limit-compare"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127) // Conditional expression is constant
#endif

        if(sizeof(unsigned long long) > sizeof(std::uint64_t)) {
            if(v > std::numeric_limits<std::uint64_t>::max())
                throw std::invalid_argument("Invalid conversion");
        }

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

        return static_cast<std::uint64_t>(v);
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::uint64_t const &value) {
        return serialize_impl<ArchiveT, std::uint64_t>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static std::uint64_t deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, std::uint64_t>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::float_t> {
    using nullable_type                     = std::float_t;

    static constexpr bool const             IsNullableType = true;
    static constexpr bool const             IsNativeNullableType = true;

    static nullable_type CreateNullValue(void) {
        return std::numeric_limits<std::float_t>::quiet_NaN();
    }

    static bool IsNull(nullable_type const& value) {
        return std::isnan(value);
    }

    static std::float_t const & GetNullableValue(nullable_type const& value) {
        if (IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a float_t NaN.");

        return value;
    }

    static std::float_t & GetNullableValue(nullable_type &value) {
        if(IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a float_t NaN.");

        return value;
    }

    static std::string ToString(nullable_type const& value) {
        if (IsNull(value))
        {
            return "NaN";
        }

        return std::to_string(value);
    }

    static std::float_t FromString(std::string const &value) {
        if(value == "NaN")
            return std::numeric_limits<std::float_t>::quiet_NaN();

        return std::stof(value.c_str());
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, nullable_type const &value) {
        return serialize_impl<ArchiveT, nullable_type>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static nullable_type deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, nullable_type>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::double_t>  {
    using nullable_type                     = std::double_t;

    static constexpr bool const             IsNullableType = true;
    static constexpr bool const             IsNativeNullableType = true;

    static nullable_type CreateNullValue(void) {
        return std::numeric_limits<std::double_t>::quiet_NaN();
    }

    static bool IsNull(nullable_type const& value) {
        return std::isnan(value);
    }

    static std::double_t const & GetNullableValue(nullable_type const& value) {
        if (IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a double_t NaN.");

        return value;
    }

    static std::double_t & GetNullableValue(nullable_type &value) {
        if(IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a double_t NaN.");

        return value;
    }

    static std::string ToString(nullable_type const& value) {
        if (IsNull(value))
        {
            return "NaN";
        }

        return std::to_string(value);
    }

    static std::double_t FromString(std::string const &value) {
        if(value == "NaN")
            return std::numeric_limits<std::double_t>::quiet_NaN();

        return std::stod(value.c_str());
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, nullable_type const &value) {
        return serialize_impl<ArchiveT, nullable_type>(ar, value, std::integral_constant<bool,ISLITTLEENDIAN>());
    }

    template <typename ArchiveT>
    static nullable_type deserialize(ArchiveT &ar) {
        return deserialize_impl<ArchiveT, nullable_type>(ar, std::integral_constant<bool,ISLITTLEENDIAN>());
    }
};

template <>
struct Traits<std::string> : public TraitsImpl<std::string> {
    static std::string const & ToString(std::string const& value) {
        return value;
    }

    static std::string const & FromString(std::string const &value) {
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

    static std::array<T, ArrayV> FromString(std::string const &value) {
        std::ignore = value; throw std::logic_error("Not Implemented Yet");
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

    static std::vector<T, AllocatorT> FromString(std::string const &value) {
        std::ignore = value; throw std::logic_error("Not Implemented Yet");
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

    static std::map<KeyT, T, CompareT, AllocatorT> FromString(std::string const &value) {
        std::ignore = value; throw std::logic_error("Not Implemented Yet");
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

template <typename... Types>
struct Traits<std::tuple<Types...>> : public TraitsImpl<std::tuple<Types...>> {
    static std::string ToString(std::tuple<Types ...> const& value) {
        std::ostringstream streamObj;
        streamObj << "(";
        ToStringHelper<0>(value, streamObj);
        streamObj << ")";
        return streamObj.str();
    }

    static std::tuple<Types...> FromString(std::string const &value) {
        std::ignore = value; throw std::logic_error("Not Implemented Yet");
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
    template<std::size_t N> static inline typename std::enable_if<N < sizeof...(Types) - 1>::type ToStringHelper(std::tuple<Types...> const& value, std::ostringstream& streamObj) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        streamObj << Traits<type>::ToString(std::get<N>(value)) << ",";
        ToStringHelper<N + 1>(value, streamObj);
    }

    template<std::size_t N> static inline typename std::enable_if<N == (sizeof...(Types) - 1)>::type ToStringHelper(std::tuple<Types...> const& value, std::ostringstream& streamObj) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        streamObj << Traits<type>::ToString(std::get<N>(value));
    }

    template <std::size_t N, typename ArchiveT> static inline typename std::enable_if<N < sizeof...(Types) - 1>::type SerializeHelper(ArchiveT &ar, std::tuple<Types...> const &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        Traits<type>::serialize(ar, std::get<N>(value));
        SerializeHelper<N + 1>(ar, value);
    }

    template <std::size_t N, typename ArchiveT> static inline typename std::enable_if<N == sizeof...(Types) - 1>::type SerializeHelper(ArchiveT &ar, std::tuple<Types...> const &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        Traits<type>::serialize(ar, std::get<N>(value));
    }

    template <std::size_t N, typename ArchiveT> static inline typename std::enable_if<N < sizeof...(Types) - 1>::type DeserializeHelper(ArchiveT &ar, std::tuple<Types...> &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        std::get<N>(value) = Traits<type>::deserialize(ar);
        DeserializeHelper<N + 1>(ar, value);
    }

    template <std::size_t N, typename ArchiveT> static inline typename std::enable_if<N == sizeof...(Types) - 1>::type DeserializeHelper(ArchiveT &ar, std::tuple<Types...> &value) {
        using type = typename std::tuple_element<N, std::tuple<Types...>>::type;

        std::get<N>(value) = Traits<type>::deserialize(ar);
    }
};

namespace Impl {

/////////////////////////////////////////////////////////////////////////
///  \class         CommonDurationTraits
///  \brief         Traits that are common to all duration types
///
template <typename RepT, typename PeriodT>
struct CommonDurationTraits : public TraitsImpl<std::chrono::duration<RepT, PeriodT>> {
    static std::string ToString(std::chrono::duration<RepT, PeriodT> const &duration) {
        std::ostringstream                  out;

        // TODO: This returns an absolutely awful string, but there isn't time to fix it now.
        //       Ideally, this should return something like HH:MM:SS[.Milliseconds]
        date::operator <<(out, duration);
        out.flush();

        return out.str();
    }

    static std::chrono::duration<RepT, PeriodT> FromString(std::string const &value) {
        std::ignore = value; throw std::logic_error("Not Implemented Yet");
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::chrono::duration<RepT, PeriodT> const &duration) {
        return Traits<RepT>::serialize(ar, duration.count());
    }

    template <typename ArchiveT>
    static std::chrono::duration<RepT, PeriodT> deserialize(ArchiveT &ar) {
        return std::chrono::duration<RepT, PeriodT>(Traits<RepT>::deserialize(ar));
    }
};

} // Impl namespace

/////////////////////////////////////////////////////////////////////////
///  \class         Traits
///  \brief         Traits specific to any old duration (not clock-specific)
///
template <typename RepT, typename PeriodT>
struct Traits<std::chrono::duration<RepT, PeriodT>> : public Impl::CommonDurationTraits<RepT, PeriodT> {};

/////////////////////////////////////////////////////////////////////////
///  \class         Traits
///  \brief         These traits are specific to the system clock, which may be
///                 different on different systems. This class contains functionality
///                 that might be impacted by these differences.
///
template <>
struct Traits<std::chrono::system_clock::duration> : public Impl::CommonDurationTraits<std::chrono::system_clock::rep, std::chrono::system_clock::period> {
    // "std::chrono::system_clock::duration" is a specialization of std::chrono::system_clock::duration
    // However it specializes differently on Windows(std::chrono::duration<int64_t, std::ratio<1,10000000>>)
    // and Linux(std::chrono::duration<int64_t, std::ratio<1,1000000000>>). So for serDe, we cast input to a
    // fixed specialization(SystemClockSerDeDurationType).

    using SystemClockDurationRepType = decltype(std::chrono::system_clock::duration())::rep;
    using SystemClockDurationPeriodType = decltype(std::chrono::system_clock::duration())::period;
    using SystemClockSerDeDurationType = std::chrono::duration<int64_t, std::ratio<1,1000>>;

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::chrono::system_clock::duration const &duration) {
        Traits<SystemClockSerDeDurationType>::serialize(ar,std::chrono::duration_cast<SystemClockSerDeDurationType>(duration));
        return ar;
    }

    template <typename ArchiveT>
    static std::chrono::system_clock::duration deserialize(ArchiveT &ar) {
        return std::chrono::duration_cast<std::chrono::system_clock::duration>(Traits<SystemClockSerDeDurationType>::deserialize(ar));
    }
};

template <typename ClockT, typename DurationT>
struct Traits<std::chrono::time_point<ClockT, DurationT>> : public TraitsImpl<std::chrono::time_point<ClockT, DurationT>> {
    static std::string ToString(std::chrono::time_point<ClockT, DurationT> const &tp) {
        return date::format("%FT%TZ", date::floor<std::chrono::seconds>(tp));
    }

    static std::chrono::time_point<ClockT, DurationT> FromString(std::string const &value) {
        // valid iso8601 format can be YYYY-MM-DDTHH:mm:ssZ
        // dashes, T, colons and time zone offset can be optional
        // so we search for these tokens and create a template to be used in parse
        std::string dash_template_component = "";
        std::string colon_template_component = "";
        std::string T_template_component = " ";
        std::string Z_template_component = "Z";

        // use a pointer to make a copy only when necessary
        std::string const * ptr(&value);
        std::string modified;

        if ((value.find_first_of("Z") == std::string::npos)) {
            // there is no Z in the string
            if (value.find_last_of(":") == value.size() - 3) {
                // there is a colon in the time zone
                // remove it
                modified = *ptr;
                modified.erase(modified.size() - 3, 1);
                ptr = &modified;
            }
            Z_template_component = "%z";
        }
        if (!(value.find_first_of("-") == std::string::npos)) {
            // there is - in the string
            dash_template_component = "-";
        }
        if (!(value.find_first_of(":") == std::string::npos)) {
            // there is : in the string
            colon_template_component = ":";
        }
        if (!(value.find_first_of("T") == std::string::npos)) {
            // there is T in the string
            T_template_component = "T";
        }
        std::istringstream ss(*ptr);
        std::ostringstream date_template;
        date_template << "%Y" << dash_template_component << "%m" << dash_template_component << "%d" << T_template_component << "%H" << colon_template_component <<"%M" << colon_template_component << "%S" << Z_template_component;
        date::sys_time<std::chrono::system_clock::duration> tp;
        date::from_stream(ss, date_template.str().c_str(), tp);

        if (ss.fail() ) {
            throw std::invalid_argument("Date time string is not in valid ISO 8601 form!");
        }
        return tp;
    }

    template <typename ArchiveT>
    static ArchiveT & serialize(ArchiveT &ar, std::chrono::time_point<ClockT, DurationT> const &tp) {
        return Traits<DurationT>::serialize(ar, tp.time_since_epoch());
    }

    template <typename ArchiveT>
    static std::chrono::time_point<ClockT, DurationT> deserialize(ArchiveT &ar) {
        return std::chrono::time_point<ClockT, DurationT>(Traits<DurationT>::deserialize(ar));
    }
};

template <typename T>
struct Traits<nonstd::optional<T>>  {
    using nullable_type                     = nonstd::optional<T>;

    static constexpr bool const             IsNullableType = true;
    static constexpr bool const             IsNativeNullableType = false;

    static nullable_type CreateNullValue(void) {
        return nullable_type();
    }

    static bool IsNull(nullable_type const& value) {
        return !value.has_value();
    }

    static T const & GetNullableValue(nullable_type const& value) {
        if (IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a null optional type.");
        return *value;
    }

    static T & GetNullableValue(nullable_type &value) {
        if(IsNull(value))
            throw std::runtime_error("GetNullableValue attempt on a null optional type.");

        return *value;
    }

    static std::string ToString(nullable_type const& value) {
        if (value) {
            return Traits<T>::ToString(*value);
        }
        return "NULL";
    }

    static nonstd::optional<T> FromString(std::string const &value) {
        if(value == "NULL")
            return nonstd::optional<T>();

        return Traits<T>::FromString(value);
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

// TODO: ONNX (Sparse) Tensor
// TODO: Apache Arrow

} // namespace Featurizer
} // namespace Microsoft

template <typename T>
std::ostream & operator <<(std::ostream &os, nonstd::optional<T> const &value) {
    os << Microsoft::Featurizer::Traits<nonstd::optional<T>>::ToString(value);
    return os;
}
