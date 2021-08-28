#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (dst[x] != '\0' && x < dstsize)
		x++;
	while (src[y] && x + y + 1 < dstsize)
	{
		dst[x + y] = src[y];
		y++;
	}
	if (x != dstsize)
		dst[x + y] = '\0';
	return (x + ft_strlen(src));
}
