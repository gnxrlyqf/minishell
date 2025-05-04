#include <main.h>

t_member *init_member(int size, t_type type)
{
	t_member *member;

	member = malloc(sizeof(t_member));
	member->size = size;
	member->type = type;
	if (type == ARGS)
		member->members = malloc(sizeof(char *) * size);
	else
		member->members = malloc(sizeof(t_member) * size);
	while (--size > -1)
		member->members[size] = NULL;
	return (member);
}

void *cleanup(t_member *member)
{
	if (member->type != CMD)
		while (--member->size > -1)
			free(member->members[member->size]);
	free(member->members);
	free(member);
	return (NULL);
}
