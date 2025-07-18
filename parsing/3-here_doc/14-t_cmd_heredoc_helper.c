/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14-t_cmd_heredoc_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:59:06 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 01:48:38 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	destroy_hdoc(void)
{
	t_hdocfree	*hdoc;

	hdoc = hdoc_memo();
	free(hdoc->s);
	close(hdoc->fd);
}

t_hdocfree	*hdoc_memo(void)
{
	static t_hdocfree	hdoc;

	return (&hdoc);
}

char	*filepath(void)
{
	int		pid;
	char	*filepath;
	char	*piditoa;

	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		mini_exit(0);
	waitpid(pid, NULL, 0);
	piditoa = ft_itoa(pid);
	if (!piditoa)
		return (NULL);
	filepath = ft_strjoin("/tmp/tmpfileminishell-", piditoa);
	free(piditoa);
	if (!filepath)
		return (NULL);
	return (filepath);
}

void	print_ctrd_msg(char *s)
{
	t_shelldata	*shelldata;

	shelldata = shelldata_memo();
	ft_print_join("minishell: warning: here-document "
		"delimited by end-of-file (wanted '",
		s,
		"')\n");
	if (shelldata->state < 0)
		mini_exit(-shelldata->state);
}
