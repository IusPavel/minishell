#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*new;

	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (0);
	i = 0;
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
