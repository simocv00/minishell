/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-t_cmd_syntax_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:13:27 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 15:22:13 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_parsing_helper(t_shelldata *shelldata, t_cmds **list, int *pcount,
		int *cflag)
{
	if ((*list)->type == C_PARENTHES)
	{
		if (c_parenthes_checker(*list, pcount, cflag) < 0)
			return (-1);
	}
	else if ((*list)->type == WORD && *cflag == 1)
		return ((error_message((*list)->str), -1));
	else if (is_type_operation((*list)->type))
	{
		if (operations_checker(*list, cflag) < 0)
			return (-1);
	}
	else if ((*list)->type == O_PARENTHES)
	{
		if (o_parenthes_checker(*list, pcount) < 0)
			return (-1);
	}
	else if (is_type_redirection((*list)->type))
	{
		if (redirection_checker(shelldata, list) < 0)
			return (-1);
	}
	return (1);
}

int	check_parsing(t_shelldata *shelldata)
{
	t_cmds	*list;
	int		pcount;
	int		cflag;

	pcount = 0;
	cflag = 0;
	list = shelldata->cmd;
	while (list)
	{
		if (check_parsing_helper(shelldata, &list, &pcount, &cflag) < 0)
			return (-1);
		if (list)
			list = list->next;
		else
			list = shelldata->cmd;
	}
	if (pcount != 0)
		return ((error_message("("), -1));
	return (1);
}
