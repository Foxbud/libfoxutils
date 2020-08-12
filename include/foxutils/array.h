/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief This module provides a dynamic array data structure.
 */
#ifndef FOXUTILS_ARRAY_H
#define FOXUTILS_ARRAY_H

#include <stddef.h>



/* ----- PUBLIC TYPES ----- */

typedef struct FoxArray {
	unsigned char rawData[
		sizeof(struct {
			unsigned char * elems;
			size_t elemSize;
			size_t size;
			size_t cap;
			float growRate;
		})
	];
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
