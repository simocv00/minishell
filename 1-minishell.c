/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:21:25 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 12:25:33 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint;

t_shelldata	*shelldata_memo(void)
{
	static t_shelldata	shelldata;

	return (&shelldata);
}

int	main(int ac, char **av, char **ev)
{
	t_shelldata	*shelldata;

	g_sigint = 0;
	rl_outstream = stderr;
	shelldata = shelldata_memo();
	init_shelldata(shelldata);
	if (ev && ac && av)
		if (set_environment(shelldata, ev) < 0)
			mini_exit(2);
	while (1)
	{
		interactive_non_interactive(shelldata);
		if (shelldata->line)
		{
			if (shelldata->line[0])
			{
				add_history(shelldata->line);
				parse_line(shelldata);
				execute_cmd(shelldata);
			}
			free_shelldata(shelldata, F_SHELL | F_LINE, 0);
		}
	}
	return (0);
}
