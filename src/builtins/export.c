#include <main.h>

int export(char **args, int size)
{
	char *key;
	t_env *var;

	args++;
	size--;
	while (size--)
	{
		if (**args == '=')
		{
			set_err(EXPORT_INVALID_ID, *args);
			return (1);
		}
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
	}
	return (0);
}