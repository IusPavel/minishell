/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:26:48 by prochell          #+#    #+#             */
/*   Updated: 2021/11/10 18:32:01 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_minishell(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast_minishell(*lst);
	new->prev = tmp;
	tmp->next = new;
}

void	ft_lstclear_minishell(t_envp **lst)
{
	t_envp	*tmp;

	tmp = NULL;
	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

t_envp	*ft_lstlast_minishell(t_envp *lst)
{
	t_envp	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_envp	*ft_lstnew_minishell(char *key, char *value)
{
	t_envp	*nel;

	nel = (t_envp *)malloc(sizeof(t_envp));
	if (!nel)
		return (NULL);
	nel->key = key;
	nel->value = value;
	nel->next = NULL;
	nel->prev = NULL;
	return (nel);
}

t_envp	*ft_lstfirst_minishell(t_envp *lst)
{
	t_envp	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}
