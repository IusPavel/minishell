/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:39:45 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:39:46 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_unusual_case(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
}

void	ft_recursive(int n, int fd)
{
	int		memory;
	char	word;

	memory = n;
	if (n > 0)
	{
		n = n / 10;
		word = (memory % 10) + '0';
		ft_recursive(n, fd);
		write(fd, &word, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0 || n == -2147483648)
		ft_unusual_case(n, fd);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		ft_recursive(n, fd);
	}
}
