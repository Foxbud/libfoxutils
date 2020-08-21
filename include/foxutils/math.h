/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Miscellaneous math functions and macros.
 */
#ifndef FOXUTILS_MATH_H
#define FOXUTILS_MATH_H

#include <stdint.h>



/* ----- PUBLIC MACROS ----- */

#define FoxMin(a, b) \
	({ \
		typeof(a) FoxMin_a = (a); \
		typeof(b) FoxMin_b = (b); \
		(FoxMin_a < FoxMin_b) ? FoxMin_a : FoxMin_b; \
	})

#define FoxMax(a, b) \
	({ \
		typeof(a) FoxMax_a = (a); \
		typeof(b) FoxMax_b = (b); \
		(FoxMax_a > FoxMax_b) ? FoxMax_a : FoxMax_b; \
	})

#define FoxRotR(val, num) \
	({ \
		typeof(val) FoxRotR_val = (val); \
		typeof(num) FoxRotR_num = (num); \
		(FoxRotR_val >> FoxRotR_num) \
				| (FoxRotR_val << (sizeof(FoxRotR_val) * 8 - FoxRotR_num)); \
	})

#define FoxRotL(val, num) \
	({ \
		typeof(val) FoxRotL_val = (val); \
		typeof(num) FoxRotL_num = (num); \
		(FoxRotL_val << FoxRotL_num) \
				| (FoxRotL_val >> (sizeof(FoxRotL_val) * 8 - FoxRotL_num)); \
	})



/* ----- PUBLIC FUNCTIONS ----- */

unsigned int FoxRoundUpMersenneUInt(unsigned int val);

unsigned long FoxRoundUpMersenneULong(unsigned long val);

unsigned long long FoxRoundUpMersenneULongLong(unsigned long long val);

uint32_t FoxRoundUpMersenneUInt32(uint32_t val);

uint64_t FoxRoundUpMersenneUInt64(uint64_t val);

unsigned int FoxRoundUpPow2UInt(unsigned int val);

unsigned long FoxRoundUpPow2ULong(unsigned long val);

unsigned long long FoxRoundUpPow2ULongLong(unsigned long long val);

uint32_t FoxRoundUpPow2UInt32(uint32_t val);

uint64_t FoxRoundUpPow2UInt64(uint64_t val);


#endif /* FOXUTILS_MATH_H */
