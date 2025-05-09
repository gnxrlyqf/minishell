#include <main.h>

void print_args(char **args, int indent, int count)
{
	int i;
	int j;

	j = 0;
	while (j++ < indent)
		printf("    ");
	printf("ARGS: [");
	i = -1;
	while (++i < count)
	{
		printf("\"%s\"", args[i]);
		if (i < count - 1)
			printf(", ");
	}
	printf("]\n");
}

void print_redir(t_member *redir, int indent)
{
	int i;
	int j;
	char *strs[] = {"TYPE_NONE", "OR", "AND", "REDIR", "TRUNC", "APPEND", "READ", "HEREDOC", "PIPELINE", "CMD", "ARGS", "SUBSHELL"};

	j = 0;
	while (j++ < indent)
		printf("    ");
	i = -1;
	printf("%s:\n", strs[redir->type]);
	while (++i < redir->size)
	{
		j = 0;
		while (j++ < indent + 1)
			printf("    ");
		printf("%s: \"%s\"\n", strs[((t_member *)redir->members[i])->type], (char *)((t_member *)redir->members[i])->members[0]);
	}
}

void print_cmd(t_member *tree, int indent)
{
	int i;
	int j;
	char *strs[] = {"TYPE_NONE", "OR", "AND", "REDIR", "TRUNC", "APPEND", "READ", "HEREDOC", "PIPELINE", "CMD", "ARGS", "SUBSHELL"};

	j = 0;
	i = -1;
	print_args((char **)(((t_member *)tree->members[0])->members), indent, ((t_member *)tree->members[0])->size);
	if (tree->members[1])
		print_redir(tree->members[1], indent);
}

void print_ast(t_member *tree, int indent)
{
	char *strs[] = {"TYPE_NONE", "OR", "AND", "REDIR", "TRUNC", "APPEND", "READ", "HEREDOC", "PIPELINE", "CMD", "ARGS", "SUBSHELL"};
	int i;
	int j;

	j = 0;
	while (j++ < indent)
		printf("    ");
	i = 0;
	printf("%s:\n", strs[tree->type]);
	if (tree->type == CMD)
		print_cmd(tree, indent + 1);
	else if (tree->type == SUBSHELL)
	{
		print_ast(tree->members[0], indent + 1);
		if (tree->size == 2)
			print_redir(tree->members[1], indent + 1);
	}
	else
		while (i < tree->size)
			print_ast(tree->members[i++], indent + 1);
}