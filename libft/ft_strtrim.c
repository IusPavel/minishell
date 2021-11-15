/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:40:59 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:41:00 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (0);
	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] && ft_strchr(set, s1[begin]))
		begin++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > begin)
		end--;
	result = (char *)malloc(sizeof(char) * (end - begin + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, &s1[begin], end - begin + 1);
	return (result);
}
