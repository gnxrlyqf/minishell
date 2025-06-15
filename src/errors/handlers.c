#include <main.h>

void unexpected_token(void *data)
{
	data = (char *)data;
	write(2, "Error: unexpected token: `", 26);
	write(2, data, ft_strlen(data));
	write(2, "'\n", 2);
}

void malloc_fail(void *data)
{
	data = (char *)data;
	write(2, "Error: malloc fail at ", 23);
	write(2, data, ft_strlen(data));
	write(2, "\n", 1);
}
void pipe_fail(void *data)
{
	data = (char *)data;
	write(2, "Error: pipe fail at ", 21);
	write(2, data, ft_strlen(data));
	write(2, "\n", 1);
}
void read_fail(void *data)
{
	data = (char *)data;
	write(2, "Error: cannor read file \"", 25);
	write(2, data, ft_strlen(data));
	write(2, "\"\n", 2);
}
void write_fail(void *data)
{
	data = (char *)data;
	write(2, "Error: cannor write file \"", 26);
	write(2, data, ft_strlen(data));
	write(2, "\"\n", 2);
}
