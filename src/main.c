#include <main.h>

t_list *lexer(char *str)
{
	
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