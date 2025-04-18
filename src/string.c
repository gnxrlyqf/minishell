#include <main.h>

char	*ft_strtrim(char *s1, char c)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(s1);
	while (--len && c == s1[len])
		;
	if (!len)
		return (ft_strdup(""));
	i = -1;
	while (s1[++i] && c == s1[i])
		len--;
	new = malloc(++len + 1);
	if (!new)
		return (NULL);
	new[len] = 0;
	while (1)
	{
		if (!*new)
			break ;
		*(new++) = s1[i++];
	}
	return (new - len);
}

char	*ft_strrstr_skip(char *str, char *sub)
{
	int	i;
	int sublen;

	sublen = ft_strlen(sub);
	i = ft_strlen(str);
	while (--i >= 0)
	{
		if (ft_strchr("'\")", str[i]))
			i = skip(str, i - 1, str[i], 1);
		if (!ft_strncmp(str + i, sub, sublen))
			return (str + i);
	}
	return (NULL);
}

char	*ft_strstr_skip(char *str, char *sub)
{
	int	i;
	int sublen;
	int strlen;

	sublen = ft_strlen(sub);
	strlen = ft_strlen(str);
	i = -1;
	while (++i < strlen)
	{
		if (ft_strchr("'\"(", str[i]))
			i = skip(str, i + 1, str[i], 0);
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
	if (!str)
		return (len);
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

char	*ft_strtok_skip(char *str, char *delims)
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
	if (*str == '\'' || *str == '"')
	{
		i = skip(str, 1, *str, 0) - 1;
		str += i + 1;
	}
	while (*str && !ft_strchr(delims, *str) && *str != '\'' && *str != '"')
	{
		i++;
		str++;
	}
	save = str + 1 * (*str != 0);
	*str = 0;
	return (str - i);
}

