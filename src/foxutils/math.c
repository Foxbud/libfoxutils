/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <stddef.h>

#include "foxutils/math.h"



/* ----- PRIVATE FUNCTIONS ----- */

static inline uint64_t RoundUpMersenne(uint64_t val) {
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	val |= val >> 32;

	return val;
}



/* ----- PUBLIC FUNCTIONS ----- */

uint64_t FoxRoundUpMersenne(uint64_t val) {
	return RoundUpMersenne(val);
}

uint64_t FoxRoundUpPow2(uint64_t val) {
	return RoundUpMersenne(val + (val == 0) - 1) + 1;
}
