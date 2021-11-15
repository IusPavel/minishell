/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:40:37 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:40:38 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		length;
	int		index;

	if (!s1 || !s2)
		return (0);
	length = 0;
	index = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (result == 0)
		return (result);
	while (*(s1 + length))
		result[index++] = s1[length++];
	length = 0;
	while (*(s2 + length))
		result[index++] = s2[length++];
	result[index] = '\0';
	return (result);
}
