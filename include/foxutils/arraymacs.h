/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief This module abstracts foxutils/array.h.
 */
#ifndef FOXUTILS_ARRAYMACS_H
#define FOXUTILS_ARRAYMACS_H

#include "foxutils/array.h"



/* ----- PUBLIC MACROS ----- */

#define FoxArrayMNew(T) \
	FoxArrayNew(sizeof(T), 0, 0.0f)

#define FoxArrayMNewExt(T, initCap) \
	FoxArrayNew(sizeof(T), (initCap), 0.0f)

#define FoxArrayMNewAdv(T, initCap, growRate) \
	FoxArrayNew(sizeof(T), (initCap), (growRate))

#define FoxArrayMFree(T, array) \
	do { \
		FoxArrayFree((array)); \
		(array) = NULL; \
	} while (0)

#define FoxArrayMInit(T, array) \
	FoxArrayInit((array), sizeof(T), 0, 0.0f)

#define FoxArrayMInitExt(T, array, initCap) \
	FoxArrayInit((array), sizeof(T), (initCap), 0.0f)

#define FoxArrayMInitAdv(T, array, initCap, growRate) \
	FoxArrayInit((array), sizeof(T), (initCap), (growRate))

#define FoxArrayMDeinit(T, array) \
	FoxArrayDeinit((array))

#define FoxArrayMSize(T, array) \
	FoxArraySize((array))

#define FoxArrayMIndex(T, array, idx) \
	((T *)FoxArrayIndex((array), (idx)))

#define FoxArrayMInsert(T, array, idx) \
	((T *)FoxArrayInsert((array), (idx)))

#define FoxArrayMRemove(T, array, idx) \
	({ \
		T FoxArrayMRemove_elem; \
		FoxArrayRemove((array), (idx), &FoxArrayMRemove_elem); \
		FoxArrayMRemove_elem; \
	})

#define FoxArrayMPush(T, array) \
	((T *)FoxArrayInsert((array), FoxArraySize((array))))

#define FoxArrayMPeek(T, array) \
	((T *)FoxArrayIndex((array), FoxArraySize((array)) - 1))

#define FoxArrayMPop(T, array) \
	({ \
		T FoxArrayMPop_elem; \
		FoxArrayRemove((array), FoxArraySize((array)) - 1, &FoxArrayMPop_elem); \
		FoxArrayMPop_elem; \
	})



#endif /* FOXUTILS_ARRAYMACS_H */
