#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>	

typedef enum type
{
	none,
	exp,
	cmd,
	op_and,
	op_or,
	pipe,
	redir_w,
	redir_r,
	redir_app,
	redir_hd,
	var
} t_type;

typedef struct s_member
{
	char *str;
	t_type type;
	struct s_member *members;
} t_member;

char	*ft_strtok_r(char *str, char *delims, char **save);
char	*ft_strdup(char *src);


#endif