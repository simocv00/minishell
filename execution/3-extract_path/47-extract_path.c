/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   47-extract_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:25:50 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 15:52:53 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_path_state(t_shelldata *shelldata, char *str, t_pcheck *pcheck)
{
	if (pcheck->path_state == 126)
	{
		shelldata->exit_status = 126;
		ft_print_join("minishell: ", pcheck->p_denied,
			": Permission denied\n");
	}
	else
	{
		shelldata->exit_status = 127;
		ft_print_join(str, ": command not found\n", NULL);
	}
}

char	*check_cmd_in_path(t_shelldata *shelldata, char *str, t_pcheck *pcheck)
{
	while (pcheck->direcs[pcheck->i])
	{
		pcheck->cmd_path = ft_slashjoin(pcheck->direcs[pcheck->i], str);
		if (!pcheck->cmd_path)
		{
			(perror("malloc"), shelldata->state = -2);
			break ;
		}
		if (cmd_path_check(shelldata, pcheck->cmd_path, pcheck))
			break ;
		else if (shelldata->state < 0)
		{
			(free(pcheck->cmd_path), pcheck->cmd_path = NULL);
			break ;
		}
		(free(pcheck->cmd_path), pcheck->cmd_path = NULL);
		pcheck->i++;
	}
	if (!pcheck->cmd_path && shelldata->state >= 0)
		print_path_state(shelldata, str, pcheck);
	free_strs(pcheck->direcs);
	if (pcheck->p_denied)
		free(pcheck->p_denied);
	return (pcheck->cmd_path);
}

char	*extract_path(t_shelldata *shelldata, char *str)
{
	t_pcheck	pcheck;

	pcheck = (t_pcheck){0, 0, NULL, NULL, NULL, NULL};
	if (ft_chrinstr(str, '/') >= 0)
	{
		if (cmd_normal_check(shelldata, str))
		{
			pcheck.cmd_path = ft_strdup(str);
			if (!pcheck.cmd_path)
				return (perror("malloc"), shelldata->state = -2, NULL);
		}
		return (pcheck.cmd_path);
	}
	pcheck.path_value = extract_variable_value("PATH", shelldata->env);
	if (!pcheck.path_value)
	{
		shelldata->state = -127;
		ft_print_join("minishell: ", str,
			": No such file or directory\n");
		return (NULL);
	}
	pcheck.direcs = ft_split(pcheck.path_value, ':');
	if (!pcheck.direcs)
		return (perror("malloc"), shelldata->state = -2, NULL);
	return (check_cmd_in_path(shelldata, str, &pcheck));
}
