#include <main.h>

int ft_log2(int n)
{
	int result;

	if (n <= 0)
		return (-1);
	result = 0;
	while (n > 1)
	{
		n /= 2;
		result++;
	}
	return (result);
}
