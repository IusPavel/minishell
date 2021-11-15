/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:56:00 by prochell          #+#    #+#             */
/*   Updated: 2021/11/14 20:38:44 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_digit(char *str)
{
	int	i;

	if (str[0])
	{
		if ((!ft_isdigit(str[0]) && str[0] != '-')
			|| (str[0] == '-' && str[1] == '\0'))
			return (0);
	}
	i = 1;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

static int	exit_error(char *str)
{
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

int	get_exit(t_shell *minishell, char **str)
{
	int	len;

	if (!ft_strcmp("exit", str[0]))
	{
		len = 0;
		while (str[len])
			len++;
		if (len > 2)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			minishell->child_exit_status = 1;
			return (0);
		}
		else if (len == 2)
		{
			write(2, "exit\n", 5);
			if (has_digit(str[len - 1]))
				exit(ft_atoi(str[len - 1]));
			exit_error(str[len - 1]);
		}
		write(2, "exit\n", 5);
		exit(0);
	}
	return (1);
}
