/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15-t_minishell_extraction.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:16:20 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/03 13:00:55 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	extract_minishell_cmd_operation_case(t_cmds **xarg, t_data **data,
		t_minishell **shell, t_type *type)
{
	if (t_cmd_addback_data(shell, *data, *type) < 0)
		return (-1);
	(free(*data), *data = init_data(), *type = NONE);
	if (t_cmd_addback_operation(shell, (*xarg)->type) < 0)
		return (-1);
	return (1);
}

int	extract_minishell_cmd_cases(t_cmds **xarg, t_data **data,
		t_minishell **shell, t_type *type)
{
	if (is_indata((*xarg)->type) && t_cmd_addback_redir_data(*data, *xarg) < 0)
		return (-1);
	else if (is_outdata((*xarg)->type) && t_cmd_addback_redir_data(*data,
			*xarg) < 0)
		return (-1);
	else if ((*xarg)->type == WORD)
	{
		*type = WORD;
		if (t_cmd_addback_word(*data, *xarg) < 0)
			return (-1);
	}
	else if ((*xarg)->type == O_PARENTHES)
	{
		*type = C_CMD;
		(*xarg) = (*xarg)->next;
		(*data)->c_cmd = extract_minishell_cmd_helper(xarg);
		if (!(*data)->c_cmd)
			return (-1);
	}
	else if (is_type_operation((*xarg)->type))
		if (extract_minishell_cmd_operation_case(xarg, data, shell, type) < 0)
			return (-1);
	return (1);
}

t_minishell	*extract_minishell_cmd_helper(t_cmds **xarg)
{
	t_minishell	*shell;
	t_data		*data;
	t_type		type;

	shell = NULL;
	type = NONE;
	data = init_data();
	if (!data)
		return (NULL);
	while (*xarg)
	{
		if (is_indata((*xarg)->type) || is_outdata((*xarg)->type)
			|| (*xarg)->type == WORD || (*xarg)->type == O_PARENTHES
			|| is_type_operation((*xarg)->type))
		{
			if (extract_minishell_cmd_cases(xarg, &data, &shell, &type) < 0)
				return (free_data(data), free_minishell(shell), NULL);
		}
		else if ((*xarg)->type == C_PARENTHES)
			break ;
		(*xarg) = (*xarg)->next;
	}
	if (t_cmd_addback_data(&shell, data, type) < 0)
		return (free_data(data), free_minishell(shell), NULL);
	return (free(data), shell);
}

t_minishell	*extract_minishell_cmd(t_cmds *cmd)
{
	t_cmds	**xarg;

	xarg = &cmd;
	return (extract_minishell_cmd_helper(xarg));
}
