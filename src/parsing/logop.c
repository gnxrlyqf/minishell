#include <parsing.h>
#include <utils.h>

t_member *parse_logop(char *str)
{
	char *split;
	t_member *op;

	split = max_str(ft_strrstr_skip(str, "&&"), ft_strrstr_skip(str, "||"));
	if (!split)
		return (parse_pipeline(str));
	op = init_member(2, AND * (*split == '&') + OR * (*split == '|'));
	str[ft_strlen(str) - ft_strlen(split)] = 0;
	split += 2;
	if (split - 2 == str || is_empty(str) || is_empty(split))
		return (cleanup(op));
	op->members[0] = parse_logop(str);
	op->members[1] = parse_pipeline(split);
	return (op);
}
