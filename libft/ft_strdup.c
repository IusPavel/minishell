/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:40:31 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:40:32 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
