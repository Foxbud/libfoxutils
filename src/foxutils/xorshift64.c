/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>
#include <stdlib.h>

#include "foxutils/xorshift64.h"



/* ----- PRIVATE GLOBALS ----- */

static FoxPRNGVTable vtable = {
	.seed = (void (*)(FoxPRNG *, uint64_t))FoxXorshift64Seed,
	.next = (uint64_t (*)(FoxPRNG *))FoxXorshift64Next
};



/* ----- PUBLIC FUNCTIONS ----- */

FoxXorshift64 * FoxXorshift64New(uint64_t seed) {
	FoxXorshift64 * prng = calloc(1, sizeof(FoxXorshift64));
	FoxXorshift64Init(prng, seed);

	return prng;
}

void FoxXorshift64Free(FoxXorshift64 * prng) {
	FoxXorshift64Deinit(prng);
	free(prng);

	return;
}

void FoxXorshift64Init(
		FoxXorshift64 * prng,
		uint64_t seed
) {
	assert(prng);

	prng->super.vtable = &vtable;
	FoxXorshift64Seed(prng, seed);

	return;
}

void FoxXorshift64Deinit(FoxXorshift64 * prng) {
	assert(prng);

	*prng = (FoxXorshift64){0};

	return;
}

void FoxXorshift64Seed(
		FoxXorshift64 * prng,
		uint64_t seed
) {
	prng->state = seed + (seed == 0);

	return;
}

uint64_t FoxXorshift64Next(FoxXorshift64 * prng) {
	return FoxXorshift64Primitive(&prng->state);
}

uint64_t FoxXorshift64Primitive(uint64_t * state) {
	uint64_t tmpState = *state;

	tmpState ^= tmpState << 12;
	tmpState ^= tmpState >> 25;
	tmpState ^= tmpState << 27;

	return *state = tmpState;
}
