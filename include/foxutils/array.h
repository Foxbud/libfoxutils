/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Dynamic array implementation.
 */
#ifndef FOXUTILS_ARRAY_H
#define FOXUTILS_ARRAY_H

#include <stddef.h>



/* ----- PUBLIC MACROS ----- */

#define FOXARRAY_DEF_INITCAP 16ul

#define FOXARRAY_DEF_GROWRATE 2.0f



/* ----- PUBLIC TYPES ----- */

/**
 * @brief Dynamic array.
 *
 * While it is possible to directly access this struct's members, using
 * the functions provided by this module is preferred.
 */
typedef struct FoxArray {
	unsigned char * elems; /**< Underlying C array. */
	size_t elemSize; /**< Size (in bytes) of each array element. */
	size_t size; /**< Number of elements in the array. */
	size_t cap; /**< Total capacity of array (in elements, not bytes). */
	float growRate; /**< Array growth rate. */
} FoxArray;



/* ----- PUBLIC FUNCTIONS ----- */

FoxArray * FoxArrayNew(
		size_t elemSize,
		size_t initCap,
		float growRate
);

void FoxArrayFree(FoxArray * array);

void FoxArrayInit(
		FoxArray * array,
		size_t elemSize,
		size_t initCap,
		float growRate
);

void FoxArrayDeinit(FoxArray * array);

size_t FoxArraySize(FoxArray * array);

void * FoxArrayIndex(
		FoxArray * array,
		unsigned int idx
);

void * FoxArrayInsert(
		FoxArray * array,
		unsigned int idx
);

void FoxArrayRemove(
		FoxArray * array,
		unsigned int idx,
		void * elem
);



#endif /* FOXUTILS_ARRAY_H */
