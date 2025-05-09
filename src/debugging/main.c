#include <main.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_member *exp;
	char *str;
	t_error error;

	while (1)
	{
		error.data = NULL;
		str = get_input(&error);
		if (!str)
		{
			throw_err(error);
			continue ;
		}
		exp = parse_init(str, &error);
		if (!exp)
			throw_err(error);
		print_ast(exp, 0);
		free_tree(exp);
	}
	rl_clear_history();
}
