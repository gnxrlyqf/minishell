#include <main.h>

t_member *parse_cmd(char *str)
{
	t_member *cmd;

	cmd = malloc(sizeof(t_member));
	cmd->size = wc(str, ' ');
	cmd->type = CMD;
	cmd->members = (void **)tokenize(str);
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
		subshell = malloc(sizeof(t_member));
		subshell->type = SUBSHELL;
		subshell->size = 1;
		subshell->members = malloc(sizeof(t_member *));
		str++;
		i = ft_strlen(str) - 1;
		while (str[i] != ')')
			i--;
		str[i] = 0;
		subshell->members[0] = parse_logop(str);
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
	i = 0;
	skip = 0;
	pipeline = malloc(sizeof(t_member));
	pipeline->type = PIPELINE;
	pipeline->size = count;
	pipeline->members = malloc(count * sizeof(t_member *));
	while (i < count)
	{
		skip += ft_strlen(strstr_skip(str, "|"));
		str[skip] = 0;
		pipeline->members[i++] = parse_subshell(str);
		str += skip + 1;
	}
	return (pipeline);
}

t_member *parse_logop(char *str)
{
	char *split;
	t_member *op;

	split = max_str(strrstr_skip(str, "&&"), strrstr_skip(str, "||"));
	if (!split)
		return (parse_pipeline(str));
	op = malloc(sizeof(t_member));
	op->type = AND * (*split == '&') + OR * (*split == '|');
	op->members = malloc(2 * sizeof(t_member *));
	op->size = 2;
	str[ft_strlen(split)] = 0;
	split += 2;
	op->members[0] = parse_logop(str);
	op->members[1] = parse_pipeline(split);
	return (op);
}
