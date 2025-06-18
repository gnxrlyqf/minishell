#include <main.h>

void	subshell_pipe(t_member *subshell)
{
	int		fdp[2];
	pid_t	pid;

	if (pipe(fdp) == -1)
		throw_err(SYSCALL_FAIL, "pipe");
	pid = fork();
	if (pid == -1)
		throw_err(SYSCALL_FAIL, "fork");
	if (g_shell.error)
		;
	if (!pid)
	{
		close(fdp[0]);
		dup2(fdp[1], 1);
		if (subshell->size == 2)
			redir(subshell->members[1]);
		exit(breakdown(subshell->members[0]));
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		close(fdp[1]);
		dup2(fdp[0], 0);
	}
}

void	cmd_pipe(t_member *cmd)
{
	int		fdp[2];
	pid_t	pid;

	if (pipe(fdp) == -1)
		throw_err(SYSCALL_FAIL, "pipe");
	pid = fork();
	if (pid == -1)
		throw_err(SYSCALL_FAIL, "fork");
	if (!pid)
	{
		close(fdp[0]);
		dup2(fdp[1], 1);
		if (cmd->size == 2)
			redir(cmd->members[1]);
		exec(cmd->members[0]);
	}
	else
	{
		waitpid(pid, &g_shell.status, WNOHANG);
		close(fdp[1]);
		dup2(fdp[0], 0);
	}
}
