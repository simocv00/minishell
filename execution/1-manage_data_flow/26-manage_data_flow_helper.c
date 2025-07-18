/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26-manage_data_flow_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:11 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 15:46:03 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir	*manage_redirout(t_redir *redir, t_redir *redirout)
{
	if (redirout && redirout->redirfd > 0)
		close(redirout->redirfd);
	if (redir->type == OUTFILE_NAME)
		redir->redirfd = open(redir->redir_name, OUT_FLAG, 0644);
	else if (redir->type == APPEND_NAME)
		redir->redirfd = open(redir->redir_name, APPEND_FLAG, 0644);
	return (redir);
}

t_redir	*manage_redirin(t_redir *redir, t_redir *redirin)
{
	if (redirin && redirin->redirfd > 0)
		close(redirin->redirfd);
	if (redir->type == INFILE_NAME)
		redir->redirfd = open(redir->redir_name, O_RDONLY);
	return (redir);
}

void	dup_redirections(t_shelldata *shelldata, t_redir *redirin,
		t_redir *redirout)
{
	if (redirin && dup2(redirin->redirfd, 0) < 0)
	{
		perror("dup2");
		close(redirin->redirfd);
		if (redirout)
			close(redirout->redirfd);
		return (shelldata->state = -1, (void)0);
	}
	if (redirout && dup2(redirout->redirfd, 1) < 0)
	{
		perror("dup2");
		close(redirout->redirfd);
		if (redirin)
			close(redirin->redirfd);
		return (shelldata->state = -1, (void)0);
	}
}

void	manage_redirections(t_shelldata *shelldata, t_redir *redir)
{
	t_redir	*redirin;
	t_redir	*redirout;

	redirin = NULL;
	redirout = NULL;
	while (redir)
	{
		if (check_ambig(shelldata, redir, redirin, redirout) < 0)
			return ;
		if (redir->type == OUTFILE_NAME || redir->type == APPEND_NAME)
			redirout = manage_redirout(redir, redirout);
		else if (redir->type == INFILE_NAME || redir->type == DELIMITER)
			redirin = manage_redirin(redir, redirin);
		if (redir->redirfd < 0)
			return (shelldata->state = -1, ft_print_join(
					"minishell: ", redir->redir_name, NULL), perror(" "),
				(void)0);
		redir = redir->next;
	}
	if (redirin && redirin->type == DELIMITER)
		if (check_expandable_data(shelldata, redirin) < 0)
			return ;
	dup_redirections(shelldata, redirin, redirout);
}
