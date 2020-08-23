/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Xorshift64 pseudo-random number generator.
 *
 * @warning This generator is NOT suitable for cryptographic use.
 *
 * This generator was designed by George Marsaglia with parameters recommended
 * by Sebastiano Vigna. See http://vigna.di.unimi.it/ftp/papers/xorshift.pdf
 * for details.
 */
#ifndef FOXUTILS_XORSHIFT64_H
#define FOXUTILS_XORSHIFT64_H

#include "foxutils/rand.h"



/* ----- PUBLIC TYPES ----- */

typedef struct FoxXorshift64 {
	FoxPRNG super;
	uint64_t state;
} FoxXorshift64;



/* ----- PUBLIC FUNCTIONS ----- */

FoxXorshift64 * FoxXorshift64New(uint64_t seed);

void FoxXorshift64Free(FoxXorshift64 * prng);

void FoxXorshift64Init(
		FoxXorshift64 * prng,
		uint64_t seed
);

void FoxXorshift64Deinit(FoxXorshift64 * prng);

void FoxXorshift64Seed(
		FoxXorshift64 * prng,
		uint64_t seed
);

uint64_t FoxXorshift64Next(FoxXorshift64 * prng);

uint64_t FoxXorshift64Primitive(uint64_t * state);



#endif /* FOXUTILS_XORSHIFT64_H */
