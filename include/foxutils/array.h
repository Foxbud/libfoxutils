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

/**
 * Allocate a block of memory and initialize  it as a dynamic array.
 *
 * @note Every call to this function must have a corresponding call to
 * FoxArrayFree().
 *
 * @param[in] elemSize Size (in bytes) of each array element.
 * @param[in] initCap Initial capacity of array (will increase as necessary).
 * @param[in] growRate Ratio by which to increase capacity when array expands.
 *
 * @return Pointer to newly allocated and initialized array.
 */
FoxArray * FoxArrayNew(
		size_t elemSize,
		size_t initCap,
		float growRate
);

/**
 * De-initialize and de-allocate a dynamic array.
 *
 * @note Only use this function on arrays initialized with FoxArrayNew().
 *
 * @param[in] array Array to de-initialize and de-allocate.
 */
void FoxArrayFree(FoxArray * array);

/**
 * Initialize an existing block of memory as a dynamic array.
 *
 * @note Every call to this function must have a corresponding call to
 * FoxArrayDeinit().
 *
 * @param[out] array Memory to initialize as array.
 *
 * @param[in] elemSize Size (in bytes) of each array element.
 * @param[in] initCap Initial capacity of array (will increase as necessary).
 * @param[in] growRate Ratio by which to increase capacity when array expands.
 */
void FoxArrayInit(
		FoxArray * array,
		size_t elemSize,
		size_t initCap,
		float growRate
);

/**
 * De-initialize a dynamic array.
 *
 * @note Only use this function on arrays initialized with FoxArrayInit().
 *
 * @param[in] array Array to de-initialize.
 */
void FoxArrayDeinit(FoxArray * array);

/**
 * Get the size of a dynamic array.
 *
 * The size returned by this function is the total number of elements
 * currently in the array, **not** the total capacity of the array.
 *
 * @param[in] array Array to get size of.
 *
 * @return Size of array.
 */
size_t FoxArraySize(FoxArray * array);

void * FoxArrayIndex(
		FoxArray * array,
		unsigned int idx
);

void * FoxArrayPeek(FoxArray * array);

void * FoxArrayInsert(
		FoxArray * array,
		unsigned int idx
);

void * FoxArrayPush(FoxArray * array);

void FoxArrayRemove(
		FoxArray * array,
		unsigned int idx,
		void * elem
);

void FoxArrayPop(
		FoxArray * array,
		void * elem
);



#endif /* FOXUTILS_ARRAY_H */
