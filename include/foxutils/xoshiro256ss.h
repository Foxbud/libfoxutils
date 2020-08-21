/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Xoshiro256** pseudo-random number generator.
 *
 * This generator was designed by David Blackman and Sebastiano Vigna. See
 * http://prng.di.unimi.it/ for details.
 */
#ifndef FOXUTILS_XOSHIRO256SS_H
#define FOXUTILS_XOSHIRO256SS_H

#include "foxutils/rand.h"



/* ----- PUBLIC TYPES ----- */

typedef struct FoxXoshiro256SS {
	FoxPRNG super;
	uint64_t state[4];
} FoxXoshiro256SS;



/* ----- PUBLIC CONSTANTS ----- */

extern const uint64_t FOXXOSHIRO256SS_JUMPPOLY_2_128[4];

extern const uint64_t FOXXOSHIRO256SS_JUMPPOLY_2_192[4];



/* ----- PUBLIC FUNCTIONS ----- */

FoxXoshiro256SS * FoxXoshiro256SSNew(uint64_t seed);

void FoxXoshiro256SSFree(FoxXoshiro256SS * prng);

void FoxXoshiro256SSInit(
		FoxXoshiro256SS * prng,
		uint64_t seed
);

void FoxXoshiro256SSDeinit(FoxXoshiro256SS * prng);

void FoxXoshiro256SSSeed(
		FoxXoshiro256SS * prng,
		uint64_t seed
);

uint32_t FoxXoshiro256SSNext32(FoxXoshiro256SS * prng);

uint64_t FoxXoshiro256SSNext64(FoxXoshiro256SS * prng);

void FoxXoshiro256SSJump(
		FoxXoshiro256SS * prng,
		const uint64_t jumpPoly[4]
);

uint64_t FoxXoshiro256SSPrimitive(uint64_t state[4]);



#endif /* FOXUTILS_XOSHIRO256SS_H */
