/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_u_apps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:41:29 by signacia          #+#    #+#             */
/*   Updated: 2021/11/15 18:54:36 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prog_name(t_shell *minishell)
{
	int		i;
	char	*tmp;
	char	*ret;
	char	**paths;

	ret = minishell->apps->argv[0];
	paths = ft_split(ft_getenv_value(minishell->environment, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", minishell->apps->argv[0]);
		tmp = ft_strjoin_free(paths[i], tmp);
		if (access(tmp, 0) == 0)
			ret = tmp;
		else
			free(tmp);
		i++;
	}
	free(paths);
	return (ret);
}

int	builtin_exec(t_shell *minishell)
{
	if (get_pwd(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_echo(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_cd(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_env(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_export(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_unset(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_exit(minishell, minishell->apps->argv) < 1)
		return (1);
	return (0);
}

int	minishell_pre_executor(t_shell *minishell)
{
	if (minishell->apps->token == IS_PIPE)
		if (pipe(minishell->apps->fd))
			return (runtime_error(minishell, NULL));
	if (minishell->apps->output_file != NULL)
		if (dup2(minishell->apps->fd_output_file, 1) == -1)
			return (runtime_error(minishell, NULL));
	if (minishell->apps->heredoc != NULL)
		if (dup2(minishell->apps->fd_heredoc[0], 0) == -1)
			return (runtime_error(minishell, NULL));
	return (0);
}

int	minishell_post_executor(t_shell *minishell)
{
	if (minishell->apps->token == IS_PIPE)
	{
		dup2(minishell->apps->fd[0], 0);
		close(minishell->apps->fd[1]);
	}
	else if (minishell->apps->token != IS_PIPE)
	{
		dup2(minishell->fd0_source, 0);
		dup2(minishell->fd1_source, 1);
		dup2(minishell->fd2_source, 2);
	}
	if (minishell->apps->output_file != NULL)
	{
		close(minishell->apps->fd_output_file);
		dup2(minishell->fd1_source, 1);
	}
	if (minishell->apps->input_file != NULL)
		close(minishell->apps->fd_input_file);
	if (minishell->apps->heredoc != NULL)
	{
		close(minishell->apps->fd_heredoc[0]);
		dup2(minishell->fd0_source, 0);
	}
	return (0);
}
