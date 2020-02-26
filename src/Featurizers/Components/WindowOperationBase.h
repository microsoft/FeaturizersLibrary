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
    template <class T>
    class CircularIterator
        : public std::iterator<std::forward_iterator_tag,
                               T,
                               std::ptrdiff_t,
                               T*,
                               T&> {

        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::difference_type, std::ptrdiff_t>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::value_type, T>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::pointer, T*>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::reference, T&>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::iterator_category, std::forward_iterator_tag>::value, "Make sure standard iterator handles iterator traits correctly!");

        T* _itr;
        size_t _size;
        size_t _cur_index;
        size_t _max_increments;
        size_t _cur_increment;

    public:

        CircularIterator()
            : _itr(nullptr), _size(0), _cur_index(0),
            _max_increments(0), _cur_increment(0) {
        }

        CircularIterator(T* T, size_t container_max_size, size_t max_increments, size_t starting_offset = 0)
            : _itr(T), _size(container_max_size), _cur_index(starting_offset),
            _max_increments(max_increments), _cur_increment(0) {
        }

        // Pre-increment
        CircularIterator& operator++ () {
            assert(++_cur_increment <= _max_increments);

            ++_cur_index;
            _cur_index %= _size;
            return *this;
        }

        // Post-increment
        CircularIterator operator++ (int) {
            CircularIterator tmp(*this);

            assert(++_cur_increment <= _max_increments);

            ++_cur_index;
            _cur_index %= _size;
            return tmp;
        }

        // two-way comparison: v.begin() == v.cbegin() and vice versa
        template<class OtherType>
        bool operator == (const CircularIterator<OtherType>& rhs) const {
            return _itr == rhs._itr && _cur_index == rhs._cur_index &&
                !((_cur_increment == _max_increments) ^ (rhs._cur_increment == rhs._max_increments));
        }

        template<class OtherType>
        bool operator != (const CircularIterator<OtherType>& rhs) const {
            return !operator==(rhs);
        }

        T& operator* () const {
            assert(_cur_increment != _max_increments);
            return *(_itr+_cur_index);
        }

        T* operator-> () const {
            assert(_cur_increment != _max_increments);
            return (_itr+_cur_index);
        }

        // One way conversion: iterator -> const_iterator
        operator CircularIterator<const T>() const {
            return CircularIterator<const T>(_itr);
        }

    };

    template <class T>
    class CircularBuffer {

        size_t _max_size;
        size_t _start_offset;
        size_t _cur_size;

        std::vector<T> _data;

    public:
        typedef CircularIterator<T> iterator;
        typedef CircularIterator<const T> const_iterator;

        CircularBuffer(size_t max_size) : _max_size(max_size), _start_offset(0),  _cur_size(0) {
            _data.reserve(_max_size);
        }

        iterator begin() {
            if (_cur_size == 0) {
                return iterator();
            }
            return iterator(&_data[0], _max_size, _cur_size, _start_offset);
        }

        const_iterator begin() const {
            return begin();
        }

        const_iterator cbegin() const {
            return begin();
        }

        iterator end() {
            // End location of the iterator is equal to the start_offset if the buffer is full,
            // or equal to the _cur_size if it isnt full.
            if (_cur_size == 0) {
                return iterator();
            }
            return iterator(&_data[0], _max_size, 0, _cur_size == _max_size ? _start_offset : _cur_size);
        }

        const_iterator end() const {
            return end();
        }

        const_iterator cend() const {
            return end();
        }

        void push (T value) {
            // Make sure we update size and offset accordingly and insert correctly.
            // If we have filled the whole vector, then just update offset.
            // If vector still has space, then just update the _cur_size;
            if (_cur_size == _max_size) {
                _data[_start_offset] = value;
                ++_start_offset;
                _start_offset %= _max_size;
            } else {
                _data.emplace_back(std::move(value));
                ++_cur_size;
            }
        }

        std::tuple<iterator, iterator> range(size_t n) {
            // Since this class is used for window operations only
            // number of requested elements is never bigger than the max_size
            assert(n <= _max_size);
            if(n > _cur_size) {
                return std::make_tuple(begin(), end());
            }
            else {
                return std::make_tuple(iterator(&_data[0], _max_size, n, _start_offset), iterator(&_data[0], _max_size, 0, _start_offset + n));
            }
        }

        std::tuple<const_iterator, const_iterator> range(size_t n) const {
            // Sicne this class is used for window operations only
            // number of requested elements is never bigger than the max_size
            return range(n);

        }

        std::tuple<const_iterator, const_iterator> crange(size_t n) const {
            // Sicne this class is used for window operations only
            // number of requested elements is never bigger than the max_size
            return range(n);

        }

    };

} // Components
} // Featurizers
} // Featurizer
} // Microsoft
