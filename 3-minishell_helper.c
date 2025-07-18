/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-minishell_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:21:25 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 12:25:51 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_readline_msg(t_shelldata *shelldata)
{
	if (errno == 0)
		(ft_putstr_fd(2, "exit\n"), mini_exit(shelldata->exit_status));
	else if (errno == EAGAIN)
		perror("minishell: readline: ");
	else if (errno == ENOMEM)
	{
		perror("minishell: readline: ");
		mini_exit(2);
	}
	else if (errno == EIO)
	{
		perror("minishell: readline: ");
		mini_exit(1);
	}
}

void	interactive_non_interactive(t_shelldata *shelldata)
{
	if (isatty(0))
	{
		signal(SIGINT, sig_handler1);
		signal(SIGQUIT, SIG_IGN);
		shelldata->line = readline(prompt_mini(shelldata));
		if (!shelldata->line)
			print_readline_msg(shelldata);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		shelldata->line = get_next_line(shelldata, 0);
		if (!shelldata->line)
		{
			if (shelldata->state < 0)
				mini_exit(0);
			mini_exit(shelldata->exit_status);
		}
	}
	if (g_sigint == 2)
	{
		shelldata->exit_status = 130;
		g_sigint = 0;
	}
}

void	init_shelldata(t_shelldata *shelldata)
{
	shelldata->env = NULL;
	shelldata->cmd = NULL;
	shelldata->shell = NULL;
	shelldata->line = NULL;
	shelldata->sigint_h = signal(SIGINT, sig_handler1);
	shelldata->sigquit_h = signal(SIGQUIT, SIG_IGN);
	shelldata->state = 0;
	shelldata->std_incpy = -1;
	shelldata->std_outcpy = -1;
	shelldata->lvl = 0;
	shelldata->exit_status = 0;
	shelldata->cwd = getcwd(NULL, 0);
	if (!shelldata->cwd)
		perror("shell-init: error retrieving current directory: getcwd: "
			"cannot access parent directories: ");
}

void	free_shelldata(t_shelldata *shelldata, int flag, int hflag)
{
	if (shelldata->env && (flag >> 0 & 1))
		(free_env(shelldata->env), shelldata->env = NULL);
	if (shelldata->line && (flag >> 1 & 1))
	{
		free(shelldata->line);
		shelldata->line = NULL;
	}
	if (shelldata->cmd && (flag >> 2 & 1))
	{
		free_t_cmds(shelldata->cmd, hflag);
		shelldata->cmd = NULL;
	}
	if (shelldata->shell && (flag >> 3 & 1))
	{
		free_minishell(shelldata->shell);
		shelldata->shell = NULL;
	}
	if (shelldata->cwd && (flag >> 0 & 1))
		(free(shelldata->cwd), shelldata->cwd = NULL);
	if (shelldata->std_incpy >= 0)
		close(shelldata->std_incpy);
	if (shelldata->std_outcpy >= 0)
		close(shelldata->std_outcpy);
}

void	mini_exit(int status)
{
	t_shelldata	*shelldata;

	shelldata = shelldata_memo();
	free_shelldata(shelldata, F_LINE | F_CMD | F_SHELL | F_ENV, 1);
	clear_history();
	exit(status);
}
