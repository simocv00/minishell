/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34-create_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:44:54 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 21:12:58 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_pattern_list_t(t_pattern_list *pattern_list)
{
	t_pattern_list	*tmp;

	while (pattern_list)
	{
		tmp = pattern_list->next;
		if (pattern_list->pattern)
			free_pattern_t(pattern_list->pattern);
		free(pattern_list);
		pattern_list = tmp;
	}
}

t_pattern_list	*create_pattern(t_shelldata *shelldata, char *str)
{
	t_pattern_list	*pattern_list;
	t_pattern		*list;

	pattern_list = NULL;
	list = tokenize_string(shelldata, str);
	if (list)
	{
		join_near_words(shelldata, &list);
		if (shelldata->state < 0)
			return (free_pattern_t(list), NULL);
		pattern_list = create_pattern_list(shelldata, &list);
		if (!pattern_list && shelldata->state < 0)
			return (free_pattern_t(list), NULL);
	}
	return (pattern_list);
}
