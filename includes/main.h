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
# include <assert.h>

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
	EMPTY_PROMPT,
	INV_TOKEN,
	MALLOC_FAIL,
	PIPE_FAIL,
	READ_FAIL,
	WRITE_FAIL,
	CMD_ENOENT,
	AMBIG_REDIR,
} t_err;

typedef struct s_err
{
	t_err code;
	void *data;
} t_error;

typedef union u_data
{
	char c;
	int i;
	void *p;
} t_data;

typedef struct s_list
{
	struct s_list	*next;
	t_data			data;
} t_list;

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

typedef struct s_shell
{
	char *str;
	t_member *exp;
	t_error *error;
	t_env *env;
	int exit_status;
} t_shell;

typedef void (*error_handler)(void *data);

extern t_shell g_shell;

t_list		*add_node(t_list **head, void *value, int type);
int			list_len(t_list *list);

void		print_ast(t_member *tree, int indent);
void		print_env(t_env *env);
void		print_list(t_list *list, int type);

int			count_args(char *str);
char		*next_word(char **str);
int			cleanup(t_member *member);
char		*clean_quotes(char *str);

t_member	*init_cmd(char *str);
t_member	*parse_cmd(char *str);
t_member	*parse_logop(char *str);
t_member	*init_member(int size, t_type type);
t_member	*parse_init(char *str);
t_member	*parse_pipeline(char *str);
t_member	*parse_subshell(char *str);
void		parse_redir(t_member **list, char **str, int index);
int			count_redir(char *str);
void		parse_redir_sub(t_member **list, char *str, int count);

int			check_quotes(char *str);
int			validate_input(char *str);
char		*get_input(void);

int			match_tokens(t_token curr, t_token next);
t_token		token_word(char **str, char *cpy, int *len);
t_token		token_op(char **str, char *cpy, int *len);
t_token		token_redir(char **str, char *cpy, int *len);
t_token		next_token(char **str, int *len);

t_env		*init_env(char **envp);
void		init_shell(char **envp);

char		*quotes_expand(char *str, t_env *env);

char		*ft_strrstr_skip(char *str, char *sub);
char		*ft_strstr_skip(char *str, char *sub);
char		*ft_strchr(char *str, char c);
int			ft_strlen(char *str);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strndup(char *str, char *set);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *src);

char		*max_str(char *a, char *b);
int			skip(char *str, int i, char c, int rev);
int			wc(char *str, char c);
int			is_empty(char *str);
int			ft_log2(int n);
void		free_tree(t_member *tree);

int			get_wildcard_files(t_list **files, char *exp);
t_member	*expand_wildcard(t_member *args);
int			check_wildcard(char *exp, char *file);

void		set_err(t_err code, char *data);
void		throw_err(void);
void		unexpected_token(void *data);
void		malloc_fail(void *data);
void		pipe_fail(void *data);
void		read_fail(void *data);
void		write_fail(void *data);
void		ambig_redir(void *data);
void		empty_prompt(void *data);
void		cmd_enoent(void *data);

#endif