/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:40:53 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:40:54 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;
	char	*point;
	char	*cut;

	point = (char *)haystack;
	cut = (char *)needle;
	if (*cut == 0)
		return (point);
	i = 0;
	needle_len = ft_strlen(needle);
	while ((point[i] != 0) && (len >= needle_len + i))
	{
		if (cut[0] == point[i])
		{
			if ((ft_strncmp(&(point[i]), needle, needle_len) == 0))
				return (&(point[i]));
		}
		i++;
	}
	return (0);
}
