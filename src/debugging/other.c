#include <main.h>

void print_env(t_env *env)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void print_list(t_list *list, int type)
{
	t_list *curr;
	char *str;

	(void)type;
	curr = list;
	while (curr)
	{
		str = (char *)curr->data.p;
		printf("%s\n", str);
		curr = curr->next;
	}
}

void print_envp(char **envp)
{
	while (*envp)
	{
		puts(*envp);
		envp++;
	}
}