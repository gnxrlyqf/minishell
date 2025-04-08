#include <main.h>

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(s1);
	while (--len && ft_strchr(set, s1[len]))
		;
	if (!len)
		return (ft_strdup(""));
	i = -1;
	while (s1[++i] && ft_strchr(set, s1[i]))
		len--;
	new = malloc(++len + 1);
	if (!new)
		return (NULL);
	new += len + 1;
	*new = 0;
	while (len--)
		*(--new) = s1[i + len];
	return (new);
}

char	*ft_strstr(char *big, char *little)
{
	int		i;
	int		j;
	char	*temp;

	if (!big || !little || !*little)
		return (big);
	i = 0;
	while (big[i])
	{
		if (big[i] == *little)
		{
			j = i;
			temp = little;
			while (*temp && *temp == big[j])
			{
				j++;
				temp++;
			}
			if (!*temp)
				return (big + i);
		}
		i++;
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
