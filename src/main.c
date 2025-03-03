#include <main.h>

t_type id_member(char *str)
{
	int tests[2];

	tests[0] = 61 - *str;
	tests[1] = tests[0] * (61 - (*str + 1))
}

int count_members(char *str)
{
	int tokens;

	tokens = 1;
	while (1)
	{

	}
}

t_member init(char *input)
{
	t_member out;

	out.str = input;
	out.type = exp;
	out.members = id_members(input);
}

int main(int ac, char **av, char **envp)
{
	char *line;

	while (1)
	{
		line = readline("minishell$ ");
		puts(line);
		free(line);
	}
}