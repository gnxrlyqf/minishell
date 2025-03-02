#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>	

typedef enum lexicon
{
	cmd,
	var,
	pipe,
	overwr,
	open,
	append,
	heredoc,
	and,
	or
} t_lex;

typedef struct s_list
{
	void *elem;
	t_lex type;
	struct s_list *next;
} t_list;

#endif