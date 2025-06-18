#include <main.h>

int _chdir(char *dir)
{
	t_env *old;
	t_env *pwd;
	char *oldstr;
	char *pwdstr;

	oldstr = getcwd(NULL, 0);
	old = get_env(g_shell.env, "OLDPWD");
	if (old)
	{
		free(old->value);
		old->value = oldstr;
	}
	else
		add_node_env(&g_shell.env, "OLDPWD", oldstr);
}

int cd(t_member *member)
{
	if (member->size == 1)
		return (_chdir("~"));
	if (member->size > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		exit(1);
	}
	return (_chdir(member->members[1]));
}