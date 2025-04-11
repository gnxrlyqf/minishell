#include <main.h>

int validate_input(char *str)
{
	int subshell;
	int squote;
	int dquote;

	subshell = 0;
	dquote = 0;
	squote = 0;
	while (*str)
	{
		if (*str == '"' && !squote)
			dquote = (dquote + 1) % 2;
		if (*str == '\'' && !dquote)
			squote = (squote + 1) % 2;
		subshell += ((*str == '(') - (*str == ')')) * !(dquote || squote);
		str++;
	}
	return (!(squote || dquote || subshell));
}