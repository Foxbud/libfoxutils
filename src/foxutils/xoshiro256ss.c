/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>
#include <stdlib.h>

#include "foxutils/math.h"
#include "foxutils/splitmix64.h"
#include "foxutils/xoshiro256ss.h"



/* ----- PUBLIC CONSTANTS ----- */

const uint64_t FOXXOSHIRO256SS_JUMPPOLY_2_128[4] = {
	0x180ec6d33cfd0aba,
	0xd5a61266f0c9392c,
	0xa9582618e03fc9aa,
	0x39abdc4529b1661c
};

const uint64_t FOXXOSHIRO256SS_JUMPPOLY_2_192[4] = {
	0x76e15d3efefdcbbf,
	0xc5004e441c522fb3,
	0x77710069854ee241,
	0x39109bb02acbe635
};



/* ----- PRIVATE GLOBALS ----- */

static FoxPRNGVTable vtable = {
	.seed = (void (*)(FoxPRNG *, uint64_t))FoxXoshiro256SSSeed,
	.next = (uint64_t (*)(FoxPRNG *))FoxXoshiro256SSNext
};



/* ----- PUBLIC FUNCTIONS ----- */

FoxXoshiro256SS * FoxXoshiro256SSNew(uint64_t seed) {
	FoxXoshiro256SS * prng = calloc(1, sizeof(FoxXoshiro256SS));
	FoxXoshiro256SSInit(prng, seed);

	return prng;
}

void FoxXoshiro256SSFree(FoxXoshiro256SS * prng) {
	FoxXoshiro256SSDeinit(prng);
	free(prng);

	return;
}

void FoxXoshiro256SSInit(
		FoxXoshiro256SS * prng,
		uint64_t seed
) {
	assert(prng);

	prng->super.vtable = &vtable;
	FoxXoshiro256SSSeed(prng, seed);

	return;
}

void FoxXoshiro256SSDeinit(FoxXoshiro256SS * prng) {
	assert(prng);

	*prng = (FoxXoshiro256SS){0};

	return;
}

void FoxXoshiro256SSSeed(
		FoxXoshiro256SS * prng,
		uint64_t seed
) {
	uint64_t seedState = seed;
	for (unsigned int idx = 0; idx < 4; idx++) {
		prng->state[idx] = FoxSplitMix64Primitive(&seedState);
	}

	return;
}

uint64_t FoxXoshiro256SSNext(FoxXoshiro256SS * prng) {
	return FoxXoshiro256SSPrimitive(prng->state);
}

void FoxXoshiro256SSJump(
		FoxXoshiro256SS * prng,
		const uint64_t jumpPoly[]
) {
	assert(prng);
	assert(jumpPoly);

	uint64_t tmpState[4] = {0};
	for (unsigned int polyIdx = 0; polyIdx < 4; polyIdx++) {
		for (unsigned int bit = 0; bit < 64; bit++) {
			if (jumpPoly[polyIdx] & (uint64_t)1 << bit) {
				tmpState[0] ^= prng->state[0];
				tmpState[1] ^= prng->state[1];
				tmpState[2] ^= prng->state[2];
				tmpState[3] ^= prng->state[3];
			}
			FoxXoshiro256SSPrimitive(prng->state);
		}
	}

	prng->state[0] = tmpState[0];
	prng->state[1] = tmpState[1];
	prng->state[2] = tmpState[2];
	prng->state[3] = tmpState[3];

	return;
}

uint64_t FoxXoshiro256SSPrimitive(uint64_t state[4]) {
	const uint64_t result = FoxRotL(state[1] * 5, 7) * 9;
	const uint64_t tmp = state[1] << 17;

	state[2] ^= state[0];
	state[3] ^= state[1];
	state[1] ^= state[2];
	state[0] ^= state[3];

	state[2] ^= tmp;
	state[3] = FoxRotL(state[3], 45);

	return result;
}
