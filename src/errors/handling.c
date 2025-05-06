#include <main.h>

typedef void (*error_handler)(void *data);

void unexpected_token(void *data)
{
	data = (char *)data;
	write(2, "Error: unexpected token: `", 26);
	write(2, data, ft_strlen(data));
	write(2, "'\n", 2);
}

void malloc_error(void *data)
{
	(void)data;
	write(2, "Error: malloc fail\n", 19);
}

void throw_err(t_error error)
{
	static error_handler *handlers;

	if (!handlers)
	{
		handlers = malloc(sizeof(error_handler) * 3);
		handlers[0] = NULL;
		handlers[1] = unexpected_token;
		handlers[2] = malloc_error;
	}
	handlers[error.code](error.data);
}