#include <main.h>

t_member *init_member(int size, t_type type)
{
	t_member *member;

	member = malloc(sizeof(t_member));
	member->size = size;
	member->type = type;
	if (type == ARGS)
		member->members = malloc(sizeof(char *) * size);
	else
		member->members = malloc(sizeof(t_member *) * size);
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

char *clean_quotes(char *str)
{
	char    *result;

	int i;
	int j;
	int c;
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (free(str), NULL);
	i = 0;
	j = 0;
	c = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && c == 0)
			c = str[i];
		else if (str[i] == c)
			c = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (free(str), result);
}

t_member *parse_init(char *str, t_error *error)
{
	t_member *exp;

	error->data = NULL;
	exp = init_member(1, SUBSHELL);
	exp->members[0] = parse_logop(str);
	if (!exp || !exp->members[0])
		error->code = ERR_MALLOC;
	return (exp);
}