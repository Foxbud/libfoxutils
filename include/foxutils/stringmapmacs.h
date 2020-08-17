/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Convenience, function-like macros for foxutils/stringmap.h.
 */
#ifndef FOXUTILS_STRINGMAPMACS_H
#define FOXUTILS_STRINGMAPMACS_H

#include "foxutils/mapmacs.h"
#include "foxutils/stringmap.h"



/* ----- PUBLIC MACROS ----- */

#define FoxStringMapMNew(E) \
	FoxStringMapNew( \
			sizeof(E), \
			FOXMAP_DEF_INITSLOTS, \
			FOXMAP_DEF_GROWRATE, \
			FOXMAP_DEF_LFTHRESH \
	)

#define FoxStringMapMNewExt(E, initSlots) \
	FoxStringMapNew( \
			sizeof(E), \
			(initSlots), \
			FOXMAP_DEF_GROWRATE, \
			FOXMAP_DEF_LFTHRESH \
	)

#define FoxStringMapMNewAdv(E, initSlots, growRate, lfThresh) \
	FoxStringMapNew( \
			sizeof(E), \
			(initSlots), \
			(growRate), \
			(lfThresh) \
	)

#define FoxStringMapMInit(E, map) \
	FoxStringMapInit( \
			(map), \
			sizeof(E), \
			FOXMAP_DEF_INITSLOTS, \
			FOXMAP_DEF_GROWRATE, \
			FOXMAP_DEF_LFTHRESH \
	)

#define FoxStringMapMInitExt(E, map, initSlots) \
	FoxStringMapInit( \
			(map), \
			sizeof(E), \
			(initSlots), \
			FOXMAP_DEF_GROWRATE, \
			FOXMAP_DEF_LFTHRESH \
	)

#define FoxStringMapMInitAdv(E, map, initSlots, growRate, lfThresh) \
	FoxStringMapInit( \
			(map), \
			sizeof(E), \
			(initSlots), \
			(growRate), \
			(lfThresh) \
	)



#endif /* FOXUTILS_STRINGMAPMACS_H */
