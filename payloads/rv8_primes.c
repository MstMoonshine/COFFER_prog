#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <payload.h>

#define test(p) (primes[p >> 6] & 1 << (p & 0x3f))
#define set(p) (primes[p >> 6] |= 1 << (p & 0x3f))
#define is_prime(p) !test(p)

int main()
{
	unsigned long cycle3 = read_csr(cycle);
	int limit = 33333333;
	size_t primes_size = ((limit >> 6) + 1) * sizeof(uint64_t);
	uint64_t *primes = (uint64_t*)malloc(primes_size);
	int64_t p = 2, sqrt_limit = (int64_t)sqrt(limit);
	while (p <= limit >> 1) {
		for (int64_t n = 2 * p; n <= limit; n += p) if (!test(n)) set(n);
		while (++p <= sqrt_limit && test(p));
	}
	for (int i = limit; i > 0; i--) {
		if (is_prime(i)) {
			// printf("%d\r\n", i);
			return 0;
		}
	}
	unsigned long cycle4 = read_csr(cycle);
	printf("%ld    %ld    ", cycle3, cycle4);
};
