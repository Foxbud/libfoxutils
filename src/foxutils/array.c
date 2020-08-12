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



/* ----- PRIVATE TYPES ----- */

typedef struct Array {
	unsigned char * elems;
	size_t elemSize;
	size_t size;
	size_t cap;
	float growRate;
} Array;



/* ----- PRIVATE CONSTANTS ----- */

static const size_t DEFAULT_INIT_CAP = 16;

static const float DEFAULT_GROW_RATE = 2.0f;



/* ----- PUBLIC FUNCTIONS ----- */

FoxArray * FoxArrayNew(
		size_t elemSize,
		size_t initCap,
		float growRate
) {
	FoxArray * array = malloc(sizeof(Array));
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
#define array ((Array *)array)
	assert(array);
	assert(elemSize > 0);
	assert(growRate >= 0.0f);

	array->cap = (initCap > 0) ? initCap : DEFAULT_INIT_CAP;
	array->growRate = (growRate > 1.0f) ? growRate : DEFAULT_GROW_RATE;
	assert((size_t)(array->cap * array->growRate) > array->cap);

	array->elems = malloc(elemSize * array->cap);
	assert(array->elems);
	array->elemSize = elemSize;
	array->size = 0;

	return;
#undef array
}

void FoxArrayDeinit(FoxArray * array) {
#define array ((Array *)array)
	assert(array);

	free(array->elems);
	array->elems = NULL;
	array->elemSize = array->size = array->cap = 0;
	array->growRate = 0.0f;

	return;
#undef array
}

inline size_t FoxArraySize(FoxArray * array) {
	assert(array);

	return ((Array *)array)->size;
}

void * FoxArrayIndex(
		FoxArray * array,
		unsigned int idx
) {
#define array ((Array *)array)
	assert(array);
	assert(idx < array->size);

	return array->elems + array->elemSize * idx;
#undef array
}

void * FoxArrayInsert(
		FoxArray * array,
		unsigned int idx
) {
#define array ((Array *)array)
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
#undef array
}

void FoxArrayRemove(
		FoxArray * array,
		unsigned int idx,
		void * elem
) {
#define array ((Array *)array)
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
#undef array
}
