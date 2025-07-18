/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-t_cmd_syntax_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:28:30 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 10:32:10 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_type_operation(t_type type)
{
	if (type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

int	is_type_redirection(t_type type)
{
	if (type == INFILE || type == OUTFILE || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_type_file(t_type type)
{
	if (type == INFILE_NAME || type == OUTFILE_NAME || type == APPEND_NAME
		|| type == DELIMITER)
		return (1);
	return (0);
}

int	is_type_parenthesis(t_type type)
{
	if (type == O_PARENTHES || type == C_PARENTHES)
		return (1);
	return (0);
}

int	is_type_symbole(t_type type)
{
	return (is_type_operation(type) || is_type_redirection(type)
		|| is_type_parenthesis(type));
}
