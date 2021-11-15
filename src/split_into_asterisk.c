/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_asterisk.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:05:18 by signacia          #+#    #+#             */
/*   Updated: 2021/11/08 16:05:19 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**upd_matches(t_aster *astr, char **argv)
{
	int			k;
	char		**tmp;

	k = 0;
	tmp = (char **)malloc(sizeof(char *) * (++(astr->argc) + 1));
	while (k < astr->argc - 1)
	{
		tmp[k] = argv[k];
		k++;
	}
	if (argv != NULL)
		free(argv);
	tmp[k] = ft_strdup(astr->cmp->d_name);
	tmp[k + 1] = NULL;
	return (tmp);
}

static int	search_half_matches(char *pattern, t_aster *astr)
{
	int		tmp_k;
	int		tmp_j;

	if (pattern[astr->k] == astr->cmp->d_name[astr->j] && pattern[astr->k])
	{
		tmp_k = astr->k;
		tmp_j = astr->j;
		while (1)
		{
			++(astr->k);
			++(astr->j);
			if (pattern[astr->k] == '*' || (pattern[astr->k] == 0
					&& astr->cmp->d_name[astr->j] == 0))
				break ;
			if (pattern[astr->k] != astr->cmp->d_name[astr->j])
			{
				astr->k = tmp_k;
				astr->j = tmp_j;
				break ;
			}
		}
	}
	return (1);
}

static void	compare_matches(t_aster *astr, char *pattern, char ***ret)
{
	astr->cmp = readdir(astr->dir);
	while (astr->cmp)
	{
		astr->k = 0;
		astr->j = 0;
		while (1)
		{
			if ((pattern[0] != '*' && pattern[0] != astr->cmp->d_name[0])
				|| (astr->cmp->d_name[0] == '.' && pattern[0] != '.'))
				break ;
			search_half_matches(pattern, astr);
			if (pattern[astr->k] == '*')
				astr->k++;
			else if (pattern[astr->k] == 0)
			{
				*ret = upd_matches(astr, *ret);
				break ;
			}
			else if (astr->cmp->d_name[astr->j] == 0)
				break ;
			else
				astr->j++;
		}
		astr->cmp = readdir(astr->dir);
	}
}

static char	**search_matches(t_shell *minishell, int *i, t_aster	*astr)
{
	char	**ret;
	char	*pattern;

	pattern = ft_substr(minishell->input, 0, *i);
	if (pattern[0] == '/')
		return (lonely_pattern(pattern, astr));
	ret = NULL;
	astr->dir = opendir(ft_getenv_value(minishell->environment, "PWD"));
	if (astr->dir != NULL)
	{
		compare_matches(astr, pattern, &ret);
		closedir(astr->dir);
	}
	if (ret == NULL)
		return (lonely_pattern(pattern, astr));
	free(pattern);
	return (ret);
}

void	split_into_asterisk(t_shell *minishell, int *i)
{
	int			k;
	int			j;
	char		**tmp;
	char		**tmp_cards;
	t_aster		astr;

	astr = create_astr();
	tmp_cards = search_matches(minishell, i, &astr);
	k = -1;
	j = 0;
	minishell->apps->argc += astr.argc;
	tmp = (char **)malloc(sizeof(char *) * (minishell->apps->argc + 1));
	while (minishell->apps->argv != NULL && minishell->apps->argv[++k] != NULL)
		tmp[k] = minishell->apps->argv[k];
	while (tmp_cards != NULL && tmp_cards[j] != NULL)
		tmp[k++] = tmp_cards[j++];
	tmp[k] = NULL;
	if (minishell->apps->argv != NULL)
		free(minishell->apps->argv);
	if (tmp_cards != NULL)
		free(tmp_cards);
	minishell->apps->token = 0;
	minishell->apps->argv = tmp;
}
