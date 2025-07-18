/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   51-ft_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:28:59 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 01:53:31 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_errors_messages(char *value, int type)
{
	if (type == 0)
	{
		ft_print_join("minishell: exit: ", value,
			": numeric argument required\n");
		return (2);
	}
	else if (type == 1)
	{
		ft_putstr_fd(2, "minishell: exit: oo many arguments\n");
		return (1);
	}
	return (2);
}

int	check_exit_args(t_shelldata *shelldata, char **cmd, int *track)
{
	int			flag;
	long long	num;

	if (!cmd[1])
		return ((*track)++, shelldata->exit_status);
	num = 0;
	flag = 0;
	num = ft_atoll(cmd[1], &flag);
	if (ft_numericheck(cmd[1]) || flag == 1)
		return ((*track)++, exit_errors_messages(cmd[1], 0));
	if (cmd[2])
		return (*track = -1, exit_errors_messages(NULL, 1));
	return ((*track)++, num % 256);
}

int	ft_exit(t_shelldata *shelldata, char **args)
{
	int	flag;
	int	status;

	flag = 0;
	if (shelldata->lvl == 0)
		ft_putstr_fd(2, "exit\n");
	status = check_exit_args(shelldata, args, &flag);
	if (flag == 1)
		mini_exit(status);
	else if (flag == -1)
		return (status);
	return (0);
}
