/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39-expand_inside_quotes_helper.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:21:51 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/08 14:00:24 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	move_back(char *str, int k)
{
	while (str[k])
	{
		str[k] = str[k + 1];
		k++;
	}
}

void	delete_quotes(char *str, t_sdquotes *sd, t_exp *exp)
{
	if (str[exp->i] == '\'' && sd->dflag == 0)
	{
		sd->scount++;
		move_back(str, exp->i);
		if (sd->dflag == 0 && sd->sflag == 0)
			sd->sflag = 1;
		if (sd->dflag == 0 && sd->sflag == 1 && sd->scount % 2 == 0)
			sd->sflag = 0;
	}
	else if (str[exp->i] == '\"' && sd->sflag == 0)
	{
		sd->dcount++;
		move_back(str, exp->i);
		if (sd->sflag == 0 && sd->dflag == 0)
			sd->dflag = 1;
		if (sd->sflag == 0 && sd->dflag == 1 && sd->dcount % 2 == 0)
			sd->dflag = 0;
	}
}

int	check_expand_condition(char *str, t_sdquotes *sd, int i)
{
	return (str[i] == '$' && sd->sflag == 0 && ((sd->dflag == 1
				&& check_heredoc_noskips(str[i + 1]))
			|| (sd->dflag == 0 && (str[i + 1] == '\''
					|| str[i + 1] == '\"'
					|| check_heredoc_noskips(str[i + 1])))));
}

int	delete_quotes_condition(char *str, t_sdquotes *sd, int i)
{
	return ((str[i] == '\'' && sd->dflag == 0) || (str[i] == '\"'
			&& sd->sflag == 0));
}
