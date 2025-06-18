#include <main.h>

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int validate_id(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
    name++;
    while (*name && *name != '=')
    {
        if (!ft_isalnum(*name) && *name != '_')
            return (0);
        name++;
    }
    return (1);
}

int export(char **args, int size)
{
	char *key;
	t_env *var;

	args++;
	size--;
	while (size--)
	{
		if (!validate_id(*args))
			throw_err(INVALID_ID, *args);
		key = *args;
		while (**args && **args != '=')
			(*args)++;
		if (!**args)
			add_node_env(&g_shell.env, key, NULL);
		else
		{
			**args = 0;
			add_node_env(&g_shell.env, key, (*args) + 1);
		}
		args++;
	}
	return (0);
}