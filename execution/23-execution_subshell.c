/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23-execution_subshell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <melayyad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:26:21 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 21:59:27 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_subshell_word_case(t_shelldata *shelldata, t_minishell *shell)
{
	if (!shell->args_extracted)
	{
		extract_clean_args(shelldata, shell);
		if (shelldata->state < 0)
			mini_exit(-shelldata->state);
	}
	if (!shell->args || !shell->args[0])
		mini_exit(0);
	else if (builtin_check(shell->args))
		(shelldata->exit_status = execute_built_in(shelldata, shell),
			mini_exit(shelldata->exit_status));
	else
		shell->path = extract_path(shelldata, shell->args[0]);
	if (shell->path)
	{
		extract_execve_env(shelldata, shell);
		if (shelldata->state < 0)
			mini_exit(-shelldata->state);
		if (execve(shell->path, shell->args, shell->env) < 0)
			mini_exit((perror("execve"), 1));
	}
	if (shelldata->state < 0)
		mini_exit(-shelldata->state);
	mini_exit(shelldata->exit_status);
}

void	execute_subshell_helper(t_shelldata *shelldata, t_minishell *shell)
{
	shelldata->lvl++;
	signal(SIGQUIT, shelldata->sigquit_h);
	signal(SIGINT, shelldata->sigint_h);
	manage_data_flow(shelldata, shell);
	if (shelldata->state < 0)
		mini_exit(-shelldata->state);
	if (shell->type == WORD)
		execute_subshell_word_case(shelldata, shell);
	else if (shell->type == C_CMD)
	{
		signal(SIGINT, sig_handler2);
		shelldata->exit_status = execute_and_or(shelldata, shell->c_cmd);
		if (g_sigint == 2)
			mini_exit(130);
		else
			mini_exit(shelldata->exit_status);
	}
	else if (shell->type == NONE)
		mini_exit(0);
}

int	execute_subshell(t_shelldata *shelldata, t_minishell *shell)
{
	if (!shelldata->lvl)
		signal(SIGINT, SIG_IGN);
	while (shell)
	{
		if (shell->next && shell->next->type == PIPE)
			if (pipe(shell->next->pipefd) < 0)
				break ;
		shell->pid = fork();
		if (shell->pid == -1)
			break ;
		if (shell->pid == 0)
		{
			if (shell->next && shell->next->type == PIPE)
				close(shell->next->pipefd[0]);
			execute_subshell_helper(shelldata, shell);
		}
		close_pipes(shell);
		if (shell->next && shell->next->type == PIPE)
			skip_to_next_command(&shell, PIPE);
		else if (!shell->next || shell->next->type == AND
			|| shell->next->type == OR)
			break ;
	}
	return (wiat_for_children(shell));
}
