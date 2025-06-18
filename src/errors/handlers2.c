#include <main.h>

void ambig_redir(char *data)
{
	(void)data;
}

void empty_prompt(char *data)
{
	
}

void cmd_enoent(char *data)
{
	write(2, data, ft_strlen(data));
	write(2, ": command not found\n", 21);
}

void invalid_id(char *data)
{
	
}

void perm_denied(char *data)
{
	
}