#include <math.h>

int __attribute__((const)) is_prime(long long n)
{
	if (n <= 1)
		return 0;
	else if (n <= 3)
		return 1;
	else if (!(n % 2) || !(n % 3))
		return 0;

	long long cap = sqrt(n) + 1;
	for (long long int i = 5; i <= cap; i += 6)
		if (!(n%i) || !(n%(i+2)))
			return 0;

	return 1;
}
