/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:22:26 by prochell          #+#    #+#             */
/*   Updated: 2021/11/10 18:09:42 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_check_flag(char *str)
{
	int	j;

	j = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		if (!str[j])
			return (1);
		while (str[j])
		{
			if (str[j] != 'n')
				return (0);
			else
				if (!str[j + 1])
					return (1);
			j++;
		}
	}
	return (0);
}

void	write_echo(char **args, int i, int n)
{
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		ft_putstr("\n");
}

int	get_echo(t_shell *minishell, char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!ft_strcmp("echo", args[0]))
	{
		if (args[1] == NULL)
		{
			minishell->child_exit_status = 0;
			return (0);
		}
		while (args[i])
		{
			if (echo_check_flag(args[i]))
				n++;
			else
				break ;
			i++;
		}
		write_echo(args, i, n);
		minishell->child_exit_status = 0;
		return (0);
	}
	return (1);
}
