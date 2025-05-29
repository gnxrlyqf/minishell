#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

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
	PIPELINE,
	SUBSHELL,
	CMD,
	ARGS,
	OUTLIST,
	TRUNC,
	APPEND,
	READ,
	HEREDOC
} t_type;

typedef enum e_err
{
	ERR_NONE,
	INV_TOKEN,
	ERR_MALLOC,
	AMBIG_REDIR
} t_err;

typedef struct s_err
{
	t_err code;
	void *data;
} t_error;

typedef struct s_str
{
	struct s_str *next;
	char c;
} t_str;

typedef struct s_env
{
	struct s_env *next;
	char *name;
	char *value;
} t_env;

typedef struct	s_member
{
	t_type	type;
	int		size;
	void	**members;
}	t_member;

void		print_ast(t_member *tree, int indent);
void		print_env(t_env *env);

int			count_args(char *str);
char		*next_word(char **str);
int			cleanup(t_member *member);
char		*clean_quotes(char *str);

t_member	*init_cmd(char *str);
t_member	*parse_cmd(char *str);
t_member	*parse_logop(char *str);
t_member	*init_member(int size, t_type type);
t_member	*parse_init(char *str, t_error *error);
t_member	*parse_pipeline(char *str);
t_member	*parse_subshell(char *str);
void		parse_redir(t_member **list, char **str, int index);
int			count_redir(char *str);
void		parse_redir_sub(t_member **list, char *str, int count);

t_error		get_error(char *str, int len);
int			check_quotes(char *str);
int			validate_input(char *str, t_error *error);
char		*get_input(t_error *error);

int			match_tokens(t_token curr, t_token next);
t_token		token_word(char **str, char *cpy, int *len);
t_token		token_op(char **str, char *cpy, int *len);
t_token		token_redir(char **str, char *cpy, int *len);
t_token		next_token(char **str, int *len);

t_env		*init_env(char **envp);

char		*quotes_expand(char *str, t_env *env);

char		*ft_strrstr_skip(char *str, char *sub);
char		*ft_strstr_skip(char *str, char *sub);
char		*ft_strchr(char *str, char c);
int			ft_strlen(char *str);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strndup(char *str, char *set);
int			ft_strcmp(char *s1, char *s2);

char		*max_str(char *a, char *b);
int			skip(char *str, int i, char c, int rev);
int			wc(char *str, char c);
int			is_empty(char *str);
int			ft_log2(int n);
void		free_tree(t_member *tree);

void		throw_err(t_error error);


#endif