#include <main.h>

void init_shell(char **envp)
{
	g_shell.error = malloc(sizeof(t_error));
	throw_err(ERR_NONE, NULL);
	g_shell.env = init_env(envp);
	g_shell.status = 0;
	g_shell.str = NULL;
	g_shell.exp = NULL;
}