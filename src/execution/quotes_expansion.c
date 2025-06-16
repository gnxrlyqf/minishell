#include <main.h>

t_list	*add_node(t_list **head, void *value, int type)
{
	t_list	*curr;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (type == 1)
		new->data.c = *(char *)value;
	if (type == 2)
		new->data.i = *(int *)value;
	if (type == 3)
		new->data.p = value;
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

void	free_list(t_list **head)
{
	t_list	*current;
	t_list	*temp;

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

int	list_len(t_list *list)
{
	int		i;
	t_list	*curr;

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

int fill_var(char *str, t_list **list, t_env *env)
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
	while (curr && ft_strcmp(curr->key, varname))
		curr = curr->next;
	if (curr)
	{
		value = curr->value;
		while (*value)
		{
			add_node(list, value, 1);
			value++;
		}
		free(varname);
	}
	return (varsize + 1);
}

char *make_str(t_list *list)
{
	char *str;
	int size;
	t_list *curr;
	int i;

	size = list_len(list);
	str = malloc(size + 1);
	str[size] = 0;
	i = 0;
	curr = list;
	while (curr)
	{
		*(str + i) = curr->data.c;
		curr = curr->next;
		i++;
	}
	return (str);
}

char *quotes_expand(char *str, t_env *env)
{
	t_list *list;
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
			add_node(&list, cpy, 1);
		cpy++;
	}
	ret = make_str(list);
	free(str);
	free_list(&list);
	return (ret);
}
