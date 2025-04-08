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
	PIPELINE,
	CMD,
	SUBSHELL
} t_type;

typedef struct	s_member
{
	t_type	type;
	int		size;
	void	**members;
}	t_member;

char	*ft_strtok_r(char *str, char *delims, char **save);
char	*ft_strdup(char *src);
char	*ft_strchr(char *str, char c);
char	*ft_strstr(char *big, char *little);
char	*strstr_skip(char *str, char *sub);
char	*strrstr_skip(char *str, char *sub);
int		ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strtok(char *str, char *delims);
int		wc(char *str, char c);
char	**tokenize(char *str);


char	*max_str(char *a, char *b);

t_member *parse_pipeline(char *str);
t_member *parse_subshell(char *str);
t_member *parse_cmd(char *str);
t_member *parse_logop(char *str);

void print_ast(t_member *tree, int indent);

#endif