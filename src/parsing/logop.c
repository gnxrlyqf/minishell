#include <main.h>

t_member *parse_logop(char *str)
{
	char *split;
	t_member *op;

	split = max_str(ft_strrstr_skip(str, "&&"), ft_strrstr_skip(str, "||"));
	if (!split)
		return (parse_pipeline(str));
	op = init_member(2, AND * (*split == '&') + OR * (*split == '|'));
	if (!op)
		return (NULL);
	str[ft_strlen(str) - ft_strlen(split)] = 0;
	split += 2;
	op->members[0] = parse_logop(str);
	op->members[1] = parse_pipeline(split);
	if (!op->members[0] || !op->members[1])
		return (cleanup(op), NULL);
	return (op);
}
