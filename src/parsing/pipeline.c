#include <main.h>

t_member *parse_pipeline(char *str)
{
	t_member *pipeline;
	int count;
	int i;
	int skip;

	count = wc(str, '|');
	if (count <= 1)
		return (parse_subshell(str));
	pipeline = init_member(count, PIPELINE);
	skip = 0;
	i = -1;
	while (--count)
	{
		skip = ft_strlen(str) - ft_strlen(ft_strstr_skip(str, "|"));
		str[skip] = 0;
		pipeline->members[++i] = parse_subshell(str);
		str += skip + 1;
	}
	pipeline->members[++i] = parse_subshell(str);
	return (pipeline);
}
