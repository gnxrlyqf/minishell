// #include <main.h>

// typedef void (*f)(t_member *member);

// int op(t_member *member)
// {
// 	int res;

// 	res = member->type;
// 	res -= breakdown(member->members[0]);
// 	if (!res)
// 		return (1);
// 	res -= breakdown(member->members[1]);
// 	if (!res)
// 		return (1);
// 	return (0);	
// }

// int cmd(t_member *member)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (!pid)
// 	{
// 		if (member->size == 2)
// 		{
// 			// handle all redirections
// 		}
// 		//execute
// 	}
// }

// int pipeline(t_member *member)
// {
// 	//do pipex on member->members
// }

// int subshell(t_member *member)
// {
// 	if (member->size == 2)
// 	{
// 		// handle all redirections
// 	}
// 	breakdown(member->members[0]);
// }

// int breakdown(t_member *member)
// {
// 	static f funcs[] = {NULL, op, op, pipeline, subshell, cmd};

// 	funcs[member->type](member);
// }
