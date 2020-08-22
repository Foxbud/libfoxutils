/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>

#include "foxutils/hash.h"
#include "foxutils/splitmix64.h"
#include "foxutils/xorshift64.h"



/* ----- PRIVATE TYPES ----- */

typedef union MemView {
	const void * raw;
	const uint64_t * blocks;
	const uint8_t * bytes;
} MemView;

typedef union HashVal {
	uint64_t packed;
	uint8_t bytes[8];
} HashVal;



/* ----- PRIVATE FUNCTIONS ----- */

static inline uint64_t HashMem(
		const void * mem,
		size_t num
) {
	MemView view;
	view.raw = mem;
	HashVal hash;
	hash.packed = 0;

	/* Mix as many 64-bit blocks as possible. */
	size_t numBlocks = num / 8;
	for (unsigned int idx = 0; idx < numBlocks; idx++) {
		hash.packed ^= view.blocks[idx];
		FoxXorshift64Primitive(&hash.packed);
	}

	/* Mix unaligned trailing bytes. */
	if ((num & 0x7) != 0) {
		for (unsigned int idx = num & ~(size_t)0x7; idx < num; idx++) {
			hash.bytes[idx & 0x7] ^= view.bytes[idx];
		}
		FoxXorshift64Primitive(&hash.packed);
	}

	/* Finalize hash. */
	return FoxSplitMix64Primitive(&hash.packed);
}



/* ----- PUBLIC FUNCTIONS ----- */

uint64_t FoxHashMem(
		const void * mem,
		size_t num
) {
	assert(mem);

	return HashMem(mem, num);
}

uint64_t FoxHashString(const char * str) {
	assert(str);
	HashVal hash;
	hash.packed = 0;

	/* Mix bytes. */
	unsigned int charIdx = 0;
	char curChar;
	while ((curChar = str[charIdx]) != '\0') {
		hash.bytes[charIdx & 0x7] ^= (uint8_t)curChar;
		if ((++charIdx & 0x7) == 0) FoxXorshift64Primitive(&hash.packed);
	}
	if ((charIdx & 0x7) != 0) FoxXorshift64Primitive(&hash.packed);

	/* Finalize hash. */
	return FoxSplitMix64Primitive(&hash.packed);
}

uint64_t FoxHashChar(char val) {
	return HashMem(&val, sizeof(char));
}

uint64_t FoxHashSChar(signed char val) {
	return HashMem(&val, sizeof(signed char));
}

uint64_t FoxHashUChar(unsigned char val) {
	return HashMem(&val, sizeof(unsigned char));
}

uint64_t FoxHashShort(short val) {
	return HashMem(&val, sizeof(short));
}

uint64_t FoxHashUShort(unsigned short val) {
	return HashMem(&val, sizeof(unsigned short));
}

uint64_t FoxHashInt(int val) {
	return HashMem(&val, sizeof(int));
}

uint64_t FoxHashUInt(unsigned int val) {
	return HashMem(&val, sizeof(unsigned int));
}

uint64_t FoxHashLong(long val) {
	return HashMem(&val, sizeof(long));
}

uint64_t FoxHashULong(unsigned long val) {
	return HashMem(&val, sizeof(unsigned long));
}

uint64_t FoxHashLongLong(long long val) {
	return HashMem(&val, sizeof(long long));
}

uint64_t FoxHashULongLong(unsigned long long val) {
	return HashMem(&val, sizeof(unsigned long long));
}
