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

    template <class Type>
    class CircularIterator
        : public std::iterator<std::forward_iterator_tag,
                               Type,
                               std::ptrdiff_t,
                               Type*,
                               Type&>
    {
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::difference_type, std::ptrdiff_t>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::value_type, Type>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::pointer, Type*>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::reference, Type&>::value, "Make sure standard iterator handles iterator traits correctly!");
        static_assert(std::is_same<typename std::iterator_traits<CircularIterator>::iterator_category, std::forward_iterator_tag>::value, "Make sure standard iterator handles iterator traits correctly!");

        Type* _itr;
        size_t _size;
        size_t _cur;
        size_t _max_increments;
        size_t _cur_increment;
        bool _at_end;

    public:

        CircularIterator(Type* type, size_t container_max_size, size_t max_increments, size_t starting_offset = 0)
            : _itr(type), _size(container_max_size), _cur(starting_offset),
            _max_increments(max_increments), _cur_increment(0)
        {
        }

        CircularIterator& operator++ () // Pre-increment
        {
            assert(++_cur_increment <= _max_increments);

            ++_cur;
            _cur %= _size;
            return *this;
        }

        CircularIterator operator++ (int) // Post-increment
        {
            CircularIterator tmp(*this);

            assert(++_cur_increment <= _max_increments);

            ++_cur;
            _cur %= _size;
            return tmp;
        }

        // two-way comparison: v.begin() == v.cbegin() and vice versa
        template<class OtherType>
        bool operator == (const CircularIterator<OtherType>& rhs) const
        {
            return _itr == rhs._itr && _cur == rhs._cur &&
                !((_cur_increment == _max_increments) ^ (rhs._cur_increment == rhs._max_increments));
        }

        template<class OtherType>
        bool operator != (const CircularIterator<OtherType>& rhs) const
        {
            return !operator==(rhs);
        }

        Type& operator* () const
        {
            assert(_cur_increment != _max_increments);
            return *(_itr+_cur);
        }

        Type* operator-> () const
        {
            assert(_cur_increment != _max_increments);
            return (_itr+_cur);
        }

        // One way conversion: iterator -> const_iterator
        operator CircularIterator<const Type>() const
        {
            return CircularIterator<const Type>(_itr);
        }

    };

} // Components
} // Featurizers
} // Featurizer
} // Microsoft
