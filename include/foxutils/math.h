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

#define FoxClamp(val, min, max) \
	FoxMax(min, FoxMin(max, val))

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

uint64_t FoxRoundUpMersenne(uint64_t val);

uint64_t FoxRoundUpPow2(uint64_t val);


#endif /* FOXUTILS_MATH_H */
