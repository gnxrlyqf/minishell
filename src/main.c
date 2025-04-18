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
		if (line)
			add_history(line);
		printf("validity: %d\n", validate_input(line));
		exp->type = SUBSHELL;
		exp->members = malloc(sizeof(t_member *));
		exp->members[0] = parse_logop(line);
		print_ast(exp, 0);
		puts("");
	}
}