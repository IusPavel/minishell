#include "libft.h"
#include <stdlib.h>

static int	ft_count(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	if (n == 0)
		len++;
	if (n > 0)
	{
		while (n > 0)
		{
			n = n / 10;
			len++;
		}
	}
	return (len);
}

static char	*ft_unusual_case(char *result, int n)
{
	if (n == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (n == -2147483648)
		ft_strlcpy(result, "-2147483648", 12);
	return (result);
}

char	*ft_itoa(int n)
{
	size_t		len;
	char		*result;
	long long	i;

	i = (long long)n;
	len = ft_count(i);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len--] = '\0';
	if (i == 0 || i == -2147483648)
		return (ft_unusual_case(result, i));
	if (i < 0)
	{
		result[0] = '-';
		i = i * -1;
	}
	while (i > 0)
	{
		result[len] = (i % 10) + '0';
		i = i / 10;
		len--;
	}
	return (result);
}
