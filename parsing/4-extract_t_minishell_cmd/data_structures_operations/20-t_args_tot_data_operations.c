/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19-t_args_tot_data_operations.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:00:43 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 15:29:18 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	destroy_args_node(t_args *args)
{
	if (args->str)
		free(args->str);
	free(args);
}

void	free_args(t_args *args)
{
	t_args	*tmp;

	while (args)
	{
		tmp = args->next;
		destroy_args_node(args);
		args = tmp;
	}
}

t_args	*ft_lstnew_word(t_cmds *xarg)
{
	t_args	*newelem;

	newelem = (t_args *)malloc(sizeof(t_args));
	if (!newelem)
		return (NULL);
	newelem->str = ft_strdup(xarg->str);
	if (!newelem->str)
		return (free(newelem), NULL);
	newelem->next = NULL;
	newelem->is_cmd = 0;
	return (newelem);
}

int	t_cmd_addback_word(t_data *lst, t_cmds *xarg)
{
	t_args	*n;
	t_args	*new;

	new = ft_lstnew_word(xarg);
	if (!lst || !new)
		return (-1);
	if (!lst->args)
	{
		lst->args = new;
		new->is_cmd = 1;
		return (1);
	}
	n = lst->args;
	while (n->next)
		n = n->next;
	n->next = new;
	return (1);
}
