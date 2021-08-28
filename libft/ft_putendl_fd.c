#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd > 0)
	{
		write(fd, s, sizeof(char) * ft_strlen(s));
		write(fd, "\n", 1);
	}
}
