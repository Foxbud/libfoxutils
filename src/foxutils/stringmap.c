/*
 * Copyright 2020 Garrett Russell Fairburn
 * 
 * This file is part of the libfoxutils C library which is released
 * under Apache 2.0. See file LICENSE for full license details.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "foxutils/hash.h"
#include "foxutils/stringmap.h"



/* ----- PRIVATE FUNCTIONS ----- */

static unsigned int StringKeyHash(const char ** key) {
	return FoxHashString(*key);
}

static int StringKeyCompare(
		const char ** keyA,
		const char ** keyB
) {
	return strcmp(*keyA, *keyB);
}

static void StringKeyCopy(
		char ** copy,
		const char ** key
) {
	const char * tmpKey = *key;
	char * tmpCopy = malloc(strlen(tmpKey) + 1);
	assert(tmpCopy);
	*copy = strcpy(tmpCopy, tmpKey);

	return;
}

static void StringKeyDeinit(char ** key) {
	free(*key);

	return;
}



/* ----- PUBLIC FUNCTIONS ----- */

FoxMap * FoxStringMapNew(
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh
) {
	return FoxMapNew(
			sizeof(const char *),
			elemSize,
			initSlots,
			growRate,
			lfThresh,
			(unsigned int (*)(const void *))&StringKeyHash,
			(int (*)(const void *, const void *))&StringKeyCompare,
			(void (*)(void *, const void *))&StringKeyCopy,
			(void (*)(void *))&StringKeyDeinit
	);
}

void FoxStringMapInit(
		FoxMap * map,
		size_t elemSize,
		size_t initSlots,
		float growRate,
		float lfThresh
) {
	FoxMapInit(
			map,
			sizeof(const char *),
			elemSize,
			initSlots,
			growRate,
			lfThresh,
			(unsigned int (*)(const void *))&StringKeyHash,
			(int (*)(const void *, const void *))&StringKeyCompare,
			(void (*)(void *, const void *))&StringKeyCopy,
			(void (*)(void *))&StringKeyDeinit
	);

	return;
}
