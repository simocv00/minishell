/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   54-ft_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <melayyad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:26:33 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/13 21:59:02 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env_str(char *str, t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->variable, str) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	free_node_env(t_env *n)
{
	free(n->variable);
	free(n->value);
	free(n);
}

int	destroy_node(t_shelldata *shelldata, char *name)
{
	t_env	*node;
	t_env	*head;

	node = get_env_str(name, shelldata->env);
	if (!node)
		return (0);
	head = shelldata->env;
	if (head != node)
	{
		while (head->next != node)
			head = head->next;
		head->next = node->next;
		free_node_env(node);
	}
	else
	{
		shelldata->env = node->next;
		free_node_env(node);
	}
	return (0);
}

int	ft_unset(t_shelldata *shelldata, char **args)
{
	int	i;

	if (!args[1])
		return (0);
	args++;
	i = 0;
	while (args[i])
	{
		destroy_node(shelldata, args[i]);
		i++;
	}
	return (0);
}
