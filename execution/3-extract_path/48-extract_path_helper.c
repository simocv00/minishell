/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   48-extract_path_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:57:01 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 01:48:04 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_stat_errno(t_shelldata *shelldata, char *str)
{
	if (errno == ENOTDIR)
	{
		shelldata->state = -126;
		ft_print_join("minishell: ", str, ": Not a directory\n");
		shelldata->exit_status = 126;
	}
	else if (errno == ENOENT)
	{
		ft_print_join("minishell: ", str,
			": No such file or directory\n");
		shelldata->exit_status = 127;
	}
	else if (errno == ENOMEM)
	{
		ft_putstr_fd(2, "minishell: Cannot allocate memory\n");
		shelldata->exit_status = 126;
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(2, "minishell: Permission denied\n");
		shelldata->exit_status = 126;
	}
	else
	{
		perror("stat");
		shelldata->exit_status = 126;
	}
}

int	cmd_normal_check(t_shelldata *shelldata, char *str)
{
	struct stat	buf;

	if (stat(str, &buf) == -1)
	{
		check_stat_errno(shelldata, str);
		return (0);
	}
	if (S_ISDIR(buf.st_mode))
	{
		ft_print_join("minishell: ", str, ": Is a directory\n");
		shelldata->exit_status = 126;
		return (0);
	}
	if (access(str, X_OK) == -1)
	{
		ft_print_join("minishell: ", str, ": Permission denied\n");
		shelldata->exit_status = 126;
		return (0);
	}
	return (1);
}

int	cmd_path_check(t_shelldata *shelldata, char *cmd_path, t_pcheck *pcheck)
{
	struct stat	buf;

	if (stat(cmd_path, &buf) == -1)
	{
		if (errno == ENOMEM)
		{
			ft_putstr_fd(2, "minishell: Cannot allocate memory\n");
			shelldata->state = -126;
		}
		return (0);
	}
	if (S_ISDIR(buf.st_mode))
		return (0);
	if (access(cmd_path, X_OK) == -1)
	{
		if (pcheck->path_state != 126)
		{
			pcheck->p_denied = ft_strdup(pcheck->cmd_path);
			if (!pcheck->p_denied)
				return (shelldata->state = -2, 0);
			pcheck->path_state = 126;
		}
		return (0);
	}
	return (1);
}
