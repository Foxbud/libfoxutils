/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Convenience wrapper around foxutils/map.h for hash tables with
 * C string keys.
 */
#ifndef FOXUTILS_STRINGMAP_H
#define FOXUTILS_STRINGMAP_H

#include "foxutils/map.h"



/* ----- PUBLIC FUNCTIONS ----- */

FoxMap * FoxStringMapNew(
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh
);

void FoxStringMapInit(
		FoxMap * map,
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh
);



#endif /* FOXUTILS_STRINGMAP_H */
