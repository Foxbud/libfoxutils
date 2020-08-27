/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>

#include "foxutils/math.h"
#include "foxutils/rand.h"



/* ----- PUBLIC FUNCTIONS ----- */

void FoxRandSeed(
		FoxPRNG * prng,
		uint64_t seed
) {
	assert(prng);

	prng->vtable->seed(prng, seed);

	return;
}

uint64_t FoxRandUInt(FoxPRNG * prng) {
	assert(prng);

	return prng->vtable->next(prng);
}

uint64_t FoxRandUIntRange(
		FoxPRNG * prng,
		uint64_t min,
		uint64_t max
) {
	assert(prng);
	assert(max > min);

	uint64_t range = max - min;
	uint64_t mask = FoxRoundUpMersenne(range - 1);
	uint64_t result;
	uint64_t (* next)(FoxPRNG *) = prng->vtable->next;
	do {
		result = next(prng) & mask;
	} while (result >= range);

	return result + min;
}

int64_t FoxRandInt(FoxPRNG * prng) {
	assert(prng);

	return (int64_t)prng->vtable->next(prng);
}

int64_t FoxRandIntRange(
		FoxPRNG * prng,
		int64_t min,
		int64_t max
) {
	assert(max > min);

	uint64_t result = FoxRandUIntRange(prng, 0, (uint64_t)(max - min));

	return (int64_t)(result + (uint64_t)min);
}

bool FoxRandBool(FoxPRNG * prng) {
	assert(prng);

	return (bool)(prng->vtable->next(prng) >> 63);
}

float FoxRandFloat(FoxPRNG * prng) {
	assert(prng);

	return (prng->vtable->next(prng) >> (64 - 24)) * 0x1.0p-24f;
}

float FoxRandFloatRange(
		FoxPRNG * prng,
		float min,
		float max
) {
	assert(max > min);

	return FoxRandFloat(prng) * (max - min) + min;
}

double FoxRandDouble(FoxPRNG * prng) {
	assert(prng);

	return (prng->vtable->next(prng) >> (64 - 53)) * 0x1.0p-53;
}

double FoxRandDoubleRange(
		FoxPRNG * prng,
		double min,
		double max
) {
	assert(max > min);

	return FoxRandDouble(prng) * (max - min) + min;
}
