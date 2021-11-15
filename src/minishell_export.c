/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:32:48 by prochell          #+#    #+#             */
/*   Updated: 2021/11/09 16:31:04 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_swap_01(t_envp **swap)
{
	t_envp	*first;
	t_envp	*second;
	t_envp	*third;

	second = NULL;
	if (!(*swap)->prev)
	{
		if ((*swap) == NULL || (*swap)->next == NULL)
			return ;
		first = *swap;
		first->prev = (*swap)->next;
		second = first->next;
		third = second->next;
		third->prev = first;
		second->prev = NULL;
		first->next = third;
		second->next = first;
		*swap = second;
	}
	else if (!(*swap)->next->next)
		ft_lst_swap_02(swap);
	else
		ft_lst_swap_03(swap);
}

void	ft_lst_swap_02(t_envp **swap)
{
	t_envp	*zero;
	t_envp	*first;
	t_envp	*second;

	second = NULL;
	zero = (*swap)->prev;
	first = *swap;
	first->prev = (*swap)->next;
	second = first->next;
	zero->next = second;
	second->prev = zero;
	first->next = NULL;
	second->next = first;
	*swap = second;
}

void	ft_lst_swap_03(t_envp **swap)
{
	t_envp	*zero;
	t_envp	*first;
	t_envp	*second;
	t_envp	*third;

	second = NULL;
	zero = (*swap)->prev;
	first = *swap;
	first->prev = (*swap)->next;
	second = first->next;
	zero->next = second;
	third = second->next;
	third->prev = first;
	second->prev = zero;
	first->next = third;
	second->next = first;
	*swap = second;
}

int	sort_export(t_envp **tmp_env)
{
	int	i;
	int	j;
	int	list_size;

	list_size = ft_lstsize((*tmp_env));
	i = 0;
	while (i <= list_size - 1)
	{
		j = 0;
		(*tmp_env) = ft_lstfirst_minishell((*tmp_env));
		while (j < list_size - i - 1)
		{
			if (ft_strcmp((*tmp_env)->key, (*tmp_env)->next->key) > 0)
				ft_lst_swap_01(tmp_env);
			*tmp_env = (*tmp_env)->next;
			j++;
		}
		i++;
	}
	return (0);
}

int	get_export(t_shell *minishell, char **str)
{
	t_envp	*tmp_env;

	if (!ft_strcmp("export", str[0]))
	{
		if (str[1])
			return (check_export(minishell, str));
		tmp_env = fullfill_env(minishell->environment);
		sort_export(&tmp_env);
		check_list(tmp_env);
		ft_lstclear_minishell(&tmp_env);
		minishell->child_exit_status = 0;
		return (0);
	}
	return (1);
}
