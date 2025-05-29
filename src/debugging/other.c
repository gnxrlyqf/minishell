#include <main.h>

void print_env(t_env *env)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}