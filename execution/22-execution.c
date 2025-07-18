/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22-execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <melayyad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:57:53 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 21:59:23 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dup(int fd)
{
	int	*fd_check;
	int	dup_fd;
	int	i;

	fd_check = (int [3]){-1, -1, -1};
	dup_fd = dup(fd);
	i = 0;
	while (dup_fd <= 2)
	{
		if (dup_fd == -1)
			break ;
		else if (dup_fd <= 2)
			fd_check[i++] = dup_fd;
		dup_fd = dup(fd);
	}
	while (--i >= 0)
		close(fd_check[i]);
	return (dup_fd);
}

void	execute_buitl_in_command(t_shelldata *shelldata, t_minishell *shell)
{
	shelldata->std_outcpy = ft_dup(1);
	shelldata->std_incpy = ft_dup(0);
	manage_data_flow(shelldata, shell);
	if (shelldata->state == -1)
	{
		shelldata->state = 0;
		shelldata->exit_status = 1;
	}
	else if (shelldata->state == -2)
		mini_exit(-shelldata->state);
	else
	{
		shelldata->exit_status = execute_built_in(shelldata, shell);
		if (shelldata->state < 0)
			mini_exit(-shelldata->state);
	}
	dup2(shelldata->std_incpy, 0);
	dup2(shelldata->std_outcpy, 1);
	if (shelldata->std_incpy >= 0)
		(close(shelldata->std_incpy), shelldata->std_incpy = -1);
	if (shelldata->std_outcpy >= 0)
		(close(shelldata->std_outcpy), shelldata->std_outcpy = -1);
}

int	execute_and_or(t_shelldata *shelldata, t_minishell *shell)
{
	while (shell)
	{
		if (check_buitin_sample_cond(shell))
		{
			extract_clean_args(shelldata, shell);
			if (shelldata->state < 0)
				mini_exit(-shelldata->state);
			if (shell->args && builtin_check(shell->args))
				execute_buitl_in_command(shelldata, shell);
			else
				shelldata->exit_status = execute_subshell(shelldata, shell);
		}
		else
			shelldata->exit_status = execute_subshell(shelldata, shell);
		if (shelldata->exit_status == 130 && !shelldata->lvl)
			return (130);
		if (!shelldata->exit_status)
			skip_to_next_command(&shell, AND);
		else
			skip_to_next_command(&shell, OR);
	}
	return (shelldata->exit_status);
}

void	execute_cmd(t_shelldata *shelldata)
{
	t_minishell	*shell;

	shell = shelldata->shell;
	execute_and_or(shelldata, shell);
}
