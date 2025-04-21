#include <main.h>

int validate_input(char *str)
{
	int subshell;

	subshell = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			str += skip(str, 1, *str, 0);
		if (!*str)
			return (0);
		if (*str == '(' || *str == ')')
			subshell += 1 - 2 * (*str == ')');
		str++;
	}
	return (!subshell);
}
