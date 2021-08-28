#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	void	*res;

	i = 0;
	res = (void *)s;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return (res + i);
		i++;
	}
	return (0);
}
