#include <parsing.h>
#include <utils.h>

int count_args(char *str)
{
	int count;

	count = 0;
	while (ft_strchr(" <>", *str))
		str++;
	while (*str)
	{
		count++;
		while (*str && !ft_strchr(" <>", *str))
		{
			if (*str == '\'' || *str == '"')
				str += skip(str, 1, *str, 0);
			str++;
		}
		while (ft_strchr(" <>", *str))
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

t_member *init_cmd(char *str)
{
	int count;
	t_member *redir;
	t_member *args;
	t_member *cmd;

	redir = NULL;
	count = count_redir(str);
	if (count)
		redir = init_member(count, OUTLIST);
	count = count_args(str) - count;
	args = init_member(count, ARGS);
	cmd = init_member(2 - (!redir), CMD);
	cmd->members[0] = args;
	if (redir)
		cmd->members[1] = redir;
	return (cmd);
}

t_member *parse_cmd(char *str)
{
	int a;
	int r;
	char *word;
	t_member *cmd;

	a = 0;
	r = 0;
	cmd = init_cmd(str);
	while (1)
	{
		while (*str == ' ')
			str++;
		if (*str == '<' || *str == '>')
		{
			parse_redir((t_member **)(&cmd->members[1]), &str, r++);
			continue ;
		}
		word = next_word(&str);
		if (!word)
			break ;
		((t_member *)cmd->members[0])->members[a++] = clean_quotes(word);
	}
	return (cmd);
}

