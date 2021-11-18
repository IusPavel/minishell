/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:37:20 by prochell          #+#    #+#             */
/*   Updated: 2021/11/18 19:25:17 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cntrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	errno = 1;
}

void	cntrl_c2(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	cntrl_backslash(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 8);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	base_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, cntrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, cntrl_c2);
		signal(SIGQUIT, cntrl_backslash);
	}
}

void	input_eof(void)
{
	write(2, "exit\n", 5);
	exit(0);
}
