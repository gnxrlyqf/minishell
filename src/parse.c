#include <main.h>

t_member *parse_cmd(char *str)
{
	int i;
	t_member *cmd;
	
	i = wc(str, ' ');
	cmd = init_member(i, CMD);
	i = -1;
	cmd->members[++i] = ft_strtok_skip(str, " ");
	if (*(char *)(cmd->members[i]) == '(')
		return (cleanup(cmd));
	while (++i < cmd->size)
	{
		cmd->members[i] = ft_strtok_skip(NULL, " ");
		if (*(char *)(cmd->members[i]) == '(')
			return (cleanup(cmd));
	}
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
		if (is_empty(str) || !subshell->members[0])
			return (cleanup(subshell));
		return (subshell);
	}
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
	if (type == CMD)
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