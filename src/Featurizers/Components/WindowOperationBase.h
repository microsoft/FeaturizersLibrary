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
        Type* itr;
        size_t size;
        size_t curr;

    public:

        CircularIterator(Type* i, size_t s, size_t starting_offset = 0) 
            : itr(i), size(s), curr(starting_offset)
        { 
        }

        CircularIterator& operator++ () // Pre-increment
        {
            ++curr;
            curr %= size;
            return *this;
        }

        CircularIterator operator++ (int) // Post-increment
        {
            CircularIterator tmp(*this);
            ++curr;
            curr %= size;
            return tmp; 
        }

        CircularIterator operator+ (int amount)
        {
            CircularIterator tmp(*this);
            tmp.curr = (tmp.curr + amount) % tmp.size;
            return tmp; 
        }

        // two-way comparison: v.begin() == v.cbegin() and vice versa
        template<class OtherType>
        bool operator == (const CircularIterator<OtherType>& rhs) const
        {
            return itr == rhs.itr && curr == rhs.curr && size == rhs.size;
        }

        template<class OtherType>
        bool operator != (const CircularIterator<OtherType>& rhs) const
        {
            return itr != rhs.itr || curr != rhs.curr || size != rhs.size;
        }

        Type& operator* () const
        {
            return *(itr+curr);
        }

        Type* operator-> () const
        {
            return (itr+curr);
        }

        // One way conversion: iterator -> const_iterator
        operator CircularIterator<const Type>() const
        {
            return CircularIterator<const Type>(itr);
        }
    };

} // Components
} // Featurizers
} // Featurizer
} // Microsoft
