/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief This module provides an open hash table.
 */
#ifndef FOXUTILS_MAP_H
#define FOXUTILS_MAP_H

#include <stdbool.h>
#include <stddef.h>



/* ----- PUBLIC TYPES ----- */

typedef struct FoxMap {
	unsigned char rawData[
		sizeof(struct {
			size_t keySize;
			size_t elemSize;
			size_t slotEntrySize;
			size_t itemSize;
			float growRate;
			float lfThresh;
			unsigned int slotIdxMask;
			FoxArray slots;
			FoxArray items;
			unsigned int (* keyHash)(const void *);
			int (* keyCompare)(const void *, const void *);
			void (* keyCopy)(void *, const void *);
			void (* keyDeinit)(void *);
		})
	];
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
