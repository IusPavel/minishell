/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_apps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:41:29 by signacia          #+#    #+#             */
/*   Updated: 2021/11/16 19:10:00 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	source_fd_replacer(t_shell *minishell, int switcher)
{
	if (switcher == 0)
	{
		minishell->fd0_source = dup(0);
		minishell->fd1_source = dup(1);
		minishell->fd2_source = dup(2);
	}
	else
	{
		close(minishell->fd0_source);
		close(minishell->fd1_source);
		close(minishell->fd2_source);
	}
	return (0);
}

int	minishell_executor_pipe(t_shell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (minishell->apps->token == IS_PIPE
			&& minishell->apps->output_file == NULL)
		{
			dup2(minishell->apps->fd[1], 1);
			close(minishell->apps->fd[0]);
		}
		if (minishell->apps->input_file != NULL)
			if (dup2(minishell->apps->fd_input_file, 0) == -1)
				exit (1);
		if (builtin_exec(minishell))
			;
		else if (execve(get_prog_name(minishell), minishell->apps->argv,
				get_arr_env(minishell->environment)) == -1)
			executing_error(minishell);
		exit (minishell->child_exit_status);
	}
	else if (pid == -1)
		return (pid_error(minishell));
	computing_exit_status(minishell);
	return (0);
}

static int	minishell_executor_no_pipe(t_shell *minishell)
{
	if (get_pwd(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_echo(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_cd(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_env(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_export(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_unset(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_exit(minishell, minishell->apps->argv) < 1)
		return (0);
	else
		if (minishell_executor_pipe(minishell))
			return (1);
	return (0);
}

void	shell_executor(t_shell *minishell)
{
	minishell->apps = minishell->apps->head;
	while (1)
	{
		if (minishell_pre_executor(minishell))
			break ;
		signal(SIGINT, cntrl_c2);
		if (minishell->launch_method == IS_PIPE && minishell->apps->argv)
		{
			if (minishell_executor_pipe(minishell))
				break ;
		}
		else if (minishell->apps->argv)
		{
			if (minishell_executor_no_pipe(minishell))
				break ;
		}
		minishell_post_executor(minishell);
		if (minishell->apps->next == NULL
			|| (minishell->apps->token == TOKEN_OR
				&& minishell->child_exit_status == 0)
			|| (minishell->apps->token == TOKEN_AND
				&& minishell->child_exit_status != 0))
			break ;
		minishell->apps = minishell->apps->next;
	}
}

void	minishell_scheduler(t_shell *minishell)
{
	source_fd_replacer(minishell, 0);
	shell_executor(minishell);
	signal(SIGINT, cntrl_c);
	source_fd_replacer(minishell, 1);
}
