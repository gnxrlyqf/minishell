#include <parsing.h>
#include <utils.h>

void parse_redir(t_member **list, char **str, int index)
{
	char *cpy;
	t_type type;
	t_member *redir;

	cpy = *str;
	type = TRUNC * (*cpy == '>') + READ * (*cpy == '<');
	redir = init_member(1, type + (*cpy == *(cpy + 1)));
	cpy += 1 + (*cpy == *(cpy + 1));
	redir->members[0] = clean_quotes(next_word(&cpy));
	(*list)->members[index] = redir;
	*str = cpy;
}

int count_redir(char *str)
{
	int count;
	char search;

	count = 0;
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			search = *str;
			count++;
			str += (*(str + 1) == search);
		}
		if (*str == '\'' || *str == '"')
			str += skip(str, 1, *str, 0);
		str++;
	}
	return (count);
}
