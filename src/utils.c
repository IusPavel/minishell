/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:25:47 by signacia          #+#    #+#             */
/*   Updated: 2021/11/15 19:25:50 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_envp *lst)
{
	unsigned int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	check_list(t_envp *list)
{
	t_envp	*tmp_lst;

	tmp_lst = list;
	while (tmp_lst)
	{
		write(1, "declare -x ", 11);
		write(1, tmp_lst->key, ft_strlen(tmp_lst->key));
		write(1, "=\"", 2);
		write(1, tmp_lst->value, ft_strlen(tmp_lst->value));
		write(1, "\"\n", 2);
		tmp_lst = tmp_lst->next;
	}
}

char	**get_arr_env(t_envp *env)
{
	t_envp	*tmp_env;
	char	**arr;
	char	*tmp;
	int		i;

	tmp_env = env;
	i = ft_lstsize(tmp_env);
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp_env)
	{
		tmp = ft_strjoin(tmp_env->key, "=");
		arr[i] = ft_strjoin(tmp, tmp_env->value);
		free(tmp);
		tmp_env = tmp_env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	computing_exit_status(t_shell *minishell)
{
	int	ret;

	waitpid(-1, &ret, 0);
	if WIFSIGNALED(ret)
		minishell->child_exit_status = WTERMSIG(ret) + 128;
	else
		minishell->child_exit_status = WEXITSTATUS(ret);
}

void	heredoc_free(t_shell *minishell)
{
	close(minishell->apps->fd_heredoc[0]);
	free(minishell->apps->heredoc);
	minishell->apps->heredoc = NULL;
}
