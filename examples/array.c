#include <stdio.h>

#include "foxutils/array.h"



int main(void) {
	FoxArray * primes = FoxArrayNew(sizeof(int), 4, 1.5f);
	
	*(int *)FoxArrayPush(primes) = 0;
	*(int *)FoxArrayPush(primes) = 1;
	*(int *)FoxArrayPush(primes) = 3;
	*(int *)FoxArrayPush(primes) = 5;
	*(int *)FoxArrayPush(primes) = 7;
	*(int *)FoxArrayPush(primes) = 11;

	*(int *)FoxArrayIndex(primes, 0) = 2;
	FoxArrayRemove(primes, 1, NULL);

	size_t numPrimes = FoxArraySize(primes);
	printf("First %zu prime(s):", numPrimes);
	for (unsigned int idx = 0; idx < numPrimes; idx++) {
		printf(" %i", *(int *)FoxArrayIndex(primes, idx));
	}
	printf(".\n");
	
	FoxArrayFree(primes);
	primes = NULL;

	return 0;
}
