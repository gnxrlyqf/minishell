#include <main.h>

char	*max_str(char *a, char *b)
{
	if (a > b)
		return (a);
	return (b);
}

int skip(char *str, int i, char c, int rev)
{
	int subshell;
	int stop;

	stop = ft_strlen(str) * !rev - rev;
	if (c == ')' || c == '(')
	{
		subshell = 1 - 2 * (c == ')');
		while (i != stop && subshell)
		{
			subshell += (str[i] == ')' || str[i] == '(') - 2 * (str[i] == ')');
			i += 1 - 2 * rev;
		}
		return (i);
	}
	while (i != stop && str[i] != c)
		i += 1 - 2 * rev;
	return (i);
}

int wc(char *str, char c)
{
	int i;
	int count;

	count = i = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		count++;
		while (str[i] && str[i] != c)
		{
			if (ft_strchr("\"'(", str[i]))
				i = skip(str, i + 1, str[i], 0);
			i++;
		}
		while (str[i] == c)
			i++;
	}
	return (count);
}