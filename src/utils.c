#include <main.h>

char	*max_str(char *a, char *b)
{
	if (a > b)
		return (a);
	return (b);
}

int	wc(char *str, char c)
{
	int	i;
	int	count;
	int skip;

	i = 0;
	count = 0;
	skip = 0;
	while (str[i])
	{
		if (ft_strchr("\"'(", str[i]))
		{
			skip++;
			continue;
		}
		if (ft_strchr("\"')", str[i]))
		{
			skip--;
			continue;
		}
		if (!skip && str[i] != c)
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
	args[0] = ft_strtok(str, " ");
	i = -1;
	while (args[++i])
		args[i + 1] = ft_strtok(NULL, " ");
	return (args);
}
