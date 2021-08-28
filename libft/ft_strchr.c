#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	size_t	len;

	result = (char *) s;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*result == (char)c)
			return (result);
		result++;
	}
	return (0);
}
