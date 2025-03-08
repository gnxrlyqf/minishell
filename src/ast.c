#include <main.h>

void print_args(char **args, int indent)
{
	int i;

	i = 0;
	while (i++ < indent)
		printf("    ");
	printf("[");
	while (*args)
	{
		printf("\"%s\"", *args);
		args++;
		if (*args != NULL)
			printf(", ");
	}
	printf("]\n");
}

void print_ast(t_member *tree, int indent)
{
	char *strs[] = {"NONE", "OR", "AND", "WRITE", "APPEND", "READ", "HEREDOC", "PIPE", "CMD", "SUBSHELL"};
	int i;

	i = 0;
	while (i++ < indent)
		printf("    ");
	if (tree->child1 && tree->child2)
	{
		printf("%s:\n", strs[tree->type]);
		print_ast(tree->child1, indent + 1);
		print_ast(tree->child2, indent + 1);
	}
	else if (tree->child1 && !tree->child2)
	{
		printf("%s: ", strs[tree->type]);
		if (tree->type == SUBSHELL)
		{
			puts("");
			print_ast(tree->child1, indent + 1);
		}
		if (tree->type == CMD)
			print_args((char **)tree->child1, 0);
	}
}