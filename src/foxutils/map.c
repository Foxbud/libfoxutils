/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "foxutils/hash.h"
#include "foxutils/map.h"



/* ----- PRIVATE MACROS ----- */

#define ItemSize(map) (sizeof(Item) + (map)->elemSize)

#define SlotEntrySize(map) (sizeof(SlotEntry) + (map)->keySize)



/* ----- PRIVATE TYPES ----- */

typedef struct Item {
	unsigned int slotIdx;
	unsigned int slotEntryIdx;
	unsigned char elem[];
} Item;

typedef struct SlotEntry {
	unsigned int itemIdx;
	unsigned char key[];
} SlotEntry;



/* ----- PRIVATE FUNCTIONS ----- */

/* 
 * As described by Sean Eron Anderson of Standford University at
 * "https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2".
 */
static inline unsigned long RoundUpPowTwo(unsigned long val) {
	unsigned long result = val - 1;
	result |= result >> 1;
	result |= result >> 2;
	result |= result >> 4;
	result |= result >> 8;
	result |= result >> 16;
	#if __SIZEOF_LONG__ > 4
		result |= result >> 32;
	#endif

	return result + 1;
}

static inline float LoadFactor(FoxMap * map, int itemAddend) {
	return (float)(FoxArraySize(&map->items) + itemAddend)
		/ (float)FoxArraySize(&map->slots);
}

static inline bool ItemLookup(
		FoxMap * map,
		const void * key,
		unsigned int * slotIdx,
		unsigned int * slotEntryIdx,
		unsigned int * itemIdx
) {
	bool exists = false;
	int (* keyCompare)(const void *, const void *) = map->keyCompare;
	unsigned int (* keyHash)(const void *) = map->keyHash;

	/* Hash key to get slot index. */
	unsigned int hash = (
			(keyHash) ?
			keyHash(key)
			: FoxHashMem(key, map->keySize)
	);
	unsigned int tmpSlotIdx = hash & map->slotIdxMask;

	FoxArray * slot = FoxArrayIndex(&map->slots, tmpSlotIdx);
	size_t numSlotEntries = FoxArraySize(slot);
	for (unsigned int idx = 0; idx < numSlotEntries; idx++) {
		SlotEntry * slotEntry = FoxArrayIndex(slot, idx);

		/* Compare keys. */
		int diff = (
				(keyCompare) ?
				keyCompare(key, slotEntry->key)
				: memcmp(key, slotEntry->key, map->keySize)
		);
		if ((exists = (diff == 0))) {
			if (slotEntryIdx) *slotEntryIdx = idx;
			if (itemIdx) *itemIdx = slotEntry->itemIdx;
			break;
		}
	}

	if (slotIdx) *slotIdx = tmpSlotIdx;

	return exists;
}



/* ----- PUBLIC FUNCTIONS ----- */

FoxMap * FoxMapNew(
		size_t keySize,
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh,
		unsigned int (* keyHash)(const void * key),
		int (* keyCompare)(const void * keyA, const void * keyB),
		void (* keyCopy)(void *, const void *),
		void (* keyDeinit)(void *)
) {
	FoxMap * map = calloc(1, sizeof(FoxMap));
	FoxMapInit(
			map,
			keySize,
			elemSize,
			initSlots,
			growRate,
			lfThresh,
			keyHash,
			keyCompare,
			keyCopy,
			keyDeinit
	);

	return map;
}

void FoxMapFree(FoxMap * map) {
	FoxMapDeinit(map);
	free(map);

	return;
}

void FoxMapInit(
		FoxMap * map,
		size_t keySize,
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh,
		unsigned int (* keyHash)(const void * key),
		int (* keyCompare)(const void * keyA, const void * keyB),
		void (* keyCopy)(void *, const void *),
		void (* keyDeinit)(void *)
) {
	assert(map);
	assert(keySize > 0);
	assert(elemSize > 0);
	assert(initSlots > 1);
	assert(growRate > 1.0f);

	/* Calculate number of slots. */
	size_t numSlots = RoundUpPowTwo(initSlots);
	assert(RoundUpPowTwo((size_t)(numSlots * growRate)) > numSlots);

	/* Initialize scalar members. */
	map->keySize = keySize;
	map->elemSize = elemSize;
	map->growRate = growRate;
	map->lfThresh = lfThresh;
	map->slotIdxMask = numSlots - 1;

	/* Initialize key functions. */
	map->keyHash = keyHash;
	map->keyCompare = keyCompare;
	map->keyCopy = keyCopy;
	map->keyDeinit = keyDeinit;

	/* Initialize slots. */
	FoxArray * slots = &map->slots;
	FoxArrayInit(
			slots,
			sizeof(FoxArray),
			numSlots,
			FOXARRAY_DEF_GROWRATE
	);
	for (unsigned int idx = 0; idx < numSlots; idx++) {
		FoxArrayInit(
				FoxArrayInsert(slots, idx),
				SlotEntrySize(map),
				4,
				FOXARRAY_DEF_GROWRATE
		);
	}

	/* Initialize items. */
	FoxArrayInit(
			&map->items,
			ItemSize(map),
			FOXARRAY_DEF_INITCAP,
			FOXARRAY_DEF_GROWRATE
	);

	return;
}

void FoxMapDeinit(FoxMap * map) {
	assert(map);

	FoxArray * slots = &map->slots;
	size_t numSlots = FoxArraySize(slots);
	void (* keyDeinit)(void *) = map->keyDeinit;
	for (unsigned int slotIdx = 0; slotIdx < numSlots; slotIdx++) {
		FoxArray * slot = FoxArrayIndex(slots, slotIdx);
		if (keyDeinit) {
			size_t numEntries = FoxArraySize(slot);
			for (unsigned int entryIdx = 0; entryIdx < numEntries; entryIdx++) {
				SlotEntry * slotEntry = FoxArrayIndex(slot, entryIdx);
				keyDeinit(slotEntry->key);
			}
		}
		FoxArrayDeinit(slot);
	}
	FoxArrayDeinit(slots);
	FoxArrayDeinit(&map->items);
	*map = (FoxMap){0};

	return;
}

size_t FoxMapSize(FoxMap * map) {
	assert(map);

	return FoxArraySize(&map->items);
}

void * FoxMapIndex(
		FoxMap * map,
		const void * key
) {
	assert(map);
	assert(key);
	void * elem = NULL;

	unsigned int itemIdx;
	if (ItemLookup(map, key, NULL, NULL, &itemIdx)) {
		Item * item = FoxArrayIndex(&map->items, itemIdx);
		elem = item->elem;
	}

	return elem;
}

void * FoxMapInsert(
		FoxMap * map,
		const void * key
) {
	assert(map);
	assert(key);

	/* Expand map if necessary. */
	float lfThresh = map->lfThresh;
	if (lfThresh > 0.0f && LoadFactor(map, 1) >= lfThresh) {
		FoxMapExpand((FoxMap *)map);
	}

	/* Lookup slot. */
	unsigned int slotIdx;
	assert(!ItemLookup(map, key, &slotIdx, NULL, NULL));
	FoxArray * slot = FoxArrayIndex(&map->slots, slotIdx);

	/* Create slot entry. */
	unsigned int slotEntryIdx = FoxArraySize(slot);
	SlotEntry * slotEntry = FoxArrayInsert(slot, slotEntryIdx);
	
	/* Copy key. */
	void (* keyCopy)(void *, const void *) = map->keyCopy;
	if (keyCopy) {
		keyCopy(slotEntry->key, key);
	} else {
		memcpy(slotEntry->key, key, map->keySize);
	}

	/* Create item. */
	FoxArray * items = &map->items;
	unsigned int itemIdx = FoxArraySize(items);
	Item * item = FoxArrayInsert(items, itemIdx);
	item->slotIdx = slotIdx;
	item->slotEntryIdx = slotEntryIdx;

	/* Update slot entry. */
	slotEntry->itemIdx = itemIdx;

	/* Initialize target element. */
	memset(item->elem, 0, map->elemSize);

	return item->elem;
}

void FoxMapRemove(
		FoxMap * map,
		const void * key,
		void * elem
) {
	assert(map);
	assert(key);

	unsigned int slotIdx, slotEntryIdx, itemIdx;
	assert(ItemLookup(map, key, &slotIdx, &slotEntryIdx, &itemIdx));
	FoxArray * slots = &map->slots;
	FoxArray * items = &map->items;
	FoxArray * slot = FoxArrayIndex(slots, slotIdx);

	/* Get item and slot entry to remove. */
	SlotEntry * slotEntry = FoxArrayIndex(slot, slotEntryIdx);
	Item * item = FoxArrayIndex(items, itemIdx);

	/* Copy target element if requested. */
	if (elem) memcpy(elem, item->elem, map->elemSize);

	/* Remove item. */
	unsigned int lastItemIdx = FoxArraySize(items) - 1;
	if (itemIdx < lastItemIdx) {
		/* Get last item and slot entry. */
		Item * lastItem = FoxArrayIndex(items, lastItemIdx);
		FoxArray * lastSlot = FoxArrayIndex(slots, lastItem->slotIdx);
		SlotEntry * lastSlotEntry = FoxArrayIndex(
				lastSlot,
				lastItem->slotEntryIdx
		);

		/* Move last item. */
		memcpy(item, lastItem, ItemSize(map));

		/* Update last slot entry. */
		lastSlotEntry->itemIdx = itemIdx;
	}
	FoxArrayRemove(items, lastItemIdx, NULL);

	/* Remove slot entry. */
	void (* keyDeinit)(void *) = map->keyDeinit;
	if (keyDeinit) keyDeinit(slotEntry->key);
	unsigned int lastSlotEntryIdx = FoxArraySize(slot) - 1;
	if (slotEntryIdx < lastSlotEntryIdx) {
		/* Get last slot entry and item. */
		SlotEntry * lastSlotEntry = FoxArrayIndex(slot, lastSlotEntryIdx);
		Item * lastItem = FoxArrayIndex(items, lastSlotEntry->itemIdx);

		/* Move last slot entry. */
		memcpy(slotEntry, lastSlotEntry, SlotEntrySize(map));

		/* Update last item. */
		lastItem->slotEntryIdx = slotEntryIdx;
	}
	FoxArrayRemove(slot, lastSlotEntryIdx, NULL);

	return;
}

float FoxMapLoadFactor(FoxMap * map) {
	return LoadFactor(map, 0);
}

void FoxMapExpand(FoxMap * map) {
	assert(map);

	FoxArray * slots = &map->slots;
	size_t numSlots = FoxArraySize(slots);
	FoxArray * items = &map->items;
	size_t numItems = FoxArraySize(items);
	size_t elemSize = map->elemSize;

	/* Initialize new map. */
	FoxMap new = (FoxMap){0};
	FoxMapInit(
			&new,
			map->keySize,
			elemSize,
			(size_t)(numSlots * map->growRate),
			map->growRate,
			map->lfThresh,
			map->keyHash,
			map->keyCompare,
			map->keyCopy,
			map->keyDeinit
	);

	/* Copy key-element pairs to new map. */
	for (unsigned int idx = 0; idx < numItems; idx++) {
		Item * item = FoxArrayIndex(items, idx);
		FoxArray * slot = FoxArrayIndex(slots, item->slotIdx);
		SlotEntry * slotEntry = FoxArrayIndex(slot, item->slotEntryIdx);
		
		memcpy(
				FoxMapInsert(&new, slotEntry->key),
				item->elem,
				elemSize
		);
	}

	/* De-initialize old map. */
	FoxMapDeinit(map);

	/* Set new map. */
	*map = new;

	return;
}

void FoxMapForEachPair(
		FoxMap * map,
		bool (* callback)(const void * key, void * elem, void * ctx),
		void * ctx
) {
	assert(map);
	assert(callback);

	FoxArray * slots = &map->slots;
	FoxArray * items = &map->items;
	size_t numItems = FoxArraySize(items);
	for (unsigned int idx = 0; idx < numItems; idx++) {
		Item * item = FoxArrayIndex(items, idx);
		FoxArray * slot = FoxArrayIndex(slots, item->slotIdx);
		SlotEntry * slotEntry = FoxArrayIndex(slot, item->slotEntryIdx);
		if (!callback(slotEntry->key, item->elem, ctx)) break;
	}

	return;
}

void FoxMapForEachElement(
		FoxMap * map,
		bool (* callback)(void * elem, void * ctx),
		void * ctx
) {
	assert(map);
	assert(callback);

	FoxArray * items = &map->items;
	size_t numItems = FoxArraySize(items);
	for (unsigned int idx = 0; idx < numItems; idx++) {
		Item * item = FoxArrayIndex(items, idx);
		if (!callback(item->elem, ctx)) break;
	}

	return;
}

void FoxMapForEachKey(
		FoxMap * map,
		bool (* callback)(const void * key, void * ctx),
		void * ctx
) {
	assert(map);
	assert(callback);

	FoxArray * slots = &map->slots;
	FoxArray * items = &map->items;
	size_t numItems = FoxArraySize(items);
	for (unsigned int idx = 0; idx < numItems; idx++) {
		Item * item = FoxArrayIndex(items, idx);
		FoxArray * slot = FoxArrayIndex(slots, item->slotIdx);
		SlotEntry * slotEntry = FoxArrayIndex(slot, item->slotEntryIdx);
		if (!callback(slotEntry->key, ctx)) break;
	}

	return;
}
