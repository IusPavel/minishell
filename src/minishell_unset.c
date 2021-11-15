/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:15:20 by prochell          #+#    #+#             */
/*   Updated: 2021/11/10 18:28:01 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_minishell(t_envp *lst)
{
	t_envp	*before;
	t_envp	*after;

	before = NULL;
	after = NULL;
	if (!lst)
		return ;
	before = lst->prev;
	after = lst->next;
	if (lst->prev)
		before->next = lst->next;
	if (lst->next)
		after->prev = lst->prev;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	unset_del_elem(t_envp *tmp_exp, char *str, int f)
{
	while (tmp_exp && !f)
	{
		if (!ft_strcmp(tmp_exp->key, str))
		{
			ft_lstdelone_minishell(tmp_exp);
			break ;
		}
		tmp_exp = tmp_exp->next;
	}
}

static int	check_equal(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '=')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	check_unset_params(t_shell *minishell, char **str)
{
	t_envp	*tmp_exp;
	int		i;
	int		f;
	int		j;

	i = 1;
	while (str[i])
	{
		f = 0;
		j = 0;
		tmp_exp = minishell->environment;
		while ((!(ft_isalpha(str[i][j])) && (str[i][j] != '_'))
				|| !check_equal(str))
		{
			ft_error_unset(minishell, str[i]);
			f = 1;
			break ;
		}
		unset_del_elem(tmp_exp, str[i], f);
		i++;
	}
}

int	get_unset(t_shell *minishell, char **str)
{
	if (!ft_strcmp("unset", str[0]))
	{
		minishell->child_exit_status = 0;
		if (str[1])
			check_unset_params(minishell, str);
		return (0);
	}
	return (1);
}
