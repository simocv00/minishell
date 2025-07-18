/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   59-ft_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:07 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 14:02:33 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	only_cd(t_shelldata *shelldata, char **cmd, int *ex)
{
	t_env	*home;
	int		status;

	if (cmd[1] != NULL)
		return (*ex = -1, 2);
	home = get_env_str("HOME", shelldata->env);
	status = 0;
	if (!home)
	{
		*ex = 1;
		return (error_messages(1, "HOME not set", NULL));
	}
	else if (!home->value)
		return (*ex = 0, 0);
	status = chdir(home->value);
	if (status == -1)
	{
		*ex = 1;
		return (error_messages(2, strerror(errno), home->value));
	}
	return (*ex = 0, 0);
}

int	minus_option(t_shelldata *shelldata, char **cmd, int *ex)
{
	int		status;
	t_env	*oldpwd;

	if (ft_strcmp("-", cmd[1]) || cmd[2] != NULL)
		return (*ex = -1, 2);
	oldpwd = get_env_str("OLDPWD", shelldata->env);
	status = 0;
	if (!oldpwd)
	{
		*ex = 1;
		return (error_messages(1, "OLDPWD not set", NULL));
	}
	else if (!oldpwd->value)
		return (ft_putstr_fd(1, "\n"), *ex = 0, 0);
	status = chdir(oldpwd->value);
	if (status == -1)
		return (*ex = 1, error_messages(2, strerror(errno), oldpwd->value));
	if (ft_inprint_join(oldpwd->value, "\n", NULL) < 0)
		return (*ex = 1, 1);
	return (*ex = 0, 0);
}

int	special_cases(t_shelldata *shelldata, char **str)
{
	int	done;

	done = -1;
	if (only_cd(shelldata, str, &done) == 1 && done != -1)
		return (1);
	else if (done == -1 && (minus_option(shelldata, str, &done) == 1))
		return (1);
	if (done == 0)
		return (update_oldpwd(shelldata) | update_pwd(shelldata));
	else if (done == 1)
		return (1);
	return (2);
}

int	change_dir(t_shelldata *shelldata, char **str)
{
	int	er;

	er = chdir(str[1]);
	if (er == -1)
		return (error_messages(2, strerror(errno), str[1]));
	return (update_oldpwd(shelldata) | update_pwd(shelldata));
}

int	ft_cd(t_shelldata *shelldata, char **str)
{
	int	status;

	status = -1;
	if (str[1] && str[2])
		return (error_messages(1, "too many arguments", NULL));
	if (str[1] && !str[1][0])
		return (0);
	status = special_cases(shelldata, str);
	if (status == 1)
		return (1);
	else if (status == 0)
		return (0);
	if (change_dir(shelldata, str))
		return (1);
	return (0);
}
