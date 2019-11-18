/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#include "SharedLibrary_PointerTable.h"

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

Microsoft::Featurizer::PointerTable g_pointerTable;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
