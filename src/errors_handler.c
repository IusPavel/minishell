/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:04:41 by signacia          #+#    #+#             */
/*   Updated: 2021/11/16 19:09:36 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_shell *minishell, const char *token, int len)
{
	write(2, "minishell: ", 11);
	if (token[0] == 0)
		write(2, "syntax error near unexpected token `newline'\n", 45);
	else
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, token, len);
		write(2, "'\n", 2);
	}
	minishell->child_exit_status = 258;
	return (1);
}

int	standard_error(t_shell *minishell, char *arg_name)
{
	write(2, "minishell: ", 11);
	perror(arg_name);
	minishell->child_exit_status = 1;
	minishell->apps->do_not_launch = 1;
	minishell->apps->token = 0;
	return (1);
}

int	runtime_error(t_shell *minishell, char *arg_name)
{
	write(2, "minishell: ", 11);
	perror(arg_name);
	minishell->child_exit_status = 1;
	minishell_post_executor(minishell);
	return (1);
}

int	executing_error(t_shell *minishell)
{
	struct stat	buff;

	if (!stat(minishell->apps->argv[0], &buff) && S_ISDIR(buff.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, minishell->apps->argv[0], ft_strlen(minishell->apps->argv[0]));
		write(2, ": is a directory\n", 17);
		exit (126);
	}
	else if (ft_strncmp(minishell->apps->argv[0], "./", 2) == 0
		|| ft_strncmp(minishell->apps->argv[0], "../", 3) == 0
		|| ft_strncmp(minishell->apps->argv[0], "/", 1) == 0)
	{
		write(2, "minishell: ", 11);
		perror(minishell->apps->argv[0]);
		if (errno == 13)
			exit (126);
		exit (127);
	}
	write(2, "minishell: ", 11);
	write(2, minishell->apps->argv[0], ft_strlen(minishell->apps->argv[0]));
	write(2, ": command not found\n", 20);
	exit(127);
}

int	pid_error(t_shell *minishell)
{
	dup2(minishell->fd0_source, 0);
	dup2(minishell->fd1_source, 1);
	dup2(minishell->fd2_source, 2);
	if (minishell->apps->output_file != NULL)
		close(minishell->apps->fd_output_file);
	if (minishell->apps->input_file != NULL)
		close(minishell->apps->fd_input_file);
	if (minishell->apps->heredoc != NULL)
		close(minishell->apps->fd_heredoc[0]);
	return (standard_error(minishell, "fork"));
}
