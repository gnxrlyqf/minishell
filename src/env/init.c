#include <main.h>

t_env	*add_node_env(t_env **head, char *name, char *value)
{
	t_env	*curr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		set_err(MALLOC_FAIL, "setenv");
		return (NULL);
	}
	new->name = name;
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

t_env *init_env(char **envp)
{
	t_env *env;
	char *var;
	char *name;
	char *value;

	env = NULL;
	while (*envp)
	{
		name = *envp;
		var = *envp;
		while (*var != '=')
			var++;
		*var = 0;
		value = var + 1;
		add_node_env(&env, name, value);
		envp++;
	}
	return (env);
}

char *get_env_val(t_env *env, char *key)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(key, curr->name))
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
		if (!ft_strcmp(key, curr->name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
