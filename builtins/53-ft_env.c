/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   53-ft_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:00 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 14:12:36 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_clen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->ev_hide == 0)
			i++;
		env = env->next;
	}
	return (i);
}

char	**extract_cenv(t_shelldata *shelldata, t_env *env)
{
	int		i;
	int		env_len;
	char	**env_list;

	i = 0;
	env_len = env_clen(env);
	env_list = (char **)ft_calloc(env_len + 1, sizeof(char *));
	if (!env_list)
		return (perror("malloc"), shelldata->state = -2, NULL);
	while (env)
	{
		if (env->ev_hide == 0)
		{
			env_list[i] = ft_sthreecat(env->variable, "=", env->value);
			if (!env_list[i])
				return (perror("malloc"), free_strs(env_list),
					shelldata->state = -2, NULL);
			i++;
		}
		env = env->next;
	}
	return (env_list);
}

int	ft_env(t_shelldata *shelldata, t_env *env)
{
	char	*tmp;
	char	*print_env;
	char	**env_list;

	if (!env)
		return (0);
	env_list = extract_cenv(shelldata, env);
	if (!env_list)
		return (1);
	tmp = ft_strsjoin(env_list, '\n');
	free_strs(env_list);
	if (!tmp)
		return (perror("malloc"), shelldata->state = -2, 1);
	print_env = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!print_env)
		return (perror("malloc"), shelldata->state = -2, 1);
	if (ft_putstr_fd(1, print_env) < 0)
		return (free(print_env), 1);
	return (free(print_env), 0);
}
