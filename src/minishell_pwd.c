/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:28:21 by prochell          #+#    #+#             */
/*   Updated: 2021/11/16 20:42:50 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_shell *minishell, char **str)
{
	char	*tmp;

	if (!ft_strcmp("pwd", str[0]))
	{
		tmp = getcwd(NULL, 0);
		if (tmp == NULL)
			return (0);
		write(1, tmp, ft_strlen(tmp));
		write(1, "\n", 1);
		free(tmp);
		minishell->child_exit_status = 0;
		return (0);
	}
	return (1);
}
