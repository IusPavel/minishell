#include "libft.h"
#include <stdlib.h>

static char	**ft_cleaner(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static size_t	ft_num(char const *s, char c)
{
	size_t	i;
	size_t	num;

	i = 0;
	num = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			num++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		num++;
	return (num);
}

static void	ft_next_str(char **next, size_t *next_len, char c)
{
	size_t	i;

	i = 0;
	*next += *next_len;
	*next_len = 0;
	while (**next && **next == c)
		(*next)++;
	while ((*next)[i])
	{
		if ((*next)[i] == c)
			return ;
		(*next_len)++;
		i++;
	}
}

static char	**ft_splitter(const char *s, char **result, char c, size_t num)
{
	size_t	i;
	char	*next;
	size_t	next_len;

	i = 0;
	next = (char *)s;
	next_len = 0;
	while (i < num)
	{
		ft_next_str(&next, &next_len, c);
		result[i] = (char *)malloc(sizeof(char) * (next_len + 1));
		if (!result[i])
			return (ft_cleaner(result));
		ft_strlcpy(result[i], next, next_len + 1);
		i++;
	}
	result[i] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	num;

	if (!s)
		return (0);
	if (!*(s))
		return (ft_calloc(sizeof(char *), 1));
	num = ft_num(s, c);
	result = (char **)malloc(sizeof(char *) * (num + 1));
	if (!result)
		return (0);
	return (ft_splitter(s, result, c, num));
}
