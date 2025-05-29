#include <main.h>

int match_tokens(t_token curr, t_token next)
{
	static int *cases;
	static int sub_flag;

	sub_flag += (next & SUB_CLOSE) - ((next & OP) != 0) * sub_flag;
	if (sub_flag && !((curr ^ WORD) | (WORD ^ next)))
		return (0);
	if (!next)
		return (sub_flag = 0, curr & (WORD | SUB_CLOSE));
	if (!cases)
	{
		cases = malloc(sizeof(int) * 5);
		cases[0] = WORD | SUB_OPEN | REDIR; //SUB_OPEN
		cases[1] = OP | REDIR | SUB_CLOSE; //SUB_CLOSE
		cases[2] = WORD | OP | REDIR | SUB_CLOSE; //WORD
		cases[3] = WORD; //REDIR
		cases[4] = WORD | REDIR | SUB_OPEN; //OP
	}
	return (next & cases[ft_log2(curr)]);	
}

t_token token_word(char **str, char *cpy, int *len)
{
	while (*cpy && !ft_strchr(" |&()<>", *cpy))
	{
		if (*cpy == '"' || *cpy == '\'')
		{
			*len += skip(cpy, 1, *cpy, 0);
			cpy += *len;
		}
		(*len)++;
		cpy++;
	}
	*str = cpy;
	return (WORD);
}

t_token token_op(char **str, char *cpy, int *len)
{
	t_token ret;

	ret = OP;
	if (*cpy == *(cpy + 1))
		*len = 2;
	else
	{
		ret += (*cpy == '&') * OP;
		*len = 1;
	}
	cpy += *len;
	*str = cpy;
	return (ret);
}

t_token token_redir(char **str, char *cpy, int *len)
{
	t_token ret;

	ret = REDIR;
	if (*cpy == *(cpy + 1))
		(*len)++;
	(*len)++;
	cpy += *len;
	*str = cpy;
	return (ret);
}

t_token next_token(char **str, int *len)
{
	char *cpy;

	cpy = *str;
	while (*cpy == ' ')
		cpy++;
	while (*cpy)
	{
		*len = 0;
		if (*cpy == '(' || *cpy == ')')
			return (*str = cpy + 1, *len = 1, *cpy - 39);
		if (*cpy == '|' || *cpy == '&')
			return (token_op(str, cpy, len));
		if (*cpy == '>' || *cpy == '<')
			return (token_redir(str, cpy, len));
		if (*cpy != ' ')
			return (token_word(str, cpy, len));
		cpy++;
	}
	*str = cpy;
	return (TOKEN_NONE);
}
