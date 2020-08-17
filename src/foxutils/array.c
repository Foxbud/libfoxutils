/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "foxutils/array.h"



/* ----- PUBLIC FUNCTIONS ----- */

FoxArray * FoxArrayNew(
		size_t elemSize,
		size_t initCap,
		float growRate
) {
	FoxArray * array = calloc(1, sizeof(FoxArray));
	FoxArrayInit(array, elemSize, initCap, growRate);

	return array;
}

void FoxArrayFree(FoxArray * array) {
	FoxArrayDeinit(array);
	free(array);

	return;
}

void FoxArrayInit(
		FoxArray * array,
		size_t elemSize,
		size_t initCap,
		float growRate
) {
	assert(array);
	assert(elemSize > 0);
	assert(initCap > 0);
	assert(growRate > 1.0f);
	assert((size_t)(initCap * growRate) > initCap);

	array->elemSize = elemSize;
	array->size = 0;
	array->cap = initCap;
	array->growRate = growRate;

	array->elems = malloc(elemSize * initCap);
	assert(array->elems);

	return;
}

void FoxArrayDeinit(FoxArray * array) {
	assert(array);

	free(array->elems);
	*array = (FoxArray){0};

	return;
}

size_t FoxArraySize(FoxArray * array) {
	assert(array);

	return array->size;
}

bool FoxArrayEmpty(FoxArray * array) {
	assert(array);

	return array->size == 0;
}

void FoxArrayEnsureCapacity(
		FoxArray * array,
		size_t cap
) {
	assert(array);

	if (array->cap < cap) {
		array->elems = realloc(array->elems, array->elemSize * cap);
		assert(array->elems);
	}

	return;
}

void * FoxArrayIndex(
		FoxArray * array,
		unsigned int idx
) {
	assert(array);
	assert(idx < array->size);

	return array->elems + array->elemSize * idx;
}

void * FoxArrayPeek(FoxArray * array) {
	assert(array);
	size_t numElems = array->size;
	assert(numElems > 0);

	return array->elems + array->elemSize * (numElems - 1);
}

void * FoxArrayInsert(
		FoxArray * array,
		unsigned int idx
) {
	assert(array);
	assert(idx <= array->size);
	size_t elemSize = array->elemSize;

	/* Ensure sufficient capacity. */
	if (array->size == array->cap) {
		array->cap *= array->growRate;
		array->elems = realloc(array->elems, elemSize * array->cap);
		assert(array->elems);
	}

	/* Get target element. */
	unsigned char * targElem = array->elems + elemSize * idx;

	/* Shift existing elements if necessary. */
	if (idx < array->size++) {
		memmove(
				targElem + elemSize,
				targElem,
				elemSize * (array->size - 1 - idx)
		);
	}

	/* Initialize target element. */
	memset(targElem, 0, elemSize);

	return targElem;
}

void * FoxArrayPush(FoxArray * array) {
	assert(array);

	return FoxArrayInsert(array, array->size);
}

void FoxArrayRemove(
		FoxArray * array,
		unsigned int idx,
		void * elem
) {
	assert(array);
	assert(idx < array->size);
	size_t elemSize = array->elemSize;

	/* Get target element. */
	unsigned char * targElem = array->elems + elemSize * idx;

	/* Copy target element if requested. */
	if (elem) memcpy(elem, targElem, elemSize);

	/* Shift existing elements if necessary. */
	if (idx < --array->size) {
		memmove(
				targElem,
				targElem + elemSize,
				array->elemSize * (array->size + 1 - idx)
		);
	}

	return;
}

void FoxArrayPop(
		FoxArray * array,
		void * elem
) {
	assert(array);

	FoxArrayRemove(array, array->size - 1, elem);

	return;
}
