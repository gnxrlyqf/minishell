#include <main.h>

int or(t_member *or)
{
	if (breakdown(or->members[0]))
		return (breakdown(or->members[1]));
	return (0);
}

int and(t_member *and)
{
	if (!breakdown(and->members[0]))
		return (breakdown(and->members[1]));
	return (1);
}

int pipeline(t_member *pipeline)
{
	int i;
	t_member **members;

	members = (t_member **)pipeline->members;
	i = 0;
	while (i < pipeline->size - 1)
	{
		if (members[i]->type == SUBSHELL)
			subshell_pipe(members[i]);
		if (members[i]->type == CMD)
			cmd_pipe(members[i]);
		i++;
	}
	if (members[i]->type == SUBSHELL)
		subshell(members[i]);
	if (members[i]->type == CMD)
		cmd(members[i]);
	return (0);
}

int subshell(t_member *subshell)
{
	int pid;
	int status;

	pid = fork();
	if (pid == -1)
		throw_err(SYSCALL_FAIL, "fork");
	if (!pid)
	{
		if (subshell->size == 2)
			redir(subshell->members[1]);
		exit(breakdown(subshell->members[0]));
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

int cmd(t_member *cmd)
{
	int pid;

	pid = fork();
	if (pid == -1)
		throw_err(SYSCALL_FAIL, "fork");
	if (!pid)
	{
		if (cmd->size == 2)
			redir(cmd->members[1]);
		exec(cmd->members[0]);
	}
	else
		waitpid(pid, &g_shell.status, 0);
	return (g_shell.status);
}
