/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief SplitMix64 pseudo-random number generator.
 *
 * This generator was designed by Sebastiano Vigna. See
 * http://prng.di.unimi.it/ for details.
 */
#ifndef FOXUTILS_SPLITMIX64_H
#define FOXUTILS_SPLITMIX64_H

#include "foxutils/rand.h"



/* ----- PUBLIC TYPES ----- */

typedef struct FoxSplitMix64 {
	FoxPRNG super;
	uint64_t state;
} FoxSplitMix64;



/* ----- PUBLIC FUNCTIONS ----- */

FoxSplitMix64 * FoxSplitMix64New(uint64_t seed);

void FoxSplitMix64Free(FoxSplitMix64 * prng);

void FoxSplitMix64Init(
		FoxSplitMix64 * prng,
		uint64_t seed
);

void FoxSplitMix64Deinit(FoxSplitMix64 * prng);

void FoxSplitMix64Seed(
		FoxSplitMix64 * prng,
		uint64_t seed
);

uint32_t FoxSplitMix64Next32(FoxSplitMix64 * prng);

uint64_t FoxSplitMix64Next64(FoxSplitMix64 * prng);

uint64_t FoxSplitMix64Primitive(uint64_t * state);



#endif /* FOXUTILS_SPLITMIX64_H */
