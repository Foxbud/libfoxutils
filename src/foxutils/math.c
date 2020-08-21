/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <stddef.h>

#include "foxutils/math.h"



/* ----- PRIVATE MACROS ----- */

#define MRoundUpMersenne(val) \
	((typeof(val))RoundUpMersenne((uint64_t)(val), sizeof(val)))

#define RoundUpPow2(val) \
	({ \
		typeof(val) RoundUpPow2_result = (typeof(val))RoundUpMersenne( \
				(uint64_t)(val) - 1, \
				sizeof(val) \
		) + 1; \
		RoundUpPow2_result += (RoundUpPow2_result == 0); \
	})



/* ----- PRIVATE FUNCTIONS ----- */

static inline uint64_t RoundUpMersenne(
		uint64_t val,
		size_t num
) {
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	if (num > 1) {
		val |= val >> 8;
		if (num > 2) {
			val |= val >> 16;
			if (num > 4) {
				val |= val >> 32;
			}
		}
	}

	return val;
}



/* ----- PUBLIC FUNCTIONS ----- */

unsigned int FoxRoundUpMersenneUInt(unsigned int val) {
	return MRoundUpMersenne(val);
}

unsigned long FoxRoundUpMersenneULong(unsigned long val) {
	return MRoundUpMersenne(val);
}

unsigned long long FoxRoundUpMersenneULongLong(unsigned long long val) {
	return MRoundUpMersenne(val);
}

uint32_t FoxRoundUpMersenneUInt32(uint32_t val) {
	return MRoundUpMersenne(val);
}

uint64_t FoxRoundUpMersenneUInt64(uint64_t val) {
	return MRoundUpMersenne(val);
}

unsigned int FoxRoundUpPow2UInt(unsigned int val) {
	return RoundUpPow2(val);
}

unsigned long FoxRoundUpPow2ULong(unsigned long val) {
	return RoundUpPow2(val);
}

unsigned long long FoxRoundUpPow2ULongLong(unsigned long long val) {
	return RoundUpPow2(val);
}

uint32_t FoxRoundUpPow2UInt32(uint32_t val) {
	return RoundUpPow2(val);
}

uint64_t FoxRoundUpPow2UInt64(uint64_t val) {
	return RoundUpPow2(val);
}
