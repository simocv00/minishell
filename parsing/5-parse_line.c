/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-parse_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:31:19 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/10 08:50:56 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_line(t_shelldata *shelldata)
{
	if (split_line(shelldata) < 0)
		return ;
	if (!shelldata->cmd)
		return ;
	if (check_parsing(shelldata) < 0)
	{
		free_shelldata(shelldata, F_CMD, 1);
		if (g_sigint == 2)
		{
			shelldata->exit_status = 130;
			g_sigint = 0;
		}
		else
			shelldata->exit_status = 2;
		return ;
	}
	shelldata->shell = extract_minishell_cmd(shelldata->cmd);
	if (!shelldata->shell)
		mini_exit(2);
	free_shelldata(shelldata, F_CMD, 0);
}
