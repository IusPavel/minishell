#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (i < n)
	{
		res = *((unsigned char *)s1 + i) - *((unsigned char *)s2 + i);
		if (res != 0)
			return (res);
		i++;
	}
	return (res);
}
