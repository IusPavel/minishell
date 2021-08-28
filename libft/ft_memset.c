#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (len--)
	{
		*((char *)b + i) = (unsigned char) c;
		i++;
	}
	return (b);
}
