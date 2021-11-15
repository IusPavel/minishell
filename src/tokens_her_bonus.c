/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_her_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:23:29 by signacia          #+#    #+#             */
/*   Updated: 2021/11/08 17:23:30 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_or(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		expand_argv(minishell, i);
	++(*i);
	minishell->apps->token = TOKEN_OR;
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
	return (0);
}

int	heredoc(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		expand_argv(minishell, i);
	minishell->apps->token = TOKEN_HEREDOC;
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

int	single_ampersand(t_shell *minishell, int *i)
{
	return (syntax_error(minishell, minishell->input + *i, 1));
}

int	double_ampersand(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		expand_argv(minishell, i);
	++(*i);
	minishell->apps->token = TOKEN_AND;
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
	return (0);
}
