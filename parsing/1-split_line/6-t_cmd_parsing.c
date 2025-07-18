/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-t_cmd_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:21:25 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/05 16:33:30 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	select_quoted_word(t_shelldata *shelldata, int i, char q)
{
	int	d;
	int	j;

	d = 0;
	j = 0;
	while (shelldata->line[i + j] && (shelldata->line[i + j] == q || d
			% 2 == 1))
	{
		if (shelldata->line[i + j] == q)
			d++;
		j++;
	}
	if (d % 2 == 1 && shelldata->line[i + j] == '\0')
	{
		if (q == '\'')
			return (shelldata->exit_status = 2, error_message("\'"), -1);
		else
			return (shelldata->exit_status = 2, error_message("\""), -1);
	}
	return (j);
}

int	select_word(t_shelldata *shelldata, int i)
{
	int	j;
	int	k;

	j = 0;
	while ((shelldata->line[i + j] && !is_skippable(shelldata->line[i + j]))
		|| (shelldata->line[i + j] == '&' && shelldata->line[i + j + 1] != '&'))
	{
		if (shelldata->line[i + j] == '\'' || shelldata->line[i + j] == '\"')
		{
			k = select_quoted_word(shelldata, i + j, shelldata->line[i + j]);
			if (k < 0)
				return (k);
			j += k;
		}
		else
			j++;
	}
	return (j);
}

int	operations_case(t_shelldata *shelldata, t_cmdsplit *split)
{
	return (is_operation(shelldata->line[split->i])
		|| (shelldata->line[split->i] == '&' && shelldata->line[split->i
				+ 1] == '&') || is_parenthesis(shelldata->line[split->i]));
}

int	split_line_cases(t_shelldata *shelldata, t_cmdsplit *split)
{
	if (is_white_spaces(shelldata->line[split->i]))
		split->j++;
	else if (operations_case(shelldata, split))
	{
		if (!is_parenthesis(shelldata->line[split->i])
			&& shelldata->line[split->i] == shelldata->line[split->i + 1])
			++split->j;
		if (t_cmd_addback(shelldata, ft_substr(shelldata->line, split->i,
					++split->j)) < 0)
			mini_exit((perror("malloc"), 2));
	}
	else
	{
		split->j = select_word(shelldata, split->i);
		if (split->j < 0)
			return (-1);
		if (t_cmd_addback(shelldata, ft_substr(shelldata->line, split->i,
					split->j)) < 0)
			mini_exit((perror("malloc"), 2));
	}
	return (1);
}

int	split_line(t_shelldata *shelldata)
{
	t_cmdsplit	split;

	split.i = 0;
	while (shelldata->line[split.i])
	{
		split.j = 0;
		if (split_line_cases(shelldata, &split) < 0)
			return (free_shelldata(shelldata, F_LINE | F_CMD, 0), -1);
		split.i += split.j;
	}
	return (free_shelldata(shelldata, F_LINE, 0), 1);
}
