/**
 * @file
 *
 * @brief This module abstracts foxutils/map.h.
 */
#ifndef FOXUTILS_MAPMACS_H
#define FOXUTILS_MAPMACS_H

#include "foxutils/map.h"



/* ----- PUBLIC MACROS ----- */

#define FoxMapMNew( \
		K, \
		E \
) \
	FoxMapNew( \
			sizeof(K), \
			sizeof(E), \
			0, \
			0.0, \
			0.0, \
			NULL, \
			NULL, \
			NULL, \
			NULL \
	)

#define FoxMapMNewExt( \
		K, \
		E, \
		initSlots, \
		keyHash, \
		keyCompare \
) \
	FoxMapNew( \
			sizeof(K), \
			sizeof(E), \
			(initSlots), \
			0.0, \
			0.0, \
			(unsigned int (*)(const void *))(keyHash), \
			(int (*)(const void *, const void *))(keyCompare), \
			NULL, \
			NULL \
	)

#define FoxMapMNewAdv( \
		K, \
		E, \
		initSlots, \
		growRate, \
		lfThresh, \
		keyHash, \
		keyCompare, \
		keyCopy, \
		keyDeinit \
) \
	FoxMapNew( \
			sizeof(K), \
			sizeof(E), \
			(initSlots), \
			(growRate), \
			(lfThresh), \
			(unsigned int (*)(const void *))(keyHash), \
			(int (*)(const void *, const void *))(keyCompare), \
			(void (*)(void *, const void *))(keyCopy), \
			(void (*)(void *))(keyDeinit) \
	)

#define FoxMapMFree(K, E, map) \
	do { \
		FoxMapFree((map)); \
		(map) = NULL; \
	} while (0)

#define FoxMapMInit( \
		K, \
		E, \
		map \
) \
	FoxMapInit( \
			(map), \
			sizeof(K), \
			sizeof(E), \
			0, \
			0.0, \
			0.0, \
			NULL, \
			NULL, \
			NULL, \
			NULL \
	)

#define FoxMapMInitExt( \
		K, \
		E, \
		map, \
		initSlots, \
		keyHash, \
		keyCompare \
) \
	FoxMapInit( \
			(map), \
			sizeof(K), \
			sizeof(E), \
			(initSlots), \
			0.0, \
			0.0, \
			(unsigned int (*)(const void *))(keyHash), \
			(int (*)(const void *, const void *))(keyCompare), \
			NULL, \
			NULL \
	)

#define FoxMapMInitAdv( \
		K, \
		E, \
		map, \
		initSlots, \
		growRate, \
		lfThresh, \
		keyHash, \
		keyCompare, \
		keyCopy, \
		keyDeinit \
) \
	FoxMapInit( \
			(map), \
			sizeof(K), \
			sizeof(E), \
			(initSlots), \
			(growRate), \
			(lfThresh), \
			(unsigned int (*)(const void *))(keyHash), \
			(int (*)(const void *, const void *))(keyCompare), \
			(void (*)(void *, const void *))(keyCopy), \
			(void (*)(void *))(keyDeinit) \
	)

#define FoxMapMDeinit(K, E, map) \
	FoxMapDeinit((map))

#define FoxMapMSize(K, E, map) \
	FoxMapSize((map))

#define FoxMapMIndex(K, E, map, key) \
	({ \
		K FoxMapMIndex_key = (key); \
		(E *)FoxMapIndex((map), &FoxMapMIndex_key); \
	})

#define FoxMapMInsert(K, E, map, key) \
	({ \
		K FoxMapMInsert_key = (key); \
		((E *)FoxMapInsert((map), &FoxMapMInsert_key)); \
	})

#define FoxMapMRemove(K, E, map, key) \
	({ \
		K FoxMapMRemove_key = (key); \
		E FoxMapMRemove_elem; \
		FoxMapRemove((map), &FoxMapMRemove_key, &FoxMapMRemove_elem); \
		FoxMapMRemove_elem; \
	})

#define FoxMapMLoadFactor(K, E, map) \
	FoxMapLoadFactor((map))

#define FoxMapMExpand(K, E, map) \
	FoxMapExpand((map))

#define FoxMapMForEachPair(K, E, map, callback, ctx) \
	FoxMapForEachPair( \
			(map), \
			(bool (*)(const void *, void *, void *))(callback), \
			(ctx) \
	)

#define FoxMapMForEachElement(K, E, map, callback, ctx) \
	FoxMapForEachElement( \
			(map), \
			(bool (*)(void *, void *))(callback), \
			(ctx) \
	)

#define FoxMapMForEachKey(K, E, map, callback, ctx) \
	FoxMapForEachKey( \
			(map), \
			(bool (*)(const void *, void *))(callback), \
			(ctx) \
	)



#endif /* FOXUTILS_MAPMACS_H */
