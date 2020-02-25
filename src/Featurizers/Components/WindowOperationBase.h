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

        CircularIterator(Type* i, size_t s) 
            : itr(i), size(s), curr(0)
        { 
        }

        CircularIterator& operator++ () // Pre-increment
        {
            ++curr;
            curr %= size;
            return this;
        }

        CircularIterator operator++ (int) // Post-increment
        {
            CircularIterator tmp(*this);
            ++curr;
            curr %= size;
            return tmp; 
        }

        // two-way comparison: v.begin() == v.cbegin() and vice versa
        template<class OtherType>
        bool operator == (const CircularIterator<OtherType>& rhs) const
        {
            return itr == rhs.itr;
        }

        template<class OtherType>
        bool operator != (const CircularIterator<OtherType>& rhs) const
        {
            return itr != rhs.itr;
        }

        Type& operator* () const
        {
            return *(itr+curr);
        }

        Type& operator-> () const
        {
            return *(itr+curr);
        }

        // One way conversion: iterator -> const_iterator
        operator CircularIterator<const Type>() const
        {
            return CircularIterator<const Type>(itr);
        }
    };




    // `iterator` and `const_iterator` used by your class:
    // typedef CircularIterator<T> iterator;
    // typedef CircularIterator<const T> const_iterator;
    // }




} // Components
} // Featurizers
} // Featurizer
} // Microsoft
