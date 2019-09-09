// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once
#include <unordered_map>
#include <random>
#include <assert.h>
#include <stdexcept>

namespace Microsoft{
namespace Featurizer{
    
/////////////////////////////////////////////////////////////////////////
///  \class         PointerTable
///  \brief         Provide an interface to store pointers in exchange of
///                 an index to avoid exposing pointers to users
///
class PointerTable {
    public:
        
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    
        PointerTable(unsigned int seed = (std::random_device())());

        template<typename T> 
        uint32_t Add(const T* const toBeAdded);

        template<typename T> 
        T* Find(uint32_t index);

        void Remove(uint32_t index);

    private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
        std::unordered_map<std::uint32_t, const void*>   m_un;
        std::mt19937 m_mt;

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
    inline PointerTable::PointerTable(unsigned int seed) : m_mt(seed) {
        
    }


    template<typename T>
    uint32_t PointerTable::Add(const T * const templatePointer) {
        if (templatePointer == nullptr) {
            throw std::invalid_argument("Trying to add a null pointer to the table!");
        }


        const void* const toBeAdded = reinterpret_cast<const void* const>(templatePointer);
        
        // since we are controling where and how to use PointerTable and Add function
        // it wouldn't worth the cost to have two maps with atomic insertions
        // check for duplicates at run time
        // comparing to the chance of adding the same pointer twice,
        // so we would only check for duplicates in debug mode
        #ifndef NDEBUG
            for (auto pairs : m_un) {
                assert(pairs.second != toBeAdded);
            }
        #endif

        uint32_t empty_index = 0;

        // size would be changing throughout the process
        // index zero is reserved
        std::uniform_int_distribution<uint32_t> dist(1,UINT32_MAX);

        while(true) {
            uint32_t rand_index = dist(m_mt);
            if (m_un.find(rand_index) == m_un.end()) {
                empty_index = rand_index;
                break;
            }
        }
        assert(empty_index != 0);
        m_un[empty_index] = toBeAdded;
        return empty_index;
    }
    
    template<typename T>
    T* PointerTable::Find(uint32_t index) {
        // pre-check
        if (index == 0) {
            throw std::invalid_argument("Invalid query to the Pointer table, index cannot be zero!");
        }


        std::unordered_map<std::uint32_t, const void*>::const_iterator found = m_un.find(index);
        if (found == m_un.end()) {
            throw std::invalid_argument("Invalid query to the Pointer table, index incorrect!");
        }
        return reinterpret_cast<T*>(const_cast<void*>(found->second));
    }


    inline void PointerTable::Remove(uint32_t index) {
        // pre-check
        if (index == 0) {
            throw std::invalid_argument("Invalid remove from the Pointer table, index cannot be zero!");
        }


        std::unordered_map<std::uint32_t, const void*>::const_iterator found = m_un.find(index);
        if (found == m_un.end()) {
            throw std::invalid_argument("Invalid remove from the Pointer table, index pointer not found!");
        }
        m_un.erase(found);
    }
} // namespace Featurizer
} // namespace Microsoft
