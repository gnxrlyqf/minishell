#ifndef UTILS_H
# define UTILS_H

#include <main.h>

char	*ft_strrstr_skip(char *str, char *sub);
char	*ft_strstr_skip(char *str, char *sub);
char	*ft_strchr(char *str, char c);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*max_str(char *a, char *b);
int		skip(char *str, int i, char c, int rev);
int		wc(char *str, char c);
int		is_empty(char *str);
int		ft_log2(int n);

#endif