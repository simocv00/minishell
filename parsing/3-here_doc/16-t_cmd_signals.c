/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14-t_cmd_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:22:39 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/07 18:18:29 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_handler1(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sigint = 2;
}

void	sig_handler2(int sig)
{
	(void)sig;
	g_sigint = 2;
}

void	sig_handler3(int sig)
{
	(void)sig;
	mini_exit(128 + SIGINT);
}

void	sig_heredoc(int sig)
{
	(void)sig;
	destroy_hdoc();
	write(1, "\n", 1);
	exit(128 + SIGINT);
}
