/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25-manage_data_flow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <melayyad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 09:52:35 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 21:59:38 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	manage_pipe_flow(t_shelldata *shelldata, t_minishell *shell)
{
	if (shell->next && shell->next->type == PIPE)
	{
		if (dup2(shell->next->pipefd[1], 1) < 0)
			return (shelldata->state = -1, perror("dup"), (void)0);
		close(shell->next->pipefd[1]);
	}
	if (shell->previous && shell->previous->type == PIPE)
	{
		if (dup2(shell->previous->pipefd[0], 0) < 0)
			return (shelldata->state = -1, perror("dup"), (void)0);
		close(shell->previous->pipefd[0]);
	}
}

void	manage_data_flow(t_shelldata *shelldata, t_minishell *shell)
{
	t_redir	*redir;

	redir = shell->redir;
	manage_pipe_flow(shelldata, shell);
	if (shelldata->state < 0)
		return ;
	if (redir)
		manage_redirections(shelldata, redir);
}
