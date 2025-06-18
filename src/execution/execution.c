#include <main.h>

char	*mkpath(char *path, char *cmd)
{
	char	*out;
	int		i;

	if (*cmd == '/')
		return (NULL);
	out = malloc((size_t)(ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!out)
	{
		throw_err(SYSCALL_FAIL, "malloc");
		;
	}
	i = 0;
	while (*path)
		out[i++] = *(path++);
	out[i++] = '/';
	while (*cmd)
		out[i++] = *(cmd++);
	out[i] = 0;
	return (out);
}

char	*check_cwd(char *cmd, t_env *env)
{
	t_env *curr;
	char	*out;

	curr = env;
	while (curr && ft_strcmp(curr->key, "PWD"))
		curr = curr->next;
	if (!curr)
		throw_err(CMD_ENOENT, cmd);
	out = mkpath(curr->value, cmd);
	if (!access(out, F_OK | X_OK))
		return (out);
	free(out);
	return (cmd);
}

char	*check_path(char *path)
{
	struct stat st;
	stat(path, &st);
	if (S_ISDIR(st.st_mode))
		throw_err(IS_DIR, path);
	if (!access(path, F_OK | X_OK))
		return (path);
	throw_err(PERM_DENIED, path);		
	return (NULL);
}

char	*which(char *cmd, t_env *env)
{
	t_env 	*curr;
	char	*out;
	char	*path;
	char	*dup;
	
	path = check_path(cmd);
	if (path)
		return (path);
	curr = env;
	while (curr && ft_strcmp(curr->key, "PATH"))
		curr = curr->next;
	if (!curr)
		throw_err(CMD_ENOENT, cmd);
	dup = ft_strdup(curr->value);
	path = ft_strtok(dup, ":");
	while (path)
	{
		out = mkpath(path, cmd);
		if (!access(out, F_OK | X_OK))
			return (out);
		free(out);
		path = ft_strtok(NULL, ":");
	}
	return (free(dup), check_cwd(cmd, env));
}

void	exec(t_member *args)
{
	char **envp;
	char **arr;
	char *path;

	if (!args->size)
		return ;
	arr = (char **)args->members;
	if (!**arr)
		throw_err(CMD_ENOENT, "");
	exec_builtins(arr);
	path = which(*arr, g_shell.env);
	// free(*arr);
	*arr = path;
	envp = mkenvp(g_shell.env);
	execve(*arr, arr, envp);
	throw_err(CMD_ENOENT, *arr);
}
