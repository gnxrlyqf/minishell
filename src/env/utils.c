#include <main.h>

t_env	*add_node_env(t_env **head, char *name, char *value)
{
	t_env	*curr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		throw_err(SYSCALL_FAIL, "setenv");
		return (NULL);
	}
	new->key = name;
	new->value = value;
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

char *get_env_val(t_env *env, char *key)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

t_env *get_env(t_env *env, char *key)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int env_len(t_env *env)
{
	int size;
	t_env *curr;

	curr = env;
	size = 0;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}