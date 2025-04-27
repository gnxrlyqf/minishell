#include <main.h>

t_token op_token(char *str)
{
	if (*str == *(str + 1))
		return (OP);
	return (INVALID * (*str == '&') + PIPE * (*str == '|'));
}

t_token next_token(char **str)
{
	char *cpy;

	cpy = *str;
	while (*cpy)
	{
		if (*cpy == '"' || *cpy == '\'')
			return (*str = cpy + skip(cpy, 1, *cpy, 0) + 1, WORD);
		if (*cpy == '(' || *cpy == ')')
			return (*str = cpy + 1, *cpy - 39);
		if (*cpy == '|' || *cpy == '&')
			return (*str = cpy + 1 + (*cpy == *(cpy + 1)), op_token(cpy));
		if (ft_abs(61 - *cpy) == 1)
			return (*str = cpy + 1 + (ft_abs(61 - *(cpy + 1)) == 1), REDIR);
		if (*cpy != ' ')
		{
			while (*cpy && !ft_strchr(" |&()<>'\"", *cpy))
				cpy++;
			*str = cpy;
			return (WORD);
		}
		cpy++;
	}
	*str = cpy;
	return (TOKEN_NONE);
}

int match_tokens(t_token curr, t_token next)
{
	static int *cases;

	if (!next)
		return (curr & (WORD | VAR | SUB_CLOSE));
	if (!cases)
	{
		cases = malloc(sizeof(int) * 7);
		cases[0] = WORD | VAR | REDIR | SUB_OPEN; //SUB_OPEN
		cases[1] = PIPE | OP | REDIR | SUB_CLOSE; //SUB_CLOSE
		cases[2] = WORD | PIPE | OP | REDIR | VAR | SUB_CLOSE; //WORD
		cases[3] = WORD | VAR; //REDIR
		cases[4] = WORD | REDIR | SUB_OPEN; //OP
		cases[5] = WORD | REDIR | SUB_OPEN; //PIPE
		cases[6] = WORD | REDIR | OP | PIPE; //VAR
	}
	return (next & cases[ft_log2(curr)]);	
}

int validate_input(char *str)
{
	t_token curr;
	t_token next;
	int subshell;
	int quotes;

	curr = next_token(&str);
	if (curr & (PIPE | OP | SUB_CLOSE | INVALID))
		return (0);
	subshell = (curr == SUB_OPEN) - (curr == SUB_CLOSE);
	quotes = 0;
	while (1)
	{
		printf("%c\n", *str);
		if (*str == '"' || *str == '"')
			quotes = !quotes;
		next = next_token(&str);
		subshell += (next == SUB_OPEN) - (next == SUB_CLOSE);
		if (next == INVALID || !match_tokens(curr, next))
			return (0);
		if (!next)
			break ;
		curr = next;
	}
	printf("%d - %d\n", !subshell, !quotes);
	return (!subshell && !quotes);
}
