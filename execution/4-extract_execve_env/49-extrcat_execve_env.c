/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   47-extrcat_execve_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:10:53 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/03 23:25:37 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_length(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	extract_execve_env(t_shelldata *shelldata, t_minishell *shell)
{
	int		i;
	t_env	*env;
	int		env_len;

	i = 0;
	env_len = env_length(shelldata->env);
	shell->env = (char **)ft_calloc(env_len + 1, sizeof(char *));
	if (!shell->env)
		return (shelldata->state = -2, (void)0);
	env = shelldata->env;
	while (env)
	{
		shell->env[i] = ft_sthreecat(env->variable, "=", env->value);
		if (!shell->env[i])
			return (free_strs(shell->env), shelldata->state = -2, (void)0);
		i++;
		env = env->next;
	}
}
