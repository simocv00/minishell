/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-t_cmd_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:20:22 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 01:48:21 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_white_spaces(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	is_operation(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_parenthesis(char c)
{
	return (c == '(' || c == ')');
}

int	is_skippable(char c)
{
	return (is_white_spaces(c) || is_operation(c) || is_parenthesis(c));
}

void	error_message(char *str)
{
	t_shelldata	*shelldata;

	shelldata = shelldata_memo();
	ft_print_join("minishell: syntax error near unexpected token `",
		str, "'\n");
	if (shelldata->state < 0)
		mini_exit(-shelldata->state);
}
