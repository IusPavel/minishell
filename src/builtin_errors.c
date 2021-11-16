/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:53:01 by prochell          #+#    #+#             */
/*   Updated: 2021/11/16 14:59:17 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_cd(t_shell *minishell)
{
	perror("minishell: cd");
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_cd_not_set(t_shell *minishell, char *str)
{
	write(2, "minishell: cd: ", 15);
	write(2, str, ft_strlen(str));
	write(2, " not set\n", 9);
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_cd_no_file(t_shell *minishell, char *str)
{
	write(2, "minishell: cd: ", 15);
	perror(str);
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_export(t_shell *minishell, char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_unset(t_shell *minishell, char *str)
{
	write(2, "minishell: unset: `", 19);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	minishell->child_exit_status = 1;
	return (0);
}
