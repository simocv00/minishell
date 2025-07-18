/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-t_cmd_type_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:43:11 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 10:32:25 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirection(t_type type)
{
	return (type == APPEND || type == HEREDOC || type == INFILE
		|| type == OUTFILE);
}

t_type	redirection_file_type(t_type type)
{
	if (type == APPEND)
		return (APPEND_NAME);
	else if (type == HEREDOC)
		return (DELIMITER);
	else if (type == INFILE)
		return (INFILE_NAME);
	else
		return (OUTFILE_NAME);
}

t_type	check_type(t_cmds *new, char *str)
{
	if (!ft_strncmp(str, "||", 2))
		return (OR);
	else if (!ft_strncmp(str, "&&", 2))
		return (AND);
	else if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(str, "<", 1))
		return (INFILE);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(str, ">", 1))
		return (OUTFILE);
	else if (!ft_strncmp(str, "(", 1))
		return (O_PARENTHES);
	else if (!ft_strncmp(str, ")", 1))
		return (C_PARENTHES);
	else if (new->previous && is_redirection(new->previous->type))
		return (redirection_file_type(new->previous->type));
	else
		return (WORD);
}
