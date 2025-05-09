#include <main.h>

t_error get_error(char *str, int len)
{
	t_error error;

	*str = 0;
	str -= len;
	error.data = str;
	error.code = INV_TOKEN;
	return (error);
}

int check_quotes(char *str)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			str += skip(str, 1, *str, 0);
		if (!*str)
			return (0);
		str++;
	}
	return (1);
}

int validate_input(char *str, t_error *error)
{
	t_token curr;
	t_token next;
	int len;
	int subshell;
	int quotes;

	quotes = check_quotes(str);
	curr = next_token(&str, &len);
	if (curr & (OP | SUB_CLOSE | INVALID))
		return (*error = get_error(str, len), 0);
	subshell = (curr == SUB_OPEN) - (curr == SUB_CLOSE);
	while (1)
	{
		next = next_token(&str, &len);
		subshell += (next == SUB_OPEN) - (next == SUB_CLOSE);
		if (next == INVALID || !match_tokens(curr, next))
			return (*error = get_error(str, len), 0);
		if (!next)
			break ;
		curr = next;
	}
	return (!subshell && quotes);
}

char *get_input(t_error *error)
{
	char *line;

	line = readline("ewa SHbitdir$ ");
	if (!line)
		return (NULL);
	// if (is_empty(line))
	// 	return (NULL);
	add_history(line);
	if (!validate_input(line, error))
		return (NULL);
	return (line);
}
