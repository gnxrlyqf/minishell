#include <main.h>

void print_args(char **args, int indent, int count)
{
	int i;
	int j;

	j = 0;
	while (j++ < indent)
		printf("    ");
	printf(" [");
	i = -1;
	while (++i < count)
	{
		printf("\"%s\"", args[i]);
		if (i < count - 1)
			printf(", ");
	}
	printf("]");
}

void print_redir(t_member *redir, int indent)
{
	int i;
	int j;
	char *strs[] = {"TYPE_NONE", "OR", "AND", "OUTLIST", "TRUNC", "APPEND", "INLIST", "READ", "HEREDOC", "PIPELINE", "CMD", "ARGS", "SUBSHELL"};

	j = 0;
	while (j++ < indent)
		printf("    ");
	i = -1;
	while (++i < redir->size)
		printf("%s: %s", strs[((t_member *)(redir->members[i]))->type], (char *)((t_member *)(redir->members[i]))->members[0]);
}

void print_cmd(t_member *tree, int indent)
{
	int i;
	int j;

	j = 0;
	while (j++ < indent)
		printf("    ");
	i = -1;
	print_args((char **)(((t_member *)tree->members[0])->members), indent + 1, ((t_member *)tree->members[0])->size);
	if (tree->members[1])
		print_redir(tree->members[1], indent + 1);
	if (tree->members[2])
		print_redir(tree->members[2], indent + 1);
}

void print_ast(t_member *tree, int indent)
{
	char *strs[] = {"TYPE_NONE", "OR", "AND", "OUTLIST", "TRUNC", "APPEND", "INLIST", "READ", "HEREDOC", "PIPELINE", "CMD", "ARGS", "SUBSHELL"};
	int i;
	int j;

	j = 0;
	while (j++ < indent)
		printf("    ");
	i = 0;
	printf("%s:", strs[tree->type]);
	if (tree->type == CMD)
		print_cmd(tree, indent + 1);
	else if (tree->type == SUBSHELL)
	{
		puts("");
		print_ast(tree->members[0], indent + 1);
	}
	else
		while (i < tree->size)
		{
			puts("");
			print_ast(tree->members[i++], indent + 1);
		}
}