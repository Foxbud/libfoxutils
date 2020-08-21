/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>
#include <stdlib.h>

#include "foxutils/math.h"
#include "foxutils/rand.h"



/* ----- PUBLIC CONSTANTS ----- */

const uint64_t FOXRAND_JUMPPOLY_2_128[] = {
	0x180ec6d33cfd0aba,
	0xd5a61266f0c9392c,
	0xa9582618e03fc9aa,
	0x39abdc4529b1661c
};

const uint64_t FOXRAND_JUMPPOLY_2_192[] = {
	0x76e15d3efefdcbbf,
	0xc5004e441c522fb3,
	0x77710069854ee241,
	0x39109bb02acbe635
};



/* ----- PRIVATE FUNCTIONS ----- */

/**
 * This is the primary xoshiro256** PRNG as described by David Blackman
 * and Sebastiano Vigna at http://prng.di.unimi.it/xoshiro256starstar.c.
 */
static inline uint64_t PrimaryNext(uint64_t * state) {
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

/**
 * This is a secondary 64-bit PRNG called SplitMix64 used to seed the primary
 * PRNG. Sebastiano Vigna recommends using it as opposed to an xorshift-based
 * PRNG for seeding the xoshiro256** PRNG to avoid potential bias.
 */
static inline uint64_t SeedNext(uint64_t * state) {
	uint64_t result = (*state += 0x9e3779b97f4a7c15);
	result = (result ^ (result >> 30)) * 0xbf58476d1ce4e5b9;
	result = (result ^ (result >> 27)) * 0x94d049bb133111eb;

	return result ^ (result >> 31);
}

/**
 * Seed the primary PRNG's state.
 */
static inline void PrimarySeed(
		uint64_t * state,
		uint64_t seed
) {
	uint64_t seedState = seed;
	for (unsigned int idx = 0; idx < 4; idx++) {
		state[idx] = SeedNext(&seedState);
	}

	return;
}



/* ----- PUBLIC FUNCTIONS ----- */

FoxRand * FoxRandNew(uint64_t seed) {
	FoxRand * rand = calloc(1, sizeof(FoxRand));
	FoxRandInit(rand, seed);

	return rand;
}

void FoxRandFree(FoxRand * rand) {
	FoxRandDeinit(rand);
	free(rand);

	return;
}

void FoxRandInit(
		FoxRand * rand,
		uint64_t seed
) {
	assert(rand);

	PrimarySeed(rand->state, seed);

	return;
}

void FoxRandDeinit(FoxRand * rand) {
	assert(rand);

	*rand = (FoxRand){0};

	return;
}

void FoxRandSeed(
		FoxRand * rand,
		uint64_t seed
) {
	assert(rand);

	PrimarySeed(rand->state, seed);

	return;
}

void FoxRandJump(
		FoxRand * rand,
		const uint64_t * jumpPoly
) {
	assert(rand);
	assert(jumpPoly);

	uint64_t tmpState[4] = {0};
	for (unsigned int polyIdx = 0; polyIdx < 4; polyIdx++) {
		for (unsigned int bit = 0; bit < 64; bit++) {
			if (jumpPoly[polyIdx] & (uint64_t)1 << bit) {
				tmpState[0] ^= rand->state[0];
				tmpState[1] ^= rand->state[1];
				tmpState[2] ^= rand->state[2];
				tmpState[3] ^= rand->state[3];
			}
			PrimaryNext(rand->state);
		}
	}

	rand->state[0] = tmpState[0];
	rand->state[1] = tmpState[1];
	rand->state[2] = tmpState[2];
	rand->state[3] = tmpState[3];

	return;
}

uint64_t FoxRandUInt(FoxRand * rand) {
	assert(rand);

	return PrimaryNext(rand->state);
}

uint64_t FoxRandUIntRange(
		FoxRand * rand,
		uint64_t min,
		uint64_t max
) {
	assert(rand);
	assert(max > min);

	uint64_t range = max - min;
	uint64_t mask = FoxRoundUpMersenneUInt64(range - 1);
	uint64_t result;
	do {
		result = PrimaryNext(rand->state) & mask;
	} while (result >= range);

	return result + min;
}

int64_t FoxRandInt(FoxRand * rand) {
	assert(rand);

	return (int64_t)PrimaryNext(rand->state);
}

int64_t FoxRandIntRange(
		FoxRand * rand,
		int64_t min,
		int64_t max
) {
	assert(max > min);

	uint64_t result = FoxRandUIntRange(rand, 0, (uint64_t)(max - min));

	return (int64_t)(result + (uint64_t)min);
}

bool FoxRandBool(FoxRand * rand) {
	assert(rand);

	return (bool)(PrimaryNext(rand->state) >> 63);
}

float FoxRandFloat(FoxRand * rand) {
	assert(rand);

	return (PrimaryNext(rand->state) >> (64 - 24)) * 0x1.0p-24f;
}

double FoxRandDouble(FoxRand * rand) {
	assert(rand);

	return (PrimaryNext(rand->state) >> (64 - 53)) * 0x1.0p-53;
}
