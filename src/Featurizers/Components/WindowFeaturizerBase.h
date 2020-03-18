// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

// namespace Details {

    /////////////////////////////////////////////////////////////////////////
    ///  \class         CircularIterator
    ///  \brief         This class is a forward iterator that is used to implement a
    ///                 circular buffer. If the result of incrementing the iterator
    ///                 would move it past the end of the underlying data structure,
    ///                 it will instead wrap around back to the beginning. This follows
    ///                 STL iterators in that if the underlying data structure is changed,
    ///                 the iterator is invalid and behavior is undefined if used.
    ///                 This class is designed for use with the WindowFeaturizerBase and
    ///                 so it uses assert and not exception. If this class needs to be
    ///                 used elsewhere at a later date, then this will need to be addressed.
    ///
    template <class T>
    class CircularIterator
        : public std::iterator<std::forward_iterator_tag,
                               T,
                               std::ptrdiff_t,
                               T*,
                               T&> {

        // Assert that this class handles all the iterator traits correctly. It inherits from std::iterator so it gets these by default,
        // but this check is here just to guarantee it is correct.
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::difference_type, std::ptrdiff_t>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::value_type, T>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::pointer, T*>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::reference, T&>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::iterator_category, std::forward_iterator_tag>::value, "Make sure standard iterator handles iterator traits correctly!");

    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------

        // Default constructor, already at the "end".
        CircularIterator();

        CircularIterator(T* t, size_t container_max_size, size_t max_increments, size_t starting_offset = 0);

        // Pre-increment operator.
        CircularIterator& operator++ ();

        // Post-increment operator.
        CircularIterator operator++ (int);

        // Two-way comparison: v.begin() == v.cbegin() and vice versa.
        bool operator == (const CircularIterator<T>& rhs) const;

        bool operator != (const CircularIterator<T>& rhs) const;

        T& operator* () const;

        T* operator-> () const;

    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ----------------------------------------------------------------------

        // Pointer to the first element of the underlying data structure.
        T*                                      _itr;

        // The number of elements that the underlying data structure has.
        size_t const                            _size;

        // The index this iterator is pointer it in the underlying data structure.
        size_t                                  _cur_index;

        // The maximum number of times this iterator can be incremented. Since this iterator will
        // wrap at the end of the data structure, there is no real "end" of the data so this is
        // used to determine when we have met the "end".
        size_t const                            _max_increments;

        // How many times we have incremented this iterator.
        size_t                                  _cur_increment;

        // ----------------------------------------------------------------------
        // |
        // |  Private Methods
        // |
        // ----------------------------------------------------------------------

        // check if current iterator is at the end
        bool at_end() const;

    };

    /////////////////////////////////////////////////////////////////////////
    ///  \class         CircularBuffer
    ///  \brief         A custom container class created for operations with shifted windows
    ///                 The goal is to minimize the memory allocation so when the item limit
    ///                 has been reached it overwrites the oldest item it is storing without
    ///                 allocating new memory. This class is designed for use with the
    ///                 WindowFeaturizerBase and so it uses assert and not exception. If this
    ///                 class needs to be used elsewhere at a later date, then this will need
    ///                 to be addressed.
    ///
    template <class T>
    class CircularBuffer {

    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Types
        // |
        // ----------------------------------------------------------------------
        using iterator = CircularIterator<T>;
        using const_iterator = CircularIterator<const T>;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        CircularBuffer(size_t max_size);

        size_t size() const;

        iterator begin();

        const_iterator begin() const;

        const_iterator cbegin() const;

        iterator end();

        const_iterator end() const;

        const_iterator cend() const;

        void push (T value);

        // provide a pair of begin and end iterator for the n elements requested
        std::tuple<iterator, iterator> range(size_t n, size_t offset=0);

        std::tuple<const_iterator, const_iterator> range(size_t n, size_t offset=0) const;

        std::tuple<const_iterator, const_iterator> crange(size_t n, size_t offset=0) const;

    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ----------------------------------------------------------------------

        // Maximum number of elements this container can hold. When this number is reached
        // the oldest value is overwritten.
        size_t const                            _max_size;

        // The start position of this circular buffer. This class is implemented by wrapping around
        // a vector so the "start" will change based on how much data has been overwritten.
        size_t                                  _start_offset;

        // The vector that holds the actual data. This is set to hold _max_size elements and then
        // is never resized.
        std::vector<T>                          _data;

        // ----------------------------------------------------------------------
        // |
        // |  Private Methods
        // |
        // ----------------------------------------------------------------------

        template <typename V>
        V begin_impl();

        template <typename V>
        V end_impl();

        template <typename V>
        std::tuple<V, V> range_impl(size_t n, size_t offset);
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

// ----------------------------------------------------------------------
// |
// |  CircularIterator
// |
// ----------------------------------------------------------------------
template <class T>
CircularIterator<T>::CircularIterator()
    : _itr(nullptr), _size(0), _cur_index(0),
    _max_increments(0), _cur_increment(0) {
}
template <class T>
CircularIterator<T>::CircularIterator(T* t, size_t container_max_size, size_t max_increments, size_t starting_offset)
    : _itr(t), _size(container_max_size), _cur_index(starting_offset),
        _max_increments(max_increments), _cur_increment(0) {
    if(_itr == nullptr) {
        throw std::invalid_argument("Input data cannot be a nullptr");
    }
    if(_size == 0) {
        throw std::invalid_argument("Container max size cannot be 0");
    }
    if(_max_increments > _size) {
        throw std::invalid_argument("Cannot increment more than max_size times");
    }
}
// Pre-increment operator.
template <class T>
CircularIterator<T>& CircularIterator<T>::operator++ () {
    ++_cur_increment;
    assert(_cur_increment <= _max_increments);

    ++_cur_index;
    _cur_index %= _size;
    return *this;
}

// Post-increment operator.
template <class T>
CircularIterator<T> CircularIterator<T>::operator++ (int) {
    CircularIterator tmp(*this);

    operator++();
    return tmp;
}

// Two-way comparison: v.begin() == v.cbegin() and vice versa.
template <class T>
bool CircularIterator<T>::operator == (const CircularIterator<T>& rhs) const {
    // Making sure the end state is the same for both iterators.
    if((at_end() && !rhs.at_end()) || (!at_end() && rhs.at_end())) {
        return false;
    }

    return _itr == rhs._itr && _cur_index == rhs._cur_index;
}

template <class T>
bool CircularIterator<T>::operator != (const CircularIterator<T>& rhs) const {
    return !operator==(rhs);
}

template <class T>
T& CircularIterator<T>::operator* () const {
    assert(_cur_increment != _max_increments);
    return *(_itr+_cur_index);
}

template <class T>
T* CircularIterator<T>::operator-> () const {
    assert(_cur_increment != _max_increments);
    return (_itr+_cur_index);
}

template <class T>
bool CircularIterator<T>::at_end() const {
    return _cur_increment == _max_increments;
}

// ----------------------------------------------------------------------
// |
// |  CircularBuffer
// |
// ----------------------------------------------------------------------

template <class T>
CircularBuffer<T>::CircularBuffer(size_t max_size) : _max_size(max_size), _start_offset(0) {
    if (_max_size == 0) {
        throw std::invalid_argument("Max size cannot be zero");
    }

    _data.reserve(_max_size);
}

template <class T>
size_t CircularBuffer<T>::size() const {
    return _data.size();
}

template <class T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::begin() {
    return begin_impl<iterator>();
}

template <class T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::begin() const {
    return begin_impl<const_iterator>();
}

template <class T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::cbegin() const {
    return begin_impl<const_iterator>();
}

template <class T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::end() {
    return end_impl<iterator>();
}

template <class T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::end() const {
    return end_impl<const_iterator>();
}

template <class T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::cend() const {
    return end_impl<const_iterator>();
}

template <class T>
void CircularBuffer<T>::push (T value) {
    // Make sure we update size and offset accordingly and insert correctly.
    // If we have filled the whole vector, then just update offset.
    if (_data.size() == _max_size) {
        _data[_start_offset] = value;
        ++_start_offset;
        _start_offset %= _max_size;
    } else {
        _data.emplace_back(std::move(value));
    }
}

// provide a pair of begin and end iterator for the n elements requested
template <class T>
typename std::tuple<typename CircularBuffer<T>::iterator, typename CircularBuffer<T>::iterator> CircularBuffer<T>::range(size_t n, size_t offset) {
    return range_impl<iterator>(n, offset);
}

template <class T>
typename std::tuple<typename CircularBuffer<T>::const_iterator, typename CircularBuffer<T>::const_iterator> CircularBuffer<T>::range(size_t n, size_t offset) const {
    return range_impl<const_iterator>(n, offset);
}

template <class T>
typename std::tuple<typename CircularBuffer<T>::const_iterator, typename CircularBuffer<T>::const_iterator> CircularBuffer<T>::crange(size_t n, size_t offset) const {
    return range_impl<const_iterator>(n, offset);
}

template <class T>
template <typename V>
V CircularBuffer<T>::begin_impl() {
    // When _cur_size is 0 we want to return an "end" iterator.
    if (_data.size() == 0) {
        return V();
    }
    return V(_data.data(), _max_size, _data.size(), _start_offset);
}

template <class T>
template <typename V>
V CircularBuffer<T>::end_impl() {
    // End location of the iterator is equal to the start_offset if the buffer is full,
    // or equal to the _cur_size if it isnt full.
    if (_data.size() == 0) {
        return V();
    }
    return V(_data.data(), _max_size, 0, _data.size() == _max_size ? _start_offset : _data.size());
}

template <class T>
template <typename V>
typename std::tuple<V, V> CircularBuffer<T>::range_impl(size_t n, size_t offset) {
    // Since this class is used for window operations only
    // number of requested elements is never bigger than the max_size
    assert(n + offset <= _max_size);

    if(_data.size() == 0) {
        return std::make_tuple(V(), V());
    }
    if(offset > _data.size()) {
        // if even the offset is greater than cur_size, return two end pointers
        return std::make_tuple(end_impl<V>(), end_impl<V>());
    }
    else if(n + offset > _data.size()) {
        // if the sum of n and offset is greater than _data.size(), requested elements are bounded by end()
        return std::make_tuple(V(_data.data(), _max_size, _data.size() - offset, (_start_offset + offset) % _max_size), end_impl<V>());
    }
    else {
        return std::make_tuple(V(_data.data(), _max_size, n, (_start_offset + offset) % _max_size), V(_data.data(), _max_size, 0, (_start_offset + n + offset) % _max_size));
    }
}

} // Components
} // Featurizers
} // Featurizer
} // Microsoft
