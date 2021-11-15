/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:40:23 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:40:24 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	size_t	len;

	result = (char *) s;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*result == (char)c)
			return (result);
		result++;
	}
	return (0);
}
