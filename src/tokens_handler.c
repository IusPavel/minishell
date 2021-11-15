/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:23:15 by signacia          #+#    #+#             */
/*   Updated: 2021/11/14 19:14:26 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_pipe(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		expand_argv(minishell, i);
	minishell->apps->token = IS_PIPE;
	add_application(minishell);
	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
			|| minishell->input[*i + 1] == '\t'))
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
		|| minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
		|| minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input + *i + 1, 1));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	minishell->launch_method = 1;
	return (0);
}

static int	redirect_output(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		expand_argv(minishell, i);
	minishell->apps->token = TOKEN_REDIRECT_OUTPUT;
	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
			|| minishell->input[*i + 1] == '\t'))
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
		|| minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
		|| minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input + *i + 1, 1));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static int	redirect_output_append(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		expand_argv(minishell, i);
	minishell->apps->token = TOKEN_REDIRECT_OUTPUT_APPEND;
	++(*i);
	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
			|| minishell->input[*i + 1] == '\t'))
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
		|| minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
		|| minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input + *i + 1, 1));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static int	redirect_input(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		expand_argv(minishell, i);
	minishell->apps->token = TOKEN_REDIRECT_INPUT;
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
		|| minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
		|| minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input + *i + 1, 1));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

int	tokens_handler(t_shell *minishell, int *i)
{
	if (minishell->input[*i] == '|')
	{
		if (minishell->input[*i + 1] == '|')
			return (handle_or(minishell, i));
		return (handle_pipe(minishell, i));
	}
	else if (minishell->input[*i] == '>')
	{
		if (minishell->input[*i + 1] == '>')
			return (redirect_output_append(minishell, i));
		return (redirect_output(minishell, i));
	}
	else if (minishell->input[*i] == '<')
	{
		if (minishell->input[*i + 1] == '<')
			return (heredoc(minishell, i));
		return (redirect_input(minishell, i));
	}
	else if (minishell->input[*i] == '&')
	{
		if (minishell->input[*i + 1] == '&')
			return (double_ampersand(minishell, i));
		return (single_ampersand(minishell, i));
	}
	return (0);
}
