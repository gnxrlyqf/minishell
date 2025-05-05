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
char	*ft_strstr_skip(char *str, char *sub);
char	*ft_strrstr_skip(char *str, char *sub);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strtok_skip(char *str, char *delims);

char	*next_word(char **str);
int		wc(char *str, char c);
int		skip(char *str, int i, char c, int rev);
int		validate_input(char *str);
int		is_empty(char *str);
char	*max_str(char *a, char *b);
int		count_args(char *str);

t_member	*parse_pipeline(char *str);
t_member	*parse_subshell(char *str);
t_member	*parse_cmd(char *str);
t_member	*parse_logop(char *str);
t_member	*parse_init(char *str);
t_member	*init_member(int size, t_type type);
void		parse_redir(t_member **list, char **str, int index);
int			count_redir(char *str);


void print_ast(t_member *tree, int indent);

void *cleanup(t_member *member);
int check_quotes(char *str);
char *clean_quotes(char *str);

int ft_log2(int n);
int ft_abs(int a);


#endif