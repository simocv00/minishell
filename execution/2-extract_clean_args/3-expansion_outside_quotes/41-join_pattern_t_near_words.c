/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39-join_pattern_t_near_words.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:05:38 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 15:52:30 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	consecutive_words_case(t_pattern **list, t_pattern *prev)
{
	char	*str;

	str = ft_strjoin(prev->str, (*list)->str);
	if (!str)
		return (-1);
	free(prev->str);
	prev->str = str;
	prev->next = (*list)->next;
	destroy_pattern_t_node(*list);
	(*list) = prev;
	return (1);
}

void	space_start_case(t_pattern **pattern, t_pattern **list, t_pattern *prev)
{
	*pattern = (*list)->next;
	destroy_pattern_t_node(*list);
	*list = prev;
}

void	space_last_case(t_pattern **list, t_pattern *prev)
{
	prev->next = NULL;
	destroy_pattern_t_node(*list);
	*list = prev;
}

void	join_near_words(t_shelldata *shelldata, t_pattern **pattern)
{
	t_pattern	*prev;
	t_pattern	*list;

	prev = NULL;
	list = *pattern;
	while (list)
	{
		if (list->type == S_PACE && !prev)
			space_start_case(pattern, &list, prev);
		else if (list->type == S_PACE && !list->next)
			space_last_case(&list, prev);
		else if (list->type == WORD && prev && prev->type == WORD)
		{
			if (consecutive_words_case(&list, prev) < 0)
				return (shelldata->state = -2, (void)0);
		}
		prev = list;
		if (list)
			list = list->next;
		else
			list = *pattern;
	}
}
