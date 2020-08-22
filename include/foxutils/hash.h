/**
 * @file
 *
 * @copyright Copyright 2020 Garrett Russell Fairburn
 * 
 * @copyright This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 *
 * @brief Non-cryptographically secure hashing functions.
 *
 * @warning None of the functions in this module are crytographically secure.
 */
#ifndef FOXUTILS_HASH_H
#define FOXUTILS_HASH_H

#include <stddef.h>
#include <stdint.h>



/* ----- PUBLIC FUNCTIONS ----- */

uint64_t FoxHashMem(
		const void * mem,
		size_t num
);

uint64_t FoxHashString(const char * str);

uint64_t FoxHashChar(char val);

uint64_t FoxHashSChar(signed char val);

uint64_t FoxHashUChar(unsigned char val);

uint64_t FoxHashShort(short val);

uint64_t FoxHashUShort(unsigned short val);

uint64_t FoxHashInt(int val);

uint64_t FoxHashUInt(unsigned int val);

uint64_t FoxHashLong(long val);

uint64_t FoxHashULong(unsigned long val);

uint64_t FoxHashLongLong(long long val);

uint64_t FoxHashULongLong(unsigned long long val);



#endif /* FOXUTILS_HASH_H */
