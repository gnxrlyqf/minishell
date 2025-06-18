#include <main.h>

t_member *init_member(int size, t_type type)
{
	t_member *member;

	member = malloc(sizeof(t_member));
	if (!member)
	{
		throw_err(SYSCALL_FAIL, "malloc");
		return (NULL);
	}
	member->size = size;
	member->type = type;
	if (type == ARGS)
		member->members = malloc(sizeof(char *) * size);
	else
		member->members = malloc(sizeof(t_member *) * size);
	if (!member->members)
	{
		throw_err(SYSCALL_FAIL, "malloc");
		return (NULL);
	}
	while (--size > -1)
		member->members[size] = NULL;
	return (member);
}

int cleanup(t_member *member)
{
	if (!member)
		return (1);
	while (--member->size > -1)
		free(member->members[member->size]);
	free(member->members);
	free(member);
	return (0);
}

char *clean_quotes(char *str)
{
	char    *result;
	int i[3];
	
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
	{
		throw_err(SYSCALL_FAIL, "malloc");
		return (free(str), NULL);
	}
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (str[i[0]])
	{
		if ((str[i[0]] == '\'' || str[i[0]] == '"') && i[2] == 0)
			i[2] = str[i[0]];
		else if (str[i[0]] == i[2])
			i[2] = 0;
		else
			result[i[1]++] = str[i[0]];
		i[0]++;
	}
	result[i[1]] = '\0';
	return (free(str), result);
}

t_member *parse_init(char *str)
{
	t_member *exp;

	exp = init_member(1, SUBSHELL);
	exp->members[0] = parse_logop(str);
	if (!exp || !exp->members[0])
		throw_err(SYSCALL_FAIL, "malloc");
	return (exp);
}