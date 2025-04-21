#include <main.h>

char *check_subshell(char *str, int *err)
{
	str++;
	while (*str && *str == ' ')
		str++;
	if (ft_strchr("&|)", *str))
		*err = 1;
	return (str);
}

char *check_op_pipe(char *str, int *err)
{
	if (*str == '|')
	{
		str++;
		if (!*str)
			*err = 1;
		if (*str == '|')
			str++;
	}
	if (*str == '&')
	{
		str++;
		if (*str != '&')
			*err = 1;
		str++;
	}
	while (*str && *str == ' ')
		str++;
	if (ft_strchr("|&)", *str))
		*err = 1;
	return (str);
}

int validate_input(char *str)
{
	int err;
	char *token;
	int subshell;

	err = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			str += skip(str, 1, *str, 0);
			if (*str)
				return (0);
		}
		if (*str == '|' || *str == '&')
			str = check_op_pipe(str, &err);
		if (*str == '(')
		{
			str = check_subshell(str, &err);
			subshell++;
		}
		if (*str == ')')
			subshell--;
		if (err)
			return (0);
		str++;
	}
	return (!subshell);
}
