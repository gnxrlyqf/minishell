#include <parsing.h>
#include <utils.h>

void parse_redir_sub(t_member **list, char *str, int count)
{
	int i;

	*list = init_member(count, OUTLIST);
	i = 0;
	while (1)
	{
		if (*str == '<' || *str == '>')
		{
			parse_redir(list, &str, i++);
			continue ;
		}
		str++;
		if (!*str)
			break ;
	}
}

t_member *parse_subshell(char *str)
{
	t_member *subshell;
	int count;
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
		count = count_redir(str + i + 1);
		subshell = init_member(2 - (!count), SUBSHELL);
		if (count)
			parse_redir_sub((t_member **)(&subshell->members[1]), str + i, count);
		subshell->members[0] = parse_logop(str);
		return (subshell);
	}
	return (parse_cmd(str));
}
