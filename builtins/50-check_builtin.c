/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   50-check_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:23:23 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 11:36:42 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_buitin_sample_cond(t_minishell *shell)
{
	return (shell->type == WORD && (((shell->next && (shell->next->type == AND
						|| shell->next->type == OR)) || !shell->next))
		&& ((shell->previous && (shell->previous->type == AND
					|| shell->previous->type == OR)) || !shell->previous));
}

int	builtin_check(char **args)
{
	return (!ft_strcmp("echo", args[0]) || !ft_strcmp("cd", args[0])
		|| !ft_strcmp("pwd", args[0]) || !ft_strcmp("export", args[0])
		|| !ft_strcmp("unset", args[0]) || !ft_strcmp("env", args[0])
		|| !ft_strcmp("exit", args[0]));
}

int	execute_built_in(t_shelldata *shelldata, t_minishell *shell)
{
	if (!ft_strcmp("echo", shell->args[0]))
		return (ft_echo(shelldata, shell->args));
	else if (!ft_strcmp("cd", shell->args[0]))
		return (ft_cd(shelldata, shell->args));
	else if (!ft_strcmp("pwd", shell->args[0]))
		return (ft_pwd(shelldata));
	else if (!ft_strcmp("export", shell->args[0]))
		return (ft_export(shelldata, shell->args));
	else if (!ft_strcmp("unset", shell->args[0]))
		return (ft_unset(shelldata, shell->args));
	else if (!ft_strcmp("env", shell->args[0]))
		return (ft_env(shelldata, shelldata->env));
	else
		return (ft_exit(shelldata, shell->args));
}
