/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:24:03 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 15:17:17 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_quote(t_shell *minishell, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (minishell->input[++(*i)])
		if (minishell->input[*i] == '\'')
			break ;
	if (minishell->input[*i] == 0)
		return (syntax_error(minishell, minishell->input + *i, 1));
	tmp = ft_substr(minishell->input, 0, j);
	tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1);
	tmp3 = ft_strdup(minishell->input + *i + 1);
	tmp2 = ft_strjoin_free(tmp2, tmp3);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(minishell->input);
	*i -= 2;
	minishell->input = tmp;
	return (0);
}

int	double_quote(t_shell *minishell, int *i)
{
	t_temp	t;
	int		j;

	j = *i;
	while (minishell->input[++(*i)])
	{
		if (minishell->input[*i] == '\"')
			break ;
		else if (minishell->input[*i] == '$'
			&& minishell->input[*i + 1] != '\"')
			dollar_handler(minishell, i);
	}
	if (minishell->input[*i] == 0)
		return (syntax_error(minishell, minishell->input + *i, 1));
	t.tmp = ft_substr(minishell->input, 0, j);
	t.tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1);
	t.tmp3 = ft_strdup(minishell->input + *i + 1);
	t.tmp = ft_strjoin_free(t.tmp, ft_strjoin_free(t.tmp2, t.tmp3));
	free(minishell->input);
	*i -= 2;
	minishell->input = t.tmp;
	return (0);
}
