/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Open hash table implementation.
 *
 * Because this hash table is open, it can handle arbitrarily large load
 * factors. The trade-off is that it's not as cache-friendly as a closed
 * hash table.
 */
#ifndef FOXUTILS_MAP_H
#define FOXUTILS_MAP_H

#include <stdbool.h>
#include <stddef.h>

#include "foxutils/array.h"



/* ----- PUBLIC MACROS ----- */

#define FOXMAP_DEF_INITSLOTS 64ul

#define FOXMAP_DEF_GROWRATE 4.0f

#define FOXMAP_DEF_LFTHRESH 3.0f

#define FOXMAP_NULL_LFTHRESH -1.0f



/* ----- PUBLIC TYPES ----- */

/**
 * @brief Open hash table data structure.
 *
 * @note While it is possible to directly access this struct's members, using
 * the functions provided by the foxutils/map.h module is preferred.
 */
typedef struct FoxMap {
	FoxArray slots; /**< Map slots (or "buckets") which wrap keys. */
	FoxArray items; /**< Map items which wrap elements. */
	unsigned int (* keyHash)(const void *); /**< Key hashing function. */
	int (* keyCompare)(const void *, const void *); /**< Key comparison
																										function. */
	void (* keyCopy)(void *, const void *); /**< Key duplication function. */
	void (* keyDeinit)(void *); /**< Key de-initialization function. */
	size_t keySize; /**< Size (in bytes) of each map key. */
	size_t elemSize; /**< Size (in bytes) of each map element. */
	float growRate; /**< Map growth rate. */
	float lfThresh; /**< Load factor growth threshold. */
	unsigned int slotIdxMask; /**< Binary mask applied to hashed keys to
															generate a slot index. */
} FoxMap;



/* ----- PUBLIC FUNCTIONS ----- */

FoxMap * FoxMapNew(
		size_t keySize,
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh,
		unsigned int (* keyHash)(const void * key),
		int (* keyCompare)(const void * keyA, const void * keyB),
		void (* keyCopy)(void * copy, const void * key),
		void (* keyDeinit)(void * key)
);

void FoxMapFree(FoxMap * map);

void FoxMapInit(
		FoxMap * map,
		size_t keySize,
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh,
		unsigned int (* keyHash)(const void * key),
		int (* keyCompare)(const void * keyA, const void * keyB),
		void (* keyCopy)(void * copy, const void * key),
		void (* keyDeinit)(void * key)
);

void FoxMapDeinit(FoxMap * map);

size_t FoxMapSize(FoxMap * map);

void * FoxMapIndex(
		FoxMap * map,
		const void * key
);

void * FoxMapInsert(
		FoxMap * map,
		const void * key
);

void FoxMapRemove(
		FoxMap * map,
		const void * key,
		void * elem
);

float FoxMapLoadFactor(FoxMap * map);

void FoxMapExpand(FoxMap * map);

void FoxMapForEachPair(
		FoxMap * map,
		bool (* callback)(const void * key, void * elem, void * ctx),
		void * ctx
);

void FoxMapForEachElement(
		FoxMap * map,
		bool (* callback)(void * elem, void * ctx),
		void * ctx
);

void FoxMapForEachKey(
		FoxMap * map,
		bool (* callback)(const void * key, void * ctx),
		void * ctx
);



#endif /* FOXUTILS_MAP_H */
