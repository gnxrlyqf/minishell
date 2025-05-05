#include <main.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *line;
	t_member *exp;

	exp = malloc(sizeof(t_member));
	while (1)
	{
		line = readline("ewa SHbitdir$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (!validate_input(line))
			continue ;
		printf("OK\n");
		// exp = init_member(1, SUBSHELL);
		// exp->members[0] = parse_logop(line);
		// if (exp->members[0])
		// 	print_ast(exp, 0);
		free(exp->members);
		free(line);
	}
	free(exp);
	rl_clear_history();
}
