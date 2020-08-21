/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Utilities for working with pseudo-random number generators.
 */
#ifndef FOXUTILS_RAND_H
#define FOXUTILS_RAND_H

#include <stdbool.h>
#include <stdint.h>



/* ----- PUBLIC TYPES ----- */

struct FoxPRNG;

typedef struct FoxPRNGVTable {
	void (* seed)(struct FoxPRNG * prng, uint64_t seed);
	uint32_t (* next32)(struct FoxPRNG * prng);
	uint64_t (* next64)(struct FoxPRNG * prng);
} FoxPRNGVTable;

typedef struct FoxPRNG {
	FoxPRNGVTable * vtable;
} FoxPRNG;



/* ----- PUBLIC FUNCTIONS ----- */

void FoxRandSeed(
		FoxPRNG * prng,
		uint64_t seed
);

uint64_t FoxRandUInt(FoxPRNG * prng);

uint64_t FoxRandUIntRange(
		FoxPRNG * prng,
		uint64_t min,
		uint64_t max
);

int64_t FoxRandInt(FoxPRNG * rand);

int64_t FoxRandIntRange(
		FoxPRNG * prng,
		int64_t min,
		int64_t max
);

bool FoxRandBool(FoxPRNG * prng);

float FoxRandFloat(FoxPRNG * prng);

float FoxRandFloatRange(
		FoxPRNG * prng,
		float min,
		float max
);

double FoxRandDouble(FoxPRNG * prng);

double FoxRandDoubleRange(
		FoxPRNG * prng,
		double min,
		double max
);



#endif /* FOXUTILS_RAND_H */
