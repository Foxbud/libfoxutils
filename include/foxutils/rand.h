/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Non-cryptographically secure pseudo-random number generation.
 *
 * @warning None of the functions in this module are crytographically secure.
 *
 * Internally, this module uses an xoshiro256** generator, which is a fast,
 * strong, and parallel/distributed-computing friendly PRNG designed by
 * David Blackman and Sebastiano Vigna of the Università degli Studi di Milano.
 *
 * For details about this and similar generators, see http://prng.di.unimi.it/.
 */
#ifndef FOXUTILS_RAND_H
#define FOXUTILS_RAND_H

#include <stdbool.h>
#include <stdint.h>



/* ----- PUBLIC TYPES ----- */

typedef struct FoxRand {
	uint64_t state[4];
} FoxRand;



/* ----- PUBLIC CONSTANTS ----- */

extern const uint64_t FOXRAND_JUMPPOLY_2_128[];

extern const uint64_t FOXRAND_JUMPPOLY_2_192[];



/* ----- PUBLIC FUNCTIONS ----- */

FoxRand * FoxRandNew(uint64_t seed);

void FoxRandFree(FoxRand * rand);

void FoxRandInit(
		FoxRand * rand,
		uint64_t seed
);

void FoxRandDeinit(FoxRand * rand);

void FoxRandSeed(
		FoxRand * rand,
		uint64_t seed
);

void FoxRandJump(
		FoxRand * rand,
		const uint64_t * jumpPoly
);

uint64_t FoxRandUInt(FoxRand * rand);

uint64_t FoxRandUIntRange(
		FoxRand * rand,
		uint64_t min,
		uint64_t max
);

int64_t FoxRandInt(FoxRand * rand);

int64_t FoxRandIntRange(
		FoxRand * rand,
		int64_t min,
		int64_t max
);

bool FoxRandBool(FoxRand * rand);

float FoxRandFloat(FoxRand * rand);

double FoxRandDouble(FoxRand * rand);



#endif /* FOXUTILS_RAND_H */
