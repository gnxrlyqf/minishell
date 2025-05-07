#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>	

typedef enum e_token
{
	TOKEN_NONE,
	SUB_OPEN = 1,
	SUB_CLOSE = 2,
	WORD = 4,
	REDIR = 8,
	OP = 16,
	INVALID = 32
} t_token;

typedef enum e_type
{
	TYPE_NONE,
	OR,
	AND,
	OUTLIST,
	TRUNC,
	APPEND,
	READ,
	HEREDOC,
	PIPELINE,
	CMD,
	ARGS,
	SUBSHELL
} t_type;

typedef enum e_err
{
	ERR_NONE,
	INV_TOKEN,
	ERR_MALLOC
} t_err;

typedef struct s_err
{
	t_err code;
	void *data;
} t_error;

typedef struct	s_member
{
	t_type	type;
	int		size;
	void	**members;
}	t_member;

#endif