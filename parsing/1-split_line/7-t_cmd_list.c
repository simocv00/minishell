/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-t_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:18:20 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/30 14:12:15 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_t_cmds(t_cmds *cmd, int hflag)
{
	t_cmds	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->str)
			free(cmd->str);
		if (cmd->herdocfd >= 0 && hflag)
			close(cmd->herdocfd);
		free(cmd);
		cmd = tmp;
	}
}

t_cmds	*ft_cmd_lstnew(char *content)
{
	t_cmds	*newelem;

	if (!content)
		return (NULL);
	newelem = (t_cmds *)malloc(sizeof(t_cmds));
	if (!newelem)
		return (NULL);
	newelem->type = NONE;
	newelem->next = NULL;
	newelem->herdocfd = -1;
	newelem->str = content;
	newelem->previous = NULL;
	return (newelem);
}

int	t_cmd_addback(t_shelldata *shelldata, char *content)
{
	t_cmds	*n;
	t_cmds	*new;

	new = ft_cmd_lstnew(content);
	if (!shelldata || !new)
		return (-1);
	if (!shelldata->cmd)
	{
		shelldata->cmd = new;
		new->type = check_type(new, content);
		return (1);
	}
	n = shelldata->cmd;
	while (n->next)
		n = n->next;
	n->next = new;
	new->previous = n;
	new->type = check_type(new, content);
	return (1);
}
