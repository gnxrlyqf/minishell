#include <main.h>

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

int validate_input(char *str)
{
	t_token curr;
	t_token next;
	int len;
	int subshell;
	int quotes;

	quotes = check_quotes(str);
	curr = next_token(&str, &len);
	if (curr & (OP | SUB_CLOSE | INVALID))
		return (*str = 0, str -= len, throw_err(INV_TOKEN, str), 0);
	subshell = (curr == SUB_OPEN) - (curr == SUB_CLOSE);
	while (1)
	{
		next = next_token(&str, &len);
		subshell += (next == SUB_OPEN) - (next == SUB_CLOSE);
		if (next == INVALID || !match_tokens(curr, next))
			return (*str = 0, str -= len, throw_err(INV_TOKEN, str), 0);
		if (!next)
			break ;
		curr = next;
	}
	return (!subshell && quotes);
}

char *get_input(void)
{
	char *line;

	line = readline("ewa SHbitdir$ ");
	if (!line)
	{
		throw_err(SYSCALL_FAIL, "malloc");
		return (NULL);
	}
	if (is_empty(line))
	{
		throw_err(EMPTY_PROMPT, NULL);
		return (NULL);
	}
	add_history(line);
	if (!validate_input(line))
		return (NULL);
	return (line);
}
