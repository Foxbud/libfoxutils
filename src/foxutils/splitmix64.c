/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>
#include <stdlib.h>

#include "foxutils/splitmix64.h"



/* ----- PRIVATE GLOBALS ----- */

static FoxPRNGVTable vtable = {
	.seed = (void (*)(FoxPRNG *, uint64_t))FoxSplitMix64Seed,
	.next = (uint64_t (*)(FoxPRNG *))FoxSplitMix64Next
};



/* ----- PUBLIC FUNCTIONS ----- */

FoxSplitMix64 * FoxSplitMix64New(uint64_t seed) {
	FoxSplitMix64 * prng = calloc(1, sizeof(FoxSplitMix64));
	FoxSplitMix64Init(prng, seed);

	return prng;
}

void FoxSplitMix64Free(FoxSplitMix64 * prng) {
	FoxSplitMix64Deinit(prng);
	free(prng);

	return;
}

void FoxSplitMix64Init(
		FoxSplitMix64 * prng,
		uint64_t seed
) {
	assert(prng);

	prng->super.vtable = &vtable;
	FoxSplitMix64Seed(prng, seed);

	return;
}

void FoxSplitMix64Deinit(FoxSplitMix64 * prng) {
	assert(prng);

	*prng = (FoxSplitMix64){0};

	return;
}

void FoxSplitMix64Seed(
		FoxSplitMix64 * prng,
		uint64_t seed
) {
	prng->state = seed;

	return;
}

uint64_t FoxSplitMix64Next(FoxSplitMix64 * prng) {
	return FoxSplitMix64Primitive(&prng->state);
}

uint64_t FoxSplitMix64Primitive(uint64_t * state) {
	uint64_t result = (*state += 0x9e3779b97f4a7c15);
	result = (result ^ (result >> 30)) * 0xbf58476d1ce4e5b9;
	result = (result ^ (result >> 27)) * 0x94d049bb133111eb;

	return result ^ (result >> 31);
}
