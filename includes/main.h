#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>	

typedef enum type
{
	NONE,
	OR,
	AND,
	WRITE,
	APPEND,
	READ,
	HEREDOC,
	PIPE,
	CMD,
	SUBSHELL
} t_type;

typedef struct	s_member
{
	t_type			type;
	void			*child1;
	void			*child2;
}	t_member;

char	*ft_strtok_r(char *str, char *delims, char **save);
char	*ft_strdup(char *src);
char	*ft_strchr(char *str, char c);
char	*ft_strstr(char *big, char *little);
char	*find_op(char *str, char *op);
int		ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strtok(char *str, char *delims);

long	max(long a, long b);

void	*deconstruct(char *str);

void print_ast(t_member *tree, int indent);

#endif