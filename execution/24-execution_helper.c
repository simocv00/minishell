/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24-execution_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:10:00 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 13:51:13 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes(t_minishell *shell)
{
	if (shell->previous && shell->previous->type == PIPE)
		(close(shell->previous->pipefd[0]), shell->previous->pipefd[0] = -1);
	if (shell->next && shell->next->type == PIPE)
		(close(shell->next->pipefd[1]), shell->next->pipefd[1] = -1);
}

int	wiat_for_children(t_minishell *shell)
{
	int	status;

	if (shell->pid < 0)
		return (kill_children(shell), 1);
	waitpid(shell->pid, &status, WUNTRACED);
	shell = shell->previous;
	while (shell && shell->type != AND && shell->type != OR)
	{
		if ((shell->type == WORD || shell->type == C_CMD) && shell->pid > 0)
			waitpid(shell->pid, NULL, WUNTRACED);
		shell = shell->previous;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			ft_putstr_fd(2, "Quit (core dumped)\n");
		if (WTERMSIG(status) == 2)
			ft_putstr_fd(1, "\n");
		return (128 + WTERMSIG(status));
	}
	else
		return (1);
}

t_minishell	*shell_tail(t_minishell *shell)
{
	if (!shell)
		return (NULL);
	while (shell->next)
		shell = shell->next;
	return (shell);
}

void	kill_children(t_minishell *shell)
{
	while (shell)
	{
		if (shell->type == WORD)
		{
			if (shell->c_cmd)
				kill_children(shell_tail(shell->c_cmd));
			if (shell->pid > 0)
				kill(shell->pid, SIGKILL);
		}
		shell = shell->previous;
	}
}

void	skip_to_next_command(t_minishell **cmd, t_type type)
{
	while ((*cmd) && (*cmd)->type != type)
		*cmd = (*cmd)->next;
	if (*cmd)
		*cmd = (*cmd)->next;
}
