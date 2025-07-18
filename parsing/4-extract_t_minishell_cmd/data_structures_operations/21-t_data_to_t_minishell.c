/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21-t_data_to_t_minishell.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:00:56 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 15:59:19 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_minishell(t_minishell *minishell)
{
	t_minishell	*tmp;

	while (minishell)
	{
		tmp = minishell->next;
		if (minishell->args_list)
			(free_args(minishell->args_list), minishell->args_list = NULL);
		if (minishell->redir)
			(free_redir(minishell->redir), minishell->redir = NULL);
		if (minishell->c_cmd)
			(free_minishell(minishell->c_cmd), minishell->c_cmd = NULL);
		if (minishell->args)
			(free_strs(minishell->args), minishell->args = NULL);
		if (minishell->env)
			(free_strs(minishell->env), minishell->env = NULL);
		if (minishell->path)
			(free(minishell->path), minishell->path = NULL);
		free(minishell);
		minishell = tmp;
	}
}

t_minishell	*ft_lstnew_operation(t_type type)
{
	t_minishell	*newelem;

	newelem = (t_minishell *)malloc(sizeof(t_minishell));
	if (!newelem)
		return (NULL);
	newelem->type = type;
	newelem->pid = -1;
	newelem->args_extracted = 0;
	newelem->exp_split = 0;
	newelem->path = NULL;
	newelem->c_cmd = NULL;
	newelem->redir = NULL;
	newelem->args = NULL;
	newelem->env = NULL;
	newelem->args_list = NULL;
	newelem->next = NULL;
	newelem->previous = NULL;
	return (newelem);
}

int	t_cmd_addback_operation(t_minishell **lst, t_type type)
{
	t_minishell	*n;
	t_minishell	*new;

	new = ft_lstnew_operation(type);
	if (!lst || !new)
		return (-1);
	if (!(*lst))
	{
		*lst = new;
		return (1);
	}
	n = *lst;
	while (n->next)
		n = n->next;
	n->next = new;
	new->previous = n;
	return (1);
}

t_minishell	*ft_lstnew_cmd_data(t_data *data, t_type type)
{
	t_minishell	*newelem;

	newelem = (t_minishell *)malloc(sizeof(t_minishell));
	if (!newelem || !data)
		return (NULL);
	newelem->type = type;
	newelem->path = NULL;
	if (type == C_CMD)
	{
		newelem->c_cmd = data->c_cmd;
		newelem->args_list = NULL;
	}
	else
	{
		newelem->c_cmd = NULL;
		newelem->args_list = data->args;
	}
	newelem->redir = data->redir;
	newelem->pid = -1;
	newelem->args_extracted = 0;
	newelem->exp_split = 0;
	newelem->next = NULL;
	newelem->env = NULL;
	newelem->args = NULL;
	return (newelem->previous = NULL, newelem);
}

int	t_cmd_addback_data(t_minishell **lst, t_data *data, t_type type)
{
	t_minishell	*n;
	t_minishell	*new;

	new = ft_lstnew_cmd_data(data, type);
	if (!lst || !new)
		return (-1);
	if (!(*lst))
	{
		*lst = new;
		return (1);
	}
	n = *lst;
	while (n->next)
		n = n->next;
	n->next = new;
	new->previous = n;
	return (1);
}
