/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   58-ft_export_helper_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:45:22 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 14:18:31 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_env_helper(t_env *env)
{
	char	*env_list_i;
	char	*tmp;

	if (!env->ev_hide)
	{
		tmp = ft_sthreecat("\"", env->value, "\"");
		if (!tmp)
			return (NULL);
		env_list_i = ft_sthreecat(env->variable, "=", tmp);
		free(tmp);
	}
	else
		env_list_i = ft_strdup(env->variable);
	return (env_list_i);
}

char	**extract_env(t_shelldata *shelldata, t_env *env)
{
	int		i;
	int		env_len;
	char	**env_list;

	i = 0;
	env_len = env_length(env);
	env_list = (char **)ft_calloc(env_len + 1, sizeof(char *));
	if (!env_list)
		return (perror("malloc"), shelldata->state = -2, NULL);
	while (env)
	{
		env_list[i] = extract_env_helper(env);
		if (!env_list[i])
			return (perror("malloc"), free_strs(env_list),
				shelldata->state = -2, NULL);
		i++;
		env = env->next;
	}
	return (env_list);
}

void	sort_envlist(char **env_list)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_list[i])
	{
		j = i + 1;
		while (env_list[j])
		{
			if (ft_strcmp(env_list[i], env_list[j]) > 0)
			{
				tmp = env_list[i];
				env_list[i] = env_list[j];
				env_list[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env(t_shelldata *shelldata, t_env *list)
{
	int		i;
	char	**env_list;

	if (!list)
		return ;
	env_list = extract_env(shelldata, list);
	if (!env_list || !env_list[0])
		return (free(env_list), (void)0);
	sort_envlist(env_list);
	i = 0;
	while (env_list[i])
	{
		if (ft_strncmp("_=", env_list[i], 2))
		{
			if (ft_inprint_join("declare -x ", env_list[i], "\n") < 0)
				break ;
		}
		i++;
	}
	free_strs(env_list);
}
