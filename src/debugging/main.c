#include <main.h>

t_shell g_shell;

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *str;

	init_shell(envp);
	while (1)
	{
		str = get_input();
		if (str)
		{
			g_shell.exp = parse_init(str);
			if (g_shell.exp)
				print_ast(g_shell.exp, 0);
		}
		free_tree(g_shell.exp);
		free(str);
		if (g_shell.error->code)
			throw_err();
	}
	rl_clear_history();
}
