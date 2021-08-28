#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*point;
	size_t	i;

	point = (char *)malloc(ft_strlen(s1) + 1);
	if (!point)
		return (0);
	i = 0;
	while (*(s1 + i))
	{
		*(point + i) = *(s1 + i);
		i++;
	}
	*(point + i) = '\0';
	return (point);
}
