#include <main.h>

long	max(long a, long b)
{
	return (a * (a >= b) + b * (a < b));
}

