/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   44-check_wild_exp_out_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:44:51 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 10:24:02 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exp_out_quotes(char *str, t_sdquotes sd, int i)
{
	return (str[i] == '$' && sd.sflag == 0 && sd.dflag == 0 && (ft_isalnum(str[i
					+ 1]) || str[i + 1] == '_'));
}

int	check_quotes_flags(char *str, t_sdquotes sd, int i)
{
	return ((str[i] == '\'' && sd.dflag == 0) || (str[i] == '\"'
			&& sd.sflag == 0));
}

void	check_wild_exp_out_quotes_helper(char *str, t_sdquotes *sd, int i)
{
	if (str[i] == '\'' && sd->dflag == 0)
	{
		sd->scount++;
		if (sd->dflag == 0 && sd->sflag == 0)
			sd->sflag = 1;
		if (sd->dflag == 0 && sd->sflag == 1 && sd->scount % 2 == 0)
			sd->sflag = 0;
	}
	else if (str[i] == '\"' && sd->sflag == 0)
	{
		sd->dcount++;
		if (sd->sflag == 0 && sd->dflag == 0)
			sd->dflag = 1;
		if (sd->sflag == 0 && sd->dflag == 1 && sd->dcount % 2 == 0)
			sd->dflag = 0;
	}
}

int	check_wild_exp_out_quotes(char *str)
{
	int			i;
	t_sdquotes	sd;

	i = 0;
	sd = (t_sdquotes){0, 0, 0, 0};
	while (str[i])
	{
		if (check_quotes_flags(str, sd, i))
			check_wild_exp_out_quotes_helper(str, &sd, i);
		else if (str[i] == '*' && sd.sflag == 0 && sd.dflag == 0)
			return (1);
		else if (check_exp_out_quotes(str, sd, i))
			return (1);
		i++;
	}
	return (0);
}
