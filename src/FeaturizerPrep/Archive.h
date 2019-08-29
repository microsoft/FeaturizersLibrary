// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <stdexcept>
#include <vector>

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

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    ByteArray                               _buffer;

    unsigned char const *                   _pBuffer;
    unsigned char const * const             _pEndBuffer;
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
    static_assert(std::is_pod<T>::value, "T must be a POD");
    return serialize(reinterpret_cast<unsigned char const *>(&value), sizeof(value));
}

inline Archive::ByteArray Archive::commit(void) {
    if(Mode != ModeValue::Serializing)
        throw std::runtime_error("Invalid mode");

    return std::move(_buffer);
}

template <typename T>
T Archive::deserialize(void) {
    static_assert(std::is_pod<T>::value, "T must be a POD");

    if(Mode != ModeValue::Deserializing)
        throw std::runtime_error("Invalid mode");

    if(static_cast<size_t>(_pEndBuffer - _pBuffer) < sizeof(T))
        throw std::runtime_error("Invalid buffer");

    T                                       value(*reinterpret_cast<T const *>(_pBuffer));

    _pBuffer += sizeof(T);
    return value;
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

} // namespace Featurizer
} // namespace Microsoft
