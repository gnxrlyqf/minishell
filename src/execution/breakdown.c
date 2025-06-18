#include <main.h>

int my_open(char **path, int flags, int mode)
{
	int fd;
	char *new;

	new = quotes_expand(*path, g_shell.env);
	if (!*new || ft_strchr(new, ' ') || ft_strchr(new, '*'))
		throw_err(AMBIG_REDIR, *path);
	*path = new;
	if ((flags & O_RDONLY) && access(*path, R_OK) == -1)
		throw_err(PERM_DENIED, *path);
	if ((flags & O_WRONLY) && access(*path, W_OK) == -1)
		throw_err(PERM_DENIED, *path);
	fd = open(*path, flags, mode);
	if (fd == -1)
		throw_err(SYSCALL_FAIL, "open");
	return (fd);
}

void redir(t_member *redir)
{
	int i;
	int in;
	int out;
	t_member **redirs;
	char *file;

	redirs = (t_member **)redir->members;
	i = 0;
	in = 0;
	out = 1;
	while (i < redir->size)
	{
		file = redirs[i]->members[0];
		if (redirs[i]->type == READ || redirs[i]->type == HEREDOC)
			in = my_open(&file, O_RDONLY, 0644);
		if (redirs[i]->type == TRUNC)
			out = my_open(&file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (redirs[i]->type == APPEND)
			out = my_open(&file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		i++;
	}
	if (in != 0)
		dup2(in, 0);
	if (out != 1)
		dup2(out, 1);
}

int breakdown(t_member *member)
{
	static func f[] = {
		NULL,
		or,
		and,
		pipeline,
		subshell,
		cmd
	};
	return(f[member->type](member));
}