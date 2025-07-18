/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-t_cmd_syntax_error_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:35:05 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/08 09:56:07 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	destroy_t_cmd_list(t_cmds *list)
{
	if (list->str)
		free(list->str);
	free(list);
}

int	c_parenthes_checker(t_cmds *list, int *pcount, int *cflag)
{
	(*pcount)--;
	if (*cflag == 0)
		*cflag = 1;
	if ((*pcount) < 0)
		return ((error_message(list->str), -1));
	if (list->next && list->next->type == O_PARENTHES)
		return ((error_message(list->next->str), -1));
	return (1);
}

int	operations_checker(t_cmds *list, int *cflag)
{
	if (!list->next)
		return ((error_message(list->str), -1));
	if (*cflag == 1)
		*cflag = 0;
	if (is_type_operation(list->type) && !list->previous)
		return ((error_message(list->str), -1));
	if (is_type_operation(list->type) && list->next
		&& is_type_operation(list->next->type))
		return ((error_message(list->next->str), -1));
	if (is_type_operation(list->type) && list->next
		&& list->next->type == C_PARENTHES)
		return ((error_message(list->next->str), -1));
	return (1);
}

int	o_parenthes_checker(t_cmds *list, int *pcount)
{
	if (!list->next)
		return ((error_message("newline"), -1));
	(*pcount)++;
	if (list->next && (is_type_operation(list->next->type)
			|| list->next->type == C_PARENTHES))
		return ((error_message(list->next->str), -1));
	if (list->previous && !is_type_operation(list->previous->type)
		&& list->previous->type != O_PARENTHES)
		return ((error_message(list->str), -1));
	return (1);
}

int	redirection_checker(t_shelldata *shelldata, t_cmds **list)
{
	t_cmds	*tmp;

	if (!(*list)->next)
		return ((error_message("newline"), -1));
	if (is_type_symbole((*list)->next->type))
		return ((error_message((*list)->next->str), -1));
	if ((*list)->type == HEREDOC)
	{
		(*list)->next->herdocfd = fill_herefoc((*list)->next->str, shelldata);
		if (g_sigint == 2 || (*list)->next->herdocfd < 0)
			return (-1);
	}
	if (is_type_redirection((*list)->type))
	{
		(*list)->next->previous = (*list)->previous;
		if ((*list)->previous)
			(*list)->previous->next = (*list)->next;
		else
			shelldata->cmd = (*list)->next;
		tmp = (*list)->previous;
		(destroy_t_cmd_list(*list), (*list) = tmp);
	}
	return (1);
}
