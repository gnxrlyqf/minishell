#include <main.h>

int count_args(char *str)
{
	int count;

	count = 0;
	while (*str == ' ')
		str++;
	while (*str)
	{
		count++;
		while (*str && *str != ' ')
		{
			if (*str == '\'' || *str == '"')
				str += skip(str, 1, *str, 0);
			else if ((*str == '<' || *str == '>') && *(str - 1) == ' ')
			{
				count -= 2;
				str += 1 + (*(str + 1) == '<' || *(str + 1) == '>');
				break ;
			}
			str++;
		}
		while (*str == ' ')
			str++;
	}
	return (count);
}

int count_redir(char *str, int mode)
{
	int count;
	char search;

	count = 0;
	search = '<' * (!mode) + '>' * (mode == 1);
	while (*str)
	{
		if (*str == search)
		{
			count++;
			*str += (*(str + 1) == search);
		}
		if (*str == '\'' || *str == '"')
			str += skip(str, 1, *str, 0);
		str++;
	}
	return (count);
}

char *next_word(char **str)
{
	char *cpy;
	char *word;
	int i;

	cpy = *str;
	i = 0;
	while (*cpy == ' ')
		cpy++;
	if (!*cpy)
		return (NULL);
	while (cpy[i])
	{
		if (cpy[i] == '\'' || cpy[i] == '"')
			i = skip(cpy, i + 1, cpy[i], 0);
		i++;
		if (ft_strchr(" <>", cpy[i]))
			break ;
	}
	*str = cpy + i;
	word = malloc(sizeof(char) * (i + 1));
	word[i] = 0;
	while (i--)
		word[i] = *(cpy + i);
	return (word);
}

void parse_redir(t_member **cmd, char **str)
{
	char *cpy;
	t_type type;
	t_member *redir;

	cpy = *str;
	type = TRUNC * (*cpy == '>') + READ * (*cpy == '<');
	redir = init_member(1, type + (*cpy == *(cpy + 1)));
	*(redir->members++) = next_word(&cpy);
	(*cmd)->members[1 + (*cpy == '<')] = redir;
	*str = cpy + 1 + (*cpy == *(cpy + 1));
}

t_member *init_cmd(char *str)
{
	int count;
	t_member *in;
	t_member *out;
	t_member *args;
	t_member *cmd;

	count = count_args(str);
	args = init_member(count, ARGS);
	in = NULL;
	out = NULL;
	count = count_redir(str, 0);
	if (count)
		in = init_member(count, INLIST);
	count = count_redir(str, 1);
	if (count)
		out = init_member(count, OUTLIST);
	cmd = init_member(3, CMD);
	cmd->size -= (in != NULL) + (out != NULL);
	cmd->members[0] = args;
	cmd->members[1] = in;
	cmd->members[2] = out;
	return (cmd);
}

t_member *parse_cmd(char *str)
{
	int i;
	char *word;
	t_member *cmd;

	i = 0;
	cmd = init_cmd(str);
	while (1)
	{
		if (*str == '<' || *str == '>')
		{
			parse_redir(&cmd, &str);
			continue ;
		}
		word = next_word(&str);
		if (!word)
			break ;
		((t_member *)cmd->members[0])->members[i++] = word;
	}
	if (cmd->members[1])
		((t_member *)cmd->members[1])->members -= ((t_member *)cmd->members[1])->size;
	if (cmd->members[2])
		((t_member *)cmd->members[2])->members -= ((t_member *)cmd->members[2])->size;
	return (cmd);
}

t_member *parse_subshell(char *str)
{
	t_member *subshell;
	int i;

	while (*str == ' ')
		str++;
	if (*str == '(')
	{
		str++;
		i = ft_strlen(str) - 1;
		while (str[i] != ')')
			i--;
		str[i] = 0;
		subshell = init_member(1, SUBSHELL);
		subshell->members[0] = parse_logop(str);
		if (!subshell->members[0])
			return (cleanup(subshell));
		return (subshell);
	}
	if (is_empty(str))
		return (NULL);
	return (parse_cmd(str));
}

t_member *parse_pipeline(char *str)
{
	t_member *pipeline;
	int count;
	int i;
	int skip;

	count = wc(str, '|');
	if (count <= 1)
		return (parse_subshell(str));
	pipeline = init_member(count, PIPELINE);
	skip = 0;
	i = -1;
	while (--count)
	{
		skip = ft_strlen(str) - ft_strlen(ft_strstr_skip(str, "|"));
		str[skip] = 0;
		pipeline->members[++i] = parse_subshell(str);
		if (is_empty(str) || !pipeline->members[i])
			return (cleanup(pipeline));
		str += skip + 1;
	}
	pipeline->members[++i] = parse_subshell(str);
	if (is_empty(str) || !pipeline->members[i])
		return (cleanup(pipeline));
	return (pipeline);
}

t_member *parse_logop(char *str)
{
	char *split;
	t_member *op;

	split = max_str(ft_strrstr_skip(str, "&&"), ft_strrstr_skip(str, "||"));
	if (!split)
		return (parse_pipeline(str));
	op = init_member(2, AND * (*split == '&') + OR * (*split == '|'));
	str[ft_strlen(str) - ft_strlen(split)] = 0;
	split += 2;
	if (split - 2 == str || is_empty(str) || is_empty(split))
		return (cleanup(op));
	op->members[0] = parse_logop(str);
	op->members[1] = parse_pipeline(split);
	if (!op->members[0] || !op->members[1])
		return (cleanup(op));
	return (op);
}

t_member *init_member(int size, t_type type)
{
	t_member *member;

	member = malloc(sizeof(t_member));
	member->size = size;
	member->type = type;
	if (type == ARGS)
		member->members = malloc(sizeof(char *) * size);
	else
		member->members = malloc(sizeof(t_member) * size);
	while (--size > -1)
		member->members[size] = NULL;
	return (member);
}

void *cleanup(t_member *member)
{
	if (member->type != CMD)
		while (--member->size > -1)
			free(member->members[member->size]);
	free(member->members);
	free(member);
	return (NULL);
}