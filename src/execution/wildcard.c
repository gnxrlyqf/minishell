#include <main.h>

int	check_wildcard(char *exp, char *file)
{
	while (*exp && *file)
	{
		if (*exp == '*')
		{
			exp++;
			if (!*exp)
				return (1);
			while (*file && *file != *exp)
				file++;
		}
		if (*exp && *file != *exp)
			return (0);
		file++;
		exp++;
	}
	return (1);
}

int get_wildcard_files(t_list **files, char *exp)
{
	int count;
	DIR *dir;
	struct dirent *dirent;

	dir = opendir(".");
	count = 0;
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (check_wildcard(exp, dirent->d_name))
		{
			add_node(files, dirent->d_name, 3);
			count++;
		}
	}
	// if (!count)
	// {
	// 	add_node(files, exp, 3);
	// 	count = 1;
	// }
	return (count);
}

char **make_args(t_list *files, int size)
{
	char **new;
	t_list *curr;

	new = malloc(sizeof(char *) * size);
	curr = files;
	while (curr)
	{
		*new = (char *)curr->data.p;
		new++;
		curr = curr->next;
	}
	new -= size;
	return (new);
}

t_member *expand_wildcard(t_member *args)
{
	char **arr;
	int count;
	int size;
	t_list *files;

	files = NULL;
	count = 0;
	arr = (char **)args->members;
	while (count < args->size)
	{
		if (!ft_strchr(arr[count], '*'))
			add_node(&files, arr[count], 3);
		else
			size = get_wildcard_files(&files, arr[count]);
		count++;
	}
	free(args->members);
	args->members = (void **)make_args(files, size);
	args->size = size;
	args->type = ARGS;
	return (args);
}
