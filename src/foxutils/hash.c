#include <assert.h>
#include "foxutils/hash.h"
#include "xorshift.h"



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

static inline uint32_t HashMem(
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
		XS64Round(hash.packed);
	}

	/* Mix unaligned trailing bytes. */
	if ((num & 0x7) != 0) {
		for (unsigned int idx = num & ~(size_t)0x7; idx < num; idx++) {
			hash.bytes[idx & 0x7] ^= view.bytes[idx];
		}
		XS64Round(hash.packed);
	}

	/* Finalize hash. */
	hash.packed *= XS64_STAR_COEF;
	XS64Round(hash.packed);

	/* Upper 32 bits are stronger. */
	return (uint32_t)(hash.packed >> 32);
}



/* ----- PUBLIC FUNCTIONS ----- */

uint32_t FoxHashMem(
		const void * mem,
		size_t num
) {
	assert(mem);

	return HashMem(mem, num);
}

uint32_t FoxHashString(const char * str) {
	assert(str);
	HashVal hash;
	hash.packed = 0;

	/* Mix bytes. */
	unsigned int charIdx = 0;
	char curChar;
	while ((curChar = str[charIdx]) != '\0') {
		hash.bytes[charIdx & 0x7] ^= (uint8_t)curChar;
		if ((++charIdx & 0x7) == 0) XS64Round(hash.packed);
	}
	if ((charIdx & 0x7) != 0) XS64Round(hash.packed);

	/* Finalize hash. */
	hash.packed *= XS64_STAR_COEF;
	XS64Round(hash.packed);

	/* Upper 32 bits are stronger. */
	return (uint32_t)(hash.packed >> 32);
}

uint32_t FoxHashChar(char val) {
	return HashMem(&val, sizeof(char));
}

uint32_t FoxHashSChar(signed char val) {
	return HashMem(&val, sizeof(signed char));
}

uint32_t FoxHashUChar(unsigned char val) {
	return HashMem(&val, sizeof(unsigned char));
}

uint32_t FoxHashShort(short val) {
	return HashMem(&val, sizeof(short));
}

uint32_t FoxHashUShort(unsigned short val) {
	return HashMem(&val, sizeof(unsigned short));
}

uint32_t FoxHashInt(int val) {
	return HashMem(&val, sizeof(int));
}

uint32_t FoxHashUInt(unsigned int val) {
	return HashMem(&val, sizeof(unsigned int));
}

uint32_t FoxHashLong(long val) {
	return HashMem(&val, sizeof(long));
}

uint32_t FoxHashULong(unsigned long val) {
	return HashMem(&val, sizeof(unsigned long));
}

uint32_t FoxHashLongLong(long long val) {
	return HashMem(&val, sizeof(long long));
}

uint32_t FoxHashULongLong(unsigned long long val) {
	return HashMem(&val, sizeof(unsigned long long));
}
