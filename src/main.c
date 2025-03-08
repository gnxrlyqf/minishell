#include <main.h>

char	*find_op(char *str, char *op)
{
	int	i;
	int subshell;

	i = 0;
	subshell = 0;
	while (str[i])
		i++;
	while (--i >= 0)
	{
		if (ft_strchr("\"')", str[i]))
		{
			subshell++;
			continue;
		}
		if (ft_strchr("\"'(", str[i]))
		{
			subshell--;
			continue;
		}
		if (!subshell && !ft_strncmp(str + i, op, ft_strlen(op)))
			return (str + i + ft_strlen(op));
	}
	return (NULL);
}

char	*trim_str(char *str, int start, int end)
{
	int len;
	int i;
	int size;
	char *out;

	len = ft_strlen(str);
	if (start + end > len)
		return (ft_strdup(""));
	size = len - start - end;
	out = malloc(size + 1);
	i = -1;
	while (++i < size)
		out[i] = *(str++ + start);
	out[size] = 0;
	return (out);
}

char	*clean_str(char *str, char *op, int side)
{
	int len;

	if (side == 0)
	{
		while (*str == ' ')
			str++;
		len = ft_strlen(str) - ft_strlen(op);
		while (str[--len] == ' ')
			;
		str[++len] = 0;
	}
	if (side == 1)
	{
		while (*str == *op || *str == ' ')
			str++;
		len = 0;
	}
	return (str);
}
int	wc(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**tokenize(char *str)
{
	char	**args;
	int i;

	i = wc(str, ' ');
	args = malloc(sizeof(char *) * (i + 1));
	args[i] = NULL;
	args[0] = ft_strtok(str, " ");
	i = -1;
	while (args[++i])
		args[i + 1] = ft_strtok(NULL, " ");
	return (args);
}

void	*deconstruct2(char *str)
{
	int i;
	t_member 	*new;

	while (*str == ' ')
		str++;
	new = malloc(sizeof(t_member));
	new->child2 = NULL;
	if (*str == '(')
	{
		str++;
		new->type = SUBSHELL;
		i = ft_strlen(str) - 1;
		while (str[i] != ')')
			i--;
		str[i] = 0;
		new->child1 = deconstruct(str);
	}
	else if (*str == '\'' || *str == '"')
		new->child1 = str;
	else
	{
		new->type = CMD;
		new->child1 = tokenize(str);
	}
	return (new);
}

void	*deconstruct(char *str)
{
	char *ops;
	char *latest;
	char *split;
	t_type	i;
	t_member *new;

	new = malloc(sizeof(t_member));
	new->type = OR;
	latest = NULL;
	ops = "||\0&&\0>\0\0>>\0<\0\0<<\0|";
	i = 0;
	while (i < 7)
	{
		split = find_op(str, ops + 3 * i++);
		if (split > latest)
		{
			latest = split;
			new->type = i;	
		}
		if (latest && i == 2)
			break ;
	}
	if (latest)
	{
		str[ft_strlen(str) - (ft_strlen(latest) + ft_strlen(ops))] = 0;
		new->child1 = deconstruct(str);
		new->child2 = deconstruct(latest);
		return (new);
	}
	return (deconstruct2(str));
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
		exp->child2 = NULL;
		exp->child1 = deconstruct(line);
		print_ast(exp, 0);
	}
}