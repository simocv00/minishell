/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43-add_args_t_in_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:38:24 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 16:43:12 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_args	*create_new_arg(char *str, int is_cmd)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (perror("malloc"), NULL);
	new_arg->str = str;
	new_arg->is_cmd = is_cmd;
	new_arg->next = NULL;
	return (new_arg);
}

int	add_args_word_back(t_args **args_list, char *str, int is_cmd)
{
	t_args	*new_args;
	t_args	*tmp;

	new_args = create_new_arg(str, is_cmd);
	if (!args_list || !new_args)
		return (-1);
	if (!*args_list)
	{
		*args_list = new_args;
		return (1);
	}
	tmp = *args_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_args;
	return (1);
}

void	add_args_node_back(t_args **args_list, t_args *new_args)
{
	t_args	*tmp;

	if (!new_args)
		return ;
	if (!*args_list)
	{
		*args_list = new_args;
		return ;
	}
	tmp = *args_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_args;
}

int	add_args_sorted_helper(t_args **args_list, t_args *tmp, t_args *prev,
		t_args *new_args)
{
	while (tmp)
	{
		if (ft_strcmp(new_args->str, tmp->str) < 0)
		{
			new_args->next = tmp;
			if (!prev)
			{
				*args_list = new_args;
				break ;
			}
			else
			{
				prev->next = new_args;
				break ;
			}
		}
		else if (ft_strcmp(new_args->str, tmp->str) >= 0 && !tmp->next)
		{
			tmp->next = new_args;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	add_args_sorted(t_args **args_list, char *str, int is_cmd)
{
	t_args	*tmp;
	t_args	*prev;
	t_args	*new_args;

	new_args = create_new_arg(str, is_cmd);
	if (!args_list || !new_args)
		return (-1);
	if (!*args_list)
	{
		*args_list = new_args;
		return (1);
	}
	prev = NULL;
	tmp = *args_list;
	return (add_args_sorted_helper(args_list, tmp, prev, new_args));
}
