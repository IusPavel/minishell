/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:37:01 by prochell          #+#    #+#             */
/*   Updated: 2021/11/16 19:10:14 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_get_home(t_shell *minishell)
{
	char	*tmp;
	char	*tmp_str;

	tmp = find_pwd(minishell, "HOME");
	if (!tmp)
		return (ft_error_cd_not_set(minishell, "HOME"));
	tmp_str = getcwd(NULL, 0);
	if (chdir(tmp) != 0)
	{
		if (tmp_str != NULL)
			free(tmp_str);
		return (ft_error_cd_no_file(minishell, tmp));
	}
	change_old_new_pwd(minishell, tmp_str, "OLDPWD");
	free(tmp_str);
	change_old_new_pwd(minishell, tmp, "PWD");
	minishell->child_exit_status = 0;
	return (0);
}

static int	cd_swap(t_shell *minishell)
{
	char	*tmp;
	char	*tmp_str;

	tmp = find_pwd(minishell, "OLDPWD");
	if (!tmp)
		return (ft_error_cd_not_set(minishell, "OLDPWD"));
	tmp_str = getcwd(NULL, 0);
	if (chdir(tmp) != 0)
	{
		if (tmp_str != NULL)
			free(tmp_str);
		return (ft_error_cd_no_file(minishell, tmp));
	}
	tmp = ft_strdup(tmp);
	change_old_new_pwd(minishell, tmp_str, "OLDPWD");
	free(tmp_str);
	change_old_new_pwd(minishell, tmp, "PWD");
	printf("%s\n", tmp);
	free(tmp);
	minishell->child_exit_status = 0;
	return (0);
}

static int	cd_arg(t_shell *minishell, char *str)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (ft_error_cd(minishell));
	if (chdir(str) != 0)
	{
		free(oldpwd);
		return (ft_error_cd_no_file(minishell, str));
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd == NULL)
		return (ft_error_cd(minishell));
	change_old_new_pwd(minishell, oldpwd, "OLDPWD");
	free(oldpwd);
	change_old_new_pwd(minishell, newpwd, "PWD");
	free(newpwd);
	minishell->child_exit_status = 0;
	return (0);
}

int	get_cd(t_shell *minishell, char **str)
{
	if (!ft_strcmp("cd", str[0]))
	{
		if (!str[1] || !ft_strcmp("~", str[1]))
			return (cd_get_home(minishell));
		else if (!ft_strcmp("-", str[1]))
			return (cd_swap(minishell));
		else
			return (cd_arg(minishell, str[1]));
	}
	return (1);
}
