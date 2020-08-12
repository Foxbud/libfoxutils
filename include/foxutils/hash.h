/**
 * @file
 *
 * @brief This module provides hash functions suitable for hash tables.
 *
 * @warning None of the functions in this module are crytographically secure.
 */
#ifndef FOXUTILS_HASH_H
#define FOXUTILS_HASH_H

#include <stddef.h>
#include <stdint.h>



/* ----- PUBLIC FUNCTIONS ----- */

uint32_t FoxHashMem(
		const void * mem,
		size_t num
);

uint32_t FoxHashString(const char * str);

uint32_t FoxHashChar(char val);

uint32_t FoxHashSChar(signed char val);

uint32_t FoxHashUChar(unsigned char val);

uint32_t FoxHashShort(short val);

uint32_t FoxHashUShort(unsigned short val);

uint32_t FoxHashInt(int val);

uint32_t FoxHashUInt(unsigned int val);

uint32_t FoxHashLong(long val);

uint32_t FoxHashULong(unsigned long val);

uint32_t FoxHashLongLong(long long val);

uint32_t FoxHashULongLong(unsigned long long val);



#endif /* FOXUTILS_HASH_H */
