/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42-extract_pattern_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:53:21 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 21:13:03 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_pattern_list	*create_new_pattern(t_pattern **list, t_type type)
{
	t_pattern		*prev;
	t_pattern_list	*new_pattern;

	new_pattern = malloc(sizeof(t_pattern_list));
	if (!new_pattern)
		return (NULL);
	new_pattern->is_cmd = 0;
	new_pattern->is_wildcard = 0;
	new_pattern->next = NULL;
	new_pattern->pattern = NULL;
	if (type == PATTERN)
	{
		new_pattern->type = type;
		new_pattern->pattern = *list;
		while (*list && (*list)->type != S_PACE)
		{
			if ((*list)->type == WILDCARD && !new_pattern->is_wildcard)
				new_pattern->is_wildcard = 1;
			prev = *list;
			*list = (*list)->next;
		}
		prev->next = NULL;
	}
	return (new_pattern);
}

int	add_back_pattern_list(t_pattern_list **pattern_list, t_pattern **list,
		t_type type)
{
	t_pattern_list	*tmp;
	t_pattern_list	*new_pattern;

	new_pattern = create_new_pattern(list, type);
	if (!pattern_list || !new_pattern)
		return (-1);
	if (!*pattern_list)
	{
		*pattern_list = new_pattern;
		return (1);
	}
	tmp = *pattern_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_pattern;
	return (1);
}

t_pattern_list	*create_pattern_list(t_shelldata *shelldata, t_pattern **list)
{
	t_pattern_list	*pattern_list;
	t_pattern		*tmp;

	pattern_list = NULL;
	if (!list)
		return (NULL);
	while (*list)
	{
		if ((*list)->type == WILDCARD || (*list)->type == WORD)
		{
			if (add_back_pattern_list(&pattern_list, list, PATTERN) < 0)
				return (shelldata->state = -2,
					free_pattern_list_t(pattern_list), NULL);
		}
		else if ((*list)->type == S_PACE)
		{
			tmp = (*list)->next;
			destroy_pattern_t_node(*list);
			*list = tmp;
		}
	}
	return (pattern_list);
}
