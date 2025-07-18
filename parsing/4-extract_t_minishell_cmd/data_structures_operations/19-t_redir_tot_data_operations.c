/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16-t_redir_tot_data_operations.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:53:48 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/03 17:27:11 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->redir_name)
			free(redir->redir_name);
		if (redir->redirfd > 0)
			close(redir->redirfd);
		free(redir);
		redir = tmp;
	}
}

t_redir	*ft_lstnew_redir_data(t_cmds *xarg)
{
	t_redir	*newelem;

	newelem = (t_redir *)malloc(sizeof(t_redir));
	if (!newelem)
		return (NULL);
	newelem->type = xarg->type;
	newelem->redir_name = ft_strdup(xarg->str);
	if (!newelem->redir_name)
		return (free(newelem), NULL);
	newelem->redirfd = xarg->herdocfd;
	newelem->next = NULL;
	return (newelem);
}

int	t_cmd_addback_redir_data(t_data *lst, t_cmds *xarg)
{
	t_redir	*n;
	t_redir	*new;

	new = ft_lstnew_redir_data(xarg);
	if (!lst || !new)
		return (-1);
	if (!lst->redir)
	{
		lst->redir = new;
		return (1);
	}
	n = lst->redir;
	while (n->next)
		n = n->next;
	n->next = new;
	return (1);
}
