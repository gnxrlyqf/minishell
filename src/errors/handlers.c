#include <main.h>

void unexpected_token(char *data)
{
	write(2, "Error: unexpected token: `", 26);
	write(2, data, ft_strlen(data));
	write(2, "'\n", 2);
}

void syscall_fail(char *data)
{
	write(2, "Error: malloc fail at ", 23);
	write(2, data, ft_strlen(data));
	write(2, "\n", 1);
}
