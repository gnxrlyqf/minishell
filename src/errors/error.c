#include <main.h>

void throw_err(t_err code, char *data)
{
	static error_handler handlers[] = {
		NULL,
		empty_prompt,
		unexpected_token,
		syscall_fail,
		perm_denied,
		cmd_enoent,
		ambig_redir,
		invalid_id
	};
	handlers[g_shell.error->code](g_shell.error->data);
	free(g_shell.error->data);
}

void set_err(t_err code, char *data, int throw)
{
	g_shell.error->code = code;
	g_shell.error->data = ft_strdup(data);
	if (throw)
		throw_err(code, data);
}