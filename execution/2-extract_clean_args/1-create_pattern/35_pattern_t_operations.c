/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35_pattern_t_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:30:23 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 20:52:27 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*pattern_t_str(t_pattern *list)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (list)
	{
		if (str)
			tmp = ft_strjoin(str, list->str);
		else
			tmp = ft_strdup(list->str);
		if (str)
			free(str);
		str = tmp;
		list = list->next;
	}
	return (str);
}

void	destroy_pattern_t_node(t_pattern *list)
{
	if (list->str)
		free(list->str);
	free(list);
}

void	free_pattern_t(t_pattern *list)
{
	t_pattern	*tmp;

	while (list)
	{
		tmp = list->next;
		destroy_pattern_t_node(list);
		list = tmp;
	}
}

t_pattern	*new_pattern(char *str, t_type type)
{
	t_pattern	*new;

	new = malloc(sizeof(t_pattern));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

int	add_back_pattern(t_pattern **list, char *str, t_type type)
{
	t_pattern	*n;
	t_pattern	*new;

	new = new_pattern(str, type);
	if (!list || !new)
		return (-1);
	if (!*list)
	{
		*list = new;
		return (1);
	}
	n = *list;
	while (n->next)
		n = n->next;
	n->next = new;
	return (1);
}
