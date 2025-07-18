/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-t_env_set_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:25:11 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/07 22:16:10 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->variable);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*lst_new_env(char *variable, char *value, int ev_h)
{
	t_env	*newelem;

	newelem = malloc(sizeof(t_env));
	if (!newelem)
		return (NULL);
	newelem->variable = variable;
	newelem->value = value;
	newelem->ev_hide = ev_h;
	newelem->next = NULL;
	return (newelem);
}

int	add_back_env(t_shelldata *shelldata, char *variable, char *value, int ev_h)
{
	t_env	*newelem;
	t_env	*n;

	newelem = lst_new_env(variable, value, ev_h);
	if (!shelldata || !newelem)
		return (-1);
	if (!shelldata->env)
	{
		shelldata->env = newelem;
		return (1);
	}
	n = shelldata->env;
	while (n->next)
		n = n->next;
	n->next = newelem;
	return (1);
}

int	set_environment(t_shelldata *shelldata, char **ev)
{
	char	*variable;
	char	*value;
	int		j;
	int		i;

	i = -1;
	while (ev[++i])
	{
		j = ft_chrinstr(ev[i], '=');
		variable = ft_substr(ev[i], 0, j);
		if (!variable)
			return (perror("malloc"), -1);
		if (!ev[i][j + 1])
			value = NULL;
		else
		{
			value = ft_strdup(ev[i] + j + 1);
			if (!value)
				return (perror("malloc"), free(variable), -1);
		}
		if (add_back_env(shelldata, variable, value, 0) < 0)
			return (perror("malloc"), -1);
	}
	return (1);
}
