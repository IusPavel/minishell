/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:37:20 by prochell          #+#    #+#             */
/*   Updated: 2021/11/20 15:02:49 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c2(int sig)
{
	(void)sig;
}

void	ctrl_hered(int sig)
{
	(void)sig;
	rl_done = 1;
}

void	cntrl_backslash(int sig)
{
	(void)sig;
	write(2, "Quit: 3", 7);
}

void	base_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, ctrl_c2);
		signal(SIGQUIT, cntrl_backslash);
	}
}
