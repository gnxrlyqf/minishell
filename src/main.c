#include <main.h>

char	*strrstr_skip(char *str, char *sub)
{
	int	i;
	int skip;
	int sublen;

	sublen = ft_strlen(sub);
	skip = 0;
	i = ft_strlen(str);
	while (--i >= 0)
	{
		if (ft_strchr("\"')", str[i]))
		{
			skip++;
			continue;
		}
		if (ft_strchr("\"'(", str[i]))
		{
			skip--;
			continue;
		}
		if (!skip && !ft_strncmp(str + i, sub, sublen))
			return (str + i);
	}
	return (NULL);
}

char	*strstr_skip(char *str, char *sub)
{
	int	i;
	int skip;
	int sublen;

	sublen = ft_strlen(sub);
	skip = 0;
	i = -1;
	while (++i >= 0)
	{
		if (ft_strchr("\"'(", str[i]))
		{
			skip++;
			continue;
		}
		if (ft_strchr("\"')", str[i]))
		{
			skip--;
			continue;
		}
		if (!skip && !ft_strncmp(str + i, sub, sublen))
			return (str + i);
	}
	return (NULL);
}


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *line;
	t_member *exp;

	exp = malloc(sizeof(t_member));
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
			add_history(line);
		exp->type = SUBSHELL;
		exp->members = malloc(sizeof(t_member *));
		exp->members[0] = parse_logop(line);
		print_ast(exp, 0);
	}
}