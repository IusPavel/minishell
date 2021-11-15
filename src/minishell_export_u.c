/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export_u.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:46:17 by prochell          #+#    #+#             */
/*   Updated: 2021/11/10 12:47:25 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*fullfill_env(t_envp *env)
{
	t_envp	*tmp;
	t_envp	*tmp_env;

	tmp = NULL;
	tmp_env = env;
	while (tmp_env)
	{
		if (tmp_env->value == NULL)
			tmp_env->value = "";
		ft_lstadd_back_minishell(&tmp,
			ft_lstnew_minishell(tmp_env->key, tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (tmp);
}

int	check_export_dup(t_envp *env, char **arr)
{
	t_envp	*tmp_exp;

	tmp_exp = env;
	while (tmp_exp)
	{
		if (!ft_strcmp(tmp_exp->key, arr[0]))
		{
			free(arr[0]);
			free(tmp_exp->value);
			tmp_exp->value = arr[1];
			free(arr);
			return (0);
		}
		tmp_exp = tmp_exp->next;
	}
	ft_lstadd_back_minishell(&env, ft_lstnew_minishell(arr[0], arr[1]));
	return (0);
}

static int	ft_has_alnum(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_export(t_shell *minishell, char **str)
{
	int		i;
	char	**arr;

	i = 0;
	minishell->child_exit_status = 0;
	while (str[++i])
	{
		arr = ft_split_once(str[i], '=');
		if ((!(ft_isalpha(arr[0][0])) && arr[0][0] != '_')
			|| !ft_has_alnum(arr[0]))
		{
			free(arr[0]);
			free(arr[1]);
			free(arr);
			ft_error_export(minishell, str[i]);
		}
		else
			check_export_dup(minishell->environment, arr);
	}
	return (0);
}
