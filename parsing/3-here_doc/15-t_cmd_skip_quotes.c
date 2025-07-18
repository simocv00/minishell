/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-t_cmd_skip_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:21:51 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 15:20:37 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quotes_skipper(char *str, t_sdquotes *sd, int i)
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

int	couted_dollar_signs(char *str, t_eraseq eq)
{
	return ((str[eq.i + 1] != '\'' && str[eq.i + 1] != '\"') || (eq.dollar_c
			% 2 == 0 && (str[eq.i + 1] == '\'' || str[eq.i + 1] == '\"')));
}

void	check_dollarc_value(int *dollar_c)
{
	if (*dollar_c)
		*dollar_c = 0;
}

int	erase_quotes_len(char *str)
{
	t_sdquotes	sd;
	t_eraseq	eq;

	eq = (t_eraseq){0, 0, 0, 0};
	sd = (t_sdquotes){0, 0, 0, 0};
	while (str[eq.i])
	{
		if ((str[eq.i] == '\'' && sd.dflag == 0) || (str[eq.i] == '\"'
				&& sd.sflag == 0))
			(check_dollarc_value(&eq.dollar_c), quotes_skipper(str, &sd, eq.i));
		else if (!sd.sflag && !sd.dflag && str[eq.i] == '$')
		{
			eq.dollar_c++;
			if (couted_dollar_signs(str, eq))
				eq.len++;
		}
		else
			(check_dollarc_value(&eq.dollar_c), eq.len++);
		eq.i++;
	}
	return (eq.len);
}

char	*erase_quotes(char *str)
{
	t_sdquotes	sd;
	t_eraseq	eq;
	char		*s;

	eq = (t_eraseq){0, 0, erase_quotes_len(str), 0};
	s = malloc(eq.len + 1);
	if (!s)
		return (NULL);
	sd = (t_sdquotes){0, 0, 0, 0};
	while (str[eq.i])
	{
		if ((str[eq.i] == '\'' && sd.dflag == 0) || (str[eq.i] == '\"'
				&& sd.sflag == 0))
			(check_dollarc_value(&eq.dollar_c), quotes_skipper(str, &sd, eq.i));
		else if (!sd.sflag && !sd.dflag && str[eq.i] == '$')
		{
			eq.dollar_c++;
			if (couted_dollar_signs(str, eq))
				s[eq.j++] = str[eq.i];
		}
		else
			(check_dollarc_value(&eq.dollar_c), s[eq.j++] = str[eq.i]);
		eq.i++;
	}
	return (s[eq.j] = 0, s);
}
