/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_asterisk_u.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:05:10 by signacia          #+#    #+#             */
/*   Updated: 2021/11/20 15:33:57 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lonely_pattern(char *pattern, t_aster	*astr)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	ret[0] = pattern;
	ret[1] = NULL;
	astr->argc++;
	return (ret);
}

t_aster	create_astr(void)
{
	t_aster	astr;

	astr.dir = NULL;
	astr.cmp = NULL;
	astr.k = 0;
	astr.j = 0;
	astr.argc = 0;
	return (astr);
}

int	split_into_heredoc_loop(t_shell *minishell)
{
	char	*eof;

	while (1)
	{
		eof = readline("> ");
		if (errno == EINTR)
		{
			free(eof);
			close(minishell->apps->fd_heredoc[0]);
			close(minishell->apps->fd_heredoc[1]);
			return (1);
		}
		if (!eof)
			break ;
		if (!ft_strcmp(minishell->apps->heredoc, eof))
		{
			free(eof);
			break ;
		}
		write(minishell->apps->fd_heredoc[1], eof, ft_strlen(eof));
		write(minishell->apps->fd_heredoc[1], "\n", 1);
		free(eof);
	}
	close(minishell->apps->fd_heredoc[1]);
	return (0);
}

int	split_into_argument(t_shell *minishell, int *i)
{
	int			k;
	char		**tmp;

	k = -1;
	tmp = (char **)malloc(sizeof(char *) * (++(minishell->apps->argc) + 1));
	while (++k < minishell->apps->argc - 1)
		tmp[k] = minishell->apps->argv[k];
	if (minishell->apps->argv != NULL)
		free(minishell->apps->argv);
	tmp[k] = ft_substr(minishell->input, 0, *i);
	tmp[k + 1] = NULL;
	minishell->apps->is_argv = 1;
	minishell->apps->argv = tmp;
	return (0);
}

int	loop_event(void)
{
	return (0);
}
