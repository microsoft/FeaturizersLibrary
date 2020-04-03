// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Traits.h"

#include <stdexcept>

#if (!defined ISLITTLEENDIAN)
# define ISLITTLEENDIAN 1
#endif

static bool constexpr is_little_endian = bool(ISLITTLEENDIAN);

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         Archive
///  \brief         Object that can be used when serializing and deserializing
///                 data associated with a class. This data produced during
///                 serialization and consumed during deserialization should
///                 be considered binary data.
///
class Archive {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    ///  \enum          ModeValue
    ///  \brief         Indicates how an `Archive` instance is being used.
    ///
    enum class ModeValue {
        Serializing,                        /// The `Archive` instance is being used to serialize data
        Deserializing                       /// The `Archive` instance is being used to deserialize data
    };

    using ByteArray                         = std::vector<unsigned char>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    ModeValue const                         Mode;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    Archive(size_t cReservedSize=0);
    Archive(ByteArray data);
    Archive(unsigned char const *pBuffer, size_t cbBuffer);

    ~Archive(void) = default;

    Archive(Archive const &) = delete;
    Archive & operator =(Archive const &) = delete;

    Archive(Archive &&) = default;
    Archive & operator =(Archive &&) = delete;

    // Methods value when `Mode` is `ModeValue::Serializing`
    Archive & serialize(unsigned char const *pBuffer, size_t cBuffer);
    template <typename T> Archive & serialize(T const &value);

    ByteArray commit(void);

    // Methods valid when `Mode` is `ModeValue::Deserialzing`
    unsigned char const * get_buffer_ptr(void) const;
    Archive & update_buffer_ptr(size_t cDelta);

    template <typename T> T deserialize(void);

    bool AtEnd(void) const;

    Archive clone(void) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    ByteArray                               _buffer;

    unsigned char const *                   _pBuffer;
    unsigned char const * const             _pEndBuffer;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    template <typename T> Archive & serialize_impl(T const &value, std::true_type);
    template <typename T> Archive & serialize_impl(T const &value, std::false_type);

    template <typename T> T deserialize_impl(std::true_type);
    template <typename T> T deserialize_impl(std::false_type);
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
inline Archive::Archive(size_t cReservedSize) :
    Mode(ModeValue::Serializing),
    _buffer(
        [&cReservedSize](void) -> ByteArray {
            ByteArray                       result;

            if(cReservedSize != 0)
                result.reserve(cReservedSize);

            return result;
        }()
    ),
    _pBuffer(nullptr),
    _pEndBuffer(nullptr) {
}

inline Archive::Archive(ByteArray data) :
    Mode(ModeValue::Deserializing),
    _buffer(std::move(data)),
    _pBuffer(_buffer.data()),
    _pEndBuffer(_pBuffer + _buffer.size()) {
}

inline Archive::Archive(unsigned char const *pBuffer, size_t cbBuffer) :
    Mode(ModeValue::Deserializing),
    _pBuffer(pBuffer),
    _pEndBuffer(_pBuffer + cbBuffer)
{
    if((pBuffer == nullptr && cbBuffer != 0) || (pBuffer != nullptr && cbBuffer == 0))
        throw std::invalid_argument("Invalid input buffer");
}

inline Archive & Archive::serialize(unsigned char const *pBuffer, size_t cBuffer) {
    if(Mode != ModeValue::Serializing)
        throw std::runtime_error("Invalid mode");

    if((pBuffer == nullptr && cBuffer != 0) || (pBuffer != nullptr && cBuffer == 0))
        throw std::invalid_argument("Invalid buffer");

    std::copy(pBuffer, pBuffer + cBuffer, std::back_inserter(_buffer));

    return *this;
}

template <typename T>
Archive & Archive::serialize(T const &value) {
    return serialize_impl(value, std::integral_constant<bool, ISLITTLEENDIAN>());
}

inline Archive::ByteArray Archive::commit(void) {
    if(Mode != ModeValue::Serializing)
        throw std::runtime_error("Invalid mode");

    return std::move(_buffer);
}

template <typename T>
T Archive::deserialize(void) {
    return deserialize_impl<T>(std::integral_constant<bool, ISLITTLEENDIAN>());
}

inline unsigned char const * Archive::get_buffer_ptr(void) const {
    if(Mode != ModeValue::Deserializing)
        throw std::runtime_error("Invalid mode");

    if(_pBuffer == _pEndBuffer)
        throw std::runtime_error("Invalid buffer");

    return _pBuffer;
}

inline Archive & Archive::update_buffer_ptr(size_t cDelta) {
    if(Mode != ModeValue::Deserializing)
        throw std::runtime_error("Invalid mode");

    unsigned char const *                   pNewBuffer(_pBuffer + cDelta);

    if(pNewBuffer > _pEndBuffer)
        throw std::invalid_argument("Invalid delta");

    _pBuffer = pNewBuffer;
    return *this;
}

inline bool Archive::AtEnd(void) const {
    if(Mode != ModeValue::Deserializing)
        throw std::runtime_error("Invalid mode");

    return _pBuffer == _pEndBuffer;
}

inline Archive Archive::clone(void) const {
    if(Mode != ModeValue::Deserializing)
        throw std::runtime_error("Invalid mode");

    if(_pBuffer == _pEndBuffer)
        throw std::runtime_error("It isn't possible to clone a completed archive");

    return Archive(ByteArray(_pBuffer, _pEndBuffer));
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
namespace {

template <typename T>
T swap_endian(T u) {
    unsigned char* source(reinterpret_cast<unsigned char*>(&u));
    unsigned char dest[sizeof(T)];

    for (size_t k = 0; k < sizeof(T); k++)
        dest[k] = *(source+sizeof(T) - k - 1);

    return *reinterpret_cast<T*>(dest);
}

} // anonymous namespace

template <typename T>
Archive & Archive::serialize_impl(T const &value, std::true_type) {
    static_assert(std::is_pod<T>::value, "T must be a POD");
    return serialize(reinterpret_cast<unsigned char const *>(&value), sizeof(value));
}

template <typename T>
Archive & Archive::serialize_impl(T const &value, std::false_type) {
    return serialize_impl(swap_endian<T>(value), std::true_type());
}

template <typename T>
T Archive::deserialize_impl(std::true_type) {
    static_assert(std::is_pod<T>::value, "T must be a POD");

    if(Mode != ModeValue::Deserializing)
        throw std::runtime_error("Invalid mode");

    if(static_cast<size_t>(_pEndBuffer - _pBuffer) < sizeof(T))
        throw std::runtime_error("Invalid buffer");

    T                                       value(*reinterpret_cast<T const *>(_pBuffer));

    _pBuffer += sizeof(T);
    return value;
}

template <typename T>
T Archive::deserialize_impl(std::false_type) {
    return swap_endian<T>(deserialize_impl<T>(std::true_type()));
}

} // namespace Featurizer
} // namespace Microsoft
