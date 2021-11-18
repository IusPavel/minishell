/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 20:20:28 by prochell          #+#    #+#             */
/*   Updated: 2021/11/18 19:18:36 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_once(char *str, char ch)
{
	int		i;
	char	**new_str;

	if (!str)
		return (NULL);
	new_str = (char **)malloc(sizeof(char *) * 3);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			break ;
		i++;
	}
	new_str[0] = ft_substr(str, 0, i);
	if (str[i] != ch)
		new_str[1] = ft_strdup("");
	else
		new_str[1] = ft_strdup(str + i + 1);
	new_str[2] = NULL;
	return (new_str);
}
