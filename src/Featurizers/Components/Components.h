// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \namespace     Component
///  \brief         Most featurizers are comprised of multiple sub-featurizers
///                 organized into a DAG (or pipeline). As it turns out, there
///                 are a relatively small number of components used to construct
///                 a surprisingly large number of featurizers. Featurizers within
///                 this namespace are intended to be used in the DAGs of Featurizers
///                 exposed from this library.
///
namespace Component {

} // namespace Component
} // namespace Featurizer
} // namespace Microsoft
