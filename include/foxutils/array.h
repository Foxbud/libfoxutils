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

/**
 * Dynamic array default initial capacity.
 */
#define FOXARRAY_DEF_INITCAP 16ul

/**
 * Dynamic array default growth rate.
 */
#define FOXARRAY_DEF_GROWRATE 2.0f



/* ----- PUBLIC TYPES ----- */

/**
 * @brief Dynamic array data structure.
 *
 * @note While it is possible to directly access this struct's members, using
 * the functions provided by the foxutils/array.h module is preferred.
 */
typedef struct FoxArray {
	unsigned char * elems; /**< Underlying C array. */
	size_t elemSize; /**< Size (in bytes) of each array element. */
	size_t size; /**< Number of elements in the array. */
	size_t cap; /**< Total capacity of array (in elements, not bytes). */
	float growRate; /**< Array growth rate. */
} FoxArray;
/**
 * @example array.c
 *
 * This is an example of how to use the foxutils/array.h module.
 *
 * <br />
 * Program output:
 * <br />
 * <tt>First 5 prime(s): 2 3 5 7 11.</tt>
 */



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
 * @param[in] array Array from which to get size.
 *
 * @return Size of array.
 */
size_t FoxArraySize(FoxArray * array);

/**
 * Get an element in a dynamic array.
 *
 * @param[in] array Array from which to get element.
 * @param[in] idx Index of element to get.
 *
 * @return Pointer to requested element.
 */
void * FoxArrayIndex(
		FoxArray * array,
		unsigned int idx
);

/**
 * Get the last element in a dynamic array.
 *
 * @param[in] array Array from which to get element.
 *
 * @return Pointer to last element.
 */
void * FoxArrayPeek(FoxArray * array);

/**
 * Insert an element into a dynamic array.
 *
 * The new element will be inserted immediately *before* the element at
 * the provided index. As a special case, if the provided index is equivalent
 * to the size of the array, then the new element will be inserted immediately
 * *after* the last element in the array.
 *
 * @param[in] array Array to insert element into.
 * @param[in] idx Index to insert element at.
 *
 * @return Pointer to new, zero-initialized element.
 */
void * FoxArrayInsert(
		FoxArray * array,
		unsigned int idx
);

/**
 * Insert an element at the end of a dynamic array.
 *
 * @param[in] array Array to insert element into.
 *
 * @return Pointer to new, zero-initialized element.
 */
void * FoxArrayPush(FoxArray * array);

/**
 * Remove an element from a dynamic array.
 *
 * @param[in] array Array to remove element from.
 * @param[in] idx Index of element to remove.
 *
 * @param[out] elem Removed element (can be NULL).
 */
void FoxArrayRemove(
		FoxArray * array,
		unsigned int idx,
		void * elem
);

/**
 * Remove an element from the end of a dynamic array.
 *
 * @param[in] array Array to remove element from.
 *
 * @param[out] elem Removed element (can be NULL).
 */
void FoxArrayPop(
		FoxArray * array,
		void * elem
);



#endif /* FOXUTILS_ARRAY_H */
