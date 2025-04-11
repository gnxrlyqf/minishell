#include <main.h>

char	*strrstr_skip(char *str, char *sub)
{
	int	i;
	int sublen;

	sublen = ft_strlen(sub);
	i = ft_strlen(str);
	while (--i >= 0)
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip(str, i - 1, str[i], 1);
		if (str[i] == ')')
			i = skip(str, i - 1, '(', 1);
		if (!ft_strncmp(str + i, sub, sublen))
			return (str + i);
	}
	return (NULL);
}

char	*strstr_skip(char *str, char *sub)
{
	int	i;
	int sublen;
	int strlen;

	sublen = ft_strlen(sub);
	strlen = ft_strlen(str);
	i = -1;
	while (++i < strlen)
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip(str, i + 1, str[i], 0);
		if (str[i] == '(')
			i = skip(str, i + 1, ')', 0);
		if (!ft_strncmp(str + i, sub, sublen))
			return (str + i);
	}
	return (NULL);
}

char	*ft_strchr(char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (!*str)
		return (NULL);
	return (str);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*new;

	new = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!src || !new)
		return (NULL);
	i = -1;
	while (src[++i])
		new[i] = src[i];
	new[i] = '\0';
	return (new);
}

char	*ft_strtok_r(char *str, char *delims, char **save)
{
	int	i;

	i = 0;
	if (!str)
		str = *save;
	while (*str && ft_strchr(delims, *str))
		str++;
	if (!*str)
		return (NULL);
	while (*str && !ft_strchr(delims, *str))
	{
		i++;
		str++;
	}
	*save = str + 1 * (*str != 0);
	*str = 0;
	return (str - i);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((*s1 && (*s1 == *s2)) && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	return (*s1 - *s2);
}

char	*ft_strtok(char *str, char *delims)
{
	int	i;
	static char *save;

	i = 0;
	if (!str)
		str = save;
	while (*str && ft_strchr(delims, *str))
		str++;
	if (!*str)
		return (NULL);
	while (*str && !ft_strchr(delims, *str))
	{
		i++;
		str++;
	}
	save = str + 1 * (*str != 0);
	*str = 0;
	return (str - i);
}
