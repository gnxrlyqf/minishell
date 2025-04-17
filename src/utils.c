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

	if (ft_strchr("()", c))
		subshell = 1 + 2 * (c - '(');
	stop = ft_strlen(str) * !rev - rev;
	while (i != stop && str[i] != c)
	{

		i += 1 - 2 * rev;
	}
	return (i);
}

int	wc(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip(str, i + 1, str[i], 0);
		if (str[i] == '(')
			i = skip(str, i, ')', 0);
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**tokenize(char *str)
{
	char	**args;
	int i;

	i = wc(str, ' ');
	args = malloc(sizeof(char *) * (i + 1));
	args[i] = NULL;
	i = -1;
	args[0] = ft_strtok(str, " ");
	while (args[++i])
		args[i + 1] = ft_strtok(NULL, " ");
	return (args);
}
