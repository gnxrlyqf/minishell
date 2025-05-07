#ifndef PARSING_H
# define PARSING_H

# include <main.h>

int			count_args(char *str);
char		*next_word(char **str);
void		*cleanup(t_member *member);
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

#endif