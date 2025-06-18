#include <main.h>

void exec_builtins(t_member *member)
{
	int 			i;
	static builtin	funcs[] = {
		echo, cd, pwd, export, unset, env, _exit
	};
	static char		*names[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};

	i = 0;
	while (i < 7 && ft_strcmp(member->members[0], names[i]))
		i++;
	if (i == 7)
		return ;
	funcs[i](member);
}
