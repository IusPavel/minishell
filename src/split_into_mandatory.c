/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_mandatory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:05:21 by signacia          #+#    #+#             */
/*   Updated: 2021/11/20 21:56:10 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_into_output_file(t_shell *minishell, int *i)
{
	if (minishell->apps->do_not_launch == 0)
	{
		if (minishell->apps->output_file != NULL)
		{
			close(minishell->apps->fd_output_file);
			free(minishell->apps->output_file);
			minishell->apps->output_file = NULL;
		}
		minishell->apps->output_file = ft_substr(minishell->input, 0, *i);
		if (minishell->apps->output_file == NULL)
			standard_error(minishell, NULL);
		if (minishell->apps->token == TOKEN_REDIRECT_OUTPUT)
			minishell->apps->fd_output_file = open(minishell->apps->output_file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			minishell->apps->fd_output_file = open(minishell->apps->output_file,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		if (minishell->apps->fd_output_file == -1)
			standard_error(minishell, minishell->apps->output_file);
	}
	minishell->apps->token = 0;
	return (0);
}

static int	split_into_input_file(t_shell *minishell, int *i)
{
	if (minishell->apps->do_not_launch == 0)
	{
		if (minishell->apps->input_file != NULL)
		{
			close(minishell->apps->fd_input_file);
			free(minishell->apps->input_file);
			minishell->apps->input_file = NULL;
		}
		minishell->apps->input_file = ft_substr(minishell->input, 0, *i);
		if (minishell->apps->input_file == NULL)
			standard_error(minishell, NULL);
		minishell->apps->fd_input_file = open(minishell->apps->input_file,
				O_RDONLY, 0644);
		if (minishell->apps->fd_input_file == -1)
			standard_error(minishell, minishell->apps->input_file);
	}
	minishell->apps->token = 0;
	return (0);
}

static int	split_into_heredoc(t_shell *minishell, int *i)
{
	int	ret;

	if (minishell->apps->heredoc != NULL)
		heredoc_free(minishell);
	minishell->apps->heredoc = ft_substr(minishell->input, 0, *i);
	if (minishell->apps->heredoc == NULL || pipe(minishell->apps->fd_heredoc))
		return (standard_error(minishell, NULL));
	signal(SIGINT, ctrl_hered);
	ret = split_into_heredoc_loop(minishell);
	signal(SIGINT, ctrl_c);
	minishell->apps->token = 0;
	return (ret);
}

// Expanding application table (tokens/not)
int	expand_argv(t_shell *minishell, int *i)
{
	if (minishell->apps->token == TOKEN_REDIRECT_OUTPUT
		|| minishell->apps->token == TOKEN_REDIRECT_OUTPUT_APPEND)
		return (split_into_output_file(minishell, i));
	else if (minishell->apps->token == TOKEN_REDIRECT_INPUT)
		return (split_into_input_file(minishell, i));
	else if (minishell->apps->token == TOKEN_HEREDOC)
		return (split_into_heredoc(minishell, i));
	else if (minishell->apps->token == WILDCARD_ASTERISK)
		return (split_into_asterisk(minishell, i));
	else
		return (split_into_argument(minishell, i));
}

// Expanding application table (launching of expander & removing spaces)
int	split_input(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (expand_argv(minishell, i))
		return (1);
	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
			|| minishell->input[*i + 1] == '\t'))
		++(*i);
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}
