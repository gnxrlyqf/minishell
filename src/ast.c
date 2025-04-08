#include <main.h>

void print_args(char **args, int indent, int count)
{
	int i;
	int j;

	j = 0;
	while (j++ < indent)
		printf("    ");
	printf("[");
	i = -1;
	while (++i < count)
	{
		printf("\"%s\"", args[i]);
		if (i < count - 1)
			printf(", ");
	}
	printf("]\n");
}

void print_ast(t_member *tree, int indent)
{
	char *strs[] = {"NONE", "OR", "AND", "WRITE", "APPEND", "READ", "HEREDOC", "PIPE", "CMD", "SUBSHELL"};
	int i;
	int j;

	j = 0;
	while (j++ < indent)
		printf("    ");
	i = 0;
	printf("%s:\n", strs[tree->type]);
	if (tree->type == CMD)
		print_args((char **)tree->members, 0, tree->size);
	else if (tree->type == SUBSHELL)
	{
		puts("");
		print_ast(tree->members[0], indent + 1);
	}
	else
		while (i < tree->size)
			print_ast(tree->members[i++], indent + 1);
}