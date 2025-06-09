#include <main.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_list *files;
	t_env *env;
	t_member *exp;
	char *str;
	t_error error;

	env = init_env(envp);
	while (1)
	{
		error.data = NULL;
		str = get_input(&error);
		if (!str)
		{
			throw_err(error);
			continue ;
		}
		get_wildcard_files(&files, str);
		print_list(files, 3);
		files = NULL;
		// exp = parse_init(str, &error);
		// if (!exp)
		// 	throw_err(error);
		// print_ast(exp, 0);
		// free_tree(exp);
		// free(str);
	}
	rl_clear_history();
}
