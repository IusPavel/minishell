/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:05:46 by signacia          #+#    #+#             */
/*   Updated: 2021/11/08 16:06:03 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wildcards_handler(t_shell *minishell, int *i)
{
	if (minishell->input[*i] == '*' && minishell->apps->is_argv == 1
		&& minishell->apps->token != TOKEN_HEREDOC
		&& minishell->apps->token != TOKEN_REDIRECT_INPUT
		&& minishell->apps->token != TOKEN_REDIRECT_OUTPUT
		&& minishell->apps->token != TOKEN_REDIRECT_OUTPUT_APPEND)
		minishell->apps->token = WILDCARD_ASTERISK;
	return (0);
}
