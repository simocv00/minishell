/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   55-ft_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:00:21 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 10:58:49 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_shelldata *shelldata)
{
	char	*value;

	if (shelldata->cwd)
		return (ft_inprint_join(shelldata->cwd, "\n", NULL), 0);
	value = getcwd(NULL, 0);
	if (value != NULL)
	{
		ft_inprint_join(value, "\n", NULL);
		free(value);
		return (0);
	}
	perror("pwd: error retrieving current directory: getcwd:"
		" cannot access parent directories: ");
	return (1);
}
