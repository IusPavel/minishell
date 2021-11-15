/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:38:53 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:38:54 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*point;
	size_t	length;

	length = count * size;
	point = malloc(length);
	if (!point)
		return (0);
	while (length != 0)
	{
		*((char *)point + length - 1) = 0;
		length--;
	}
	return (point);
}
