// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"
#include "../Traits.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \namespace     SampleAdd
///  \brief         A Transformer and Estimator that add values. This is a
///                 sample intended to demonstrate patterns within the
///                 implementation of these types.
///
namespace StringTransformer {

/////////////////////////////////////////////////////////////////////////
///  \class         Transformer
///  \brief         Transformer that adds an integer value to a saved delta
///                 and returns the result.
///
template <typename argT>
class Transformer : public Microsoft::Featurizer::Transformer<std::string, argT> {
public:
    // ----------------------------------------------------------------------
    // |  Public Methods
    Transformer() = default;
    ~Transformer() override = default;

    Transformer(Transformer const &) = delete;
    Transformer & operator =(Transformer const &) = delete;

    Transformer(Transformer &&) = default;
    Transformer & operator =(Transformer &&) = delete;

    std::string transform(argT const &arg) const override
    {
        return Traits::Traits<argT>::ToString(arg);
    }

private:
    // ----------------------------------------------------------------------
    // |  Relationships
    //friend class boost::serialization::access;

    // ----------------------------------------------------------------------
    // |  Private Methods
    template <typename ArchiveT>
    void serialize(ArchiveT &ar, unsigned int const version);
};

} // namespace StringTransformer
} // namespace Featurizer
} // namespace Microsoft
