/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Convenience macros for foxutils/array.h.
 */
#ifndef FOXUTILS_ARRAYMACS_H
#define FOXUTILS_ARRAYMACS_H

#include "foxutils/array.h"



/* ----- PUBLIC MACROS ----- */

#define FoxArrayMNew(T) \
	FoxArrayNew(sizeof(T), FOXARRAY_DEF_INITCAP, FOXARRAY_DEF_GROWRATE)

#define FoxArrayMNewExt(T, initCap) \
	FoxArrayNew(sizeof(T), (initCap), FOXARRAY_DEF_GROWRATE)

#define FoxArrayMNewAdv(T, initCap, growRate) \
	FoxArrayNew(sizeof(T), (initCap), (growRate))

#define FoxArrayMFree(T, array) \
		FoxArrayFree((array))

#define FoxArrayMInit(T, array) \
	FoxArrayInit((array), sizeof(T), FOXARRAY_DEF_INITCAP, FOXARRAY_DEF_GROWRATE)

#define FoxArrayMInitExt(T, array, initCap) \
	FoxArrayInit((array), sizeof(T), (initCap), FOXARRAY_DEF_GROWRATE)

#define FoxArrayMInitAdv(T, array, initCap, growRate) \
	FoxArrayInit((array), sizeof(T), (initCap), (growRate))

#define FoxArrayMDeinit(T, array) \
	FoxArrayDeinit((array))

#define FoxArrayMSize(T, array) \
	FoxArraySize((array))

#define FoxArrayMIndex(T, array, idx) \
	((T *)FoxArrayIndex((array), (idx)))

#define FoxArrayMPeek(T, array) \
	((T *)FoxArrayPeek((array)))

#define FoxArrayMInsert(T, array, idx) \
	((T *)FoxArrayInsert((array), (idx)))

#define FoxArrayMPush(T, array) \
	((T *)FoxArrayPush((array)))

#define FoxArrayMRemove(T, array, idx) \
	({ \
		T FoxArrayMRemove_elem; \
		FoxArrayRemove((array), (idx), &FoxArrayMRemove_elem); \
		FoxArrayMRemove_elem; \
	})

#define FoxArrayMPop(T, array) \
	({ \
		T FoxArrayMPop_elem; \
		FoxArrayRemove((array), &FoxArrayMPop_elem); \
		FoxArrayMPop_elem; \
	})



#endif /* FOXUTILS_ARRAYMACS_H */
