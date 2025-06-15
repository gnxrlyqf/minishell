#include <main.h>

void throw_err(void)
{
	static error_handler handlers[] = {
		NULL,
		empty_prompt,
		unexpected_token,
		malloc_fail,
		pipe_fail,
		read_fail,
		write_fail,
		cmd_enoent,
		ambig_redir
	};
	handlers[g_shell.error->code](g_shell.error->data);
	free(g_shell.error->data);
}

void set_err(t_err code, char *data)
{
	g_shell.error->code = code;
	g_shell.error->data = ft_strndup(data, 0);
}