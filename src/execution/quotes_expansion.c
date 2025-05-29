#include <main.h>

t_str	*add_node_str(t_str **head, char c)
{
	t_str	*curr;
	t_str	*new;

	new = malloc(sizeof(t_str));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (new);
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	return (new);
}

void	free_list(t_str **head)
{
	t_str	*current;
	t_str	*temp;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}

int	list_len(t_str *list)
{
	int		i;
	t_str	*curr;

	if (!list)
		return (0);
	i = 0;
	curr = list;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

int fill_var(char *str, t_str **list, t_env *env)
{
	t_env *curr;
	char *varname;
	char *value;
	int varsize;

	if (ft_strchr(" '\"", *str))
		return (1);
	varname = ft_strndup(str, " $'\"");
	varsize = ft_strlen(varname);
	curr = env;
	while (curr && ft_strcmp(curr->name, varname))
		curr = curr->next;
	if (curr)
	{
		value = curr->value;
		while (*value)
		{
			add_node_str(list, *value);
			value++;
		}
		free(varname);
	}
	return (varsize + 1);
}

char *make_str(t_str *list)
{
	char *str;
	int size;
	t_str *curr;
	int i;

	size = list_len(list);
	str = malloc(size + 1);
	str[size] = 0;
	i = 0;
	curr = list;
	while (curr)
	{
		*(str + i) = curr->c;
		curr = curr->next;
		i++;
	}
	return (str);
}

char *quotes_expand(char *str, t_env *env)
{
	t_str *list;
	char *cpy;
	char *ret;
	int c;
	
	list = NULL;
	c = 0;
	cpy = str;
	while (*cpy)
	{
		if (*cpy == '$' && c != '\'')
			cpy += fill_var(cpy + 1, &list, env);
		if ((*cpy == '\'' || *cpy == '"') && c == 0)
			c = *cpy;
		else if (*cpy == c)
			c = 0;
		else
			add_node_str(&list, *cpy);
		cpy++;
	}
	ret = make_str(list);
	free(str);
	free_list(&list);
	return (ret);
}
