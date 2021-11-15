/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:37:20 by prochell          #+#    #+#             */
/*   Updated: 2021/11/13 21:02:58 by signacia         ###   ########.fr       */
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
	return ;
}

void	cntrl_c2(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	errno = 1;
	return ;
}

void	base_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, cntrl_c);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	input_eof(void)
{
	write(2, "exit\n", 5);
	exit(0);
}
