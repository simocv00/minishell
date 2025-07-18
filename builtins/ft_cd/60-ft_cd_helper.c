/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60-ft_cd_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:57:25 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 11:54:47 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_messages(int type, char *message, char *file)
{
	char		*tmp;
	t_shelldata	*shelldata;

	shelldata = shelldata_memo();
	if (type == 1)
		ft_print_join("minishell: cd: ", message, "\n");
	else if (type == 2)
	{
		tmp = ft_sthreecat(file, ": ", message);
		if (!tmp)
			return (perror("malloc"), shelldata->state = -2, 1);
		ft_print_join("minishell: cd: ", tmp, "\n");
		free(tmp);
	}
	return (1);
}

void	print_error(void)
{
	perror("cd: error retrieving current directory:"
		"getcwd: cannot access parent directories: ");
}

int	update_pwd(t_shelldata *shelldata)
{
	char	*new_pwd;
	t_env	*env_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (print_error(), 1);
	if (shelldata->cwd)
		(free(shelldata->cwd), shelldata->cwd = NULL);
	shelldata->cwd = ft_strdup(new_pwd);
	if (!shelldata->cwd)
		return (free(new_pwd), shelldata->state = -2, 1);
	env_pwd = get_env_str("PWD", shelldata->env);
	if (!env_pwd)
		return (free(new_pwd), 0);
	env_pwd->ev_hide = 0;
	return (free(env_pwd->value), env_pwd->value = new_pwd, 0);
}

int	update_oldpwd(t_shelldata *shelldata)
{
	t_env	*env_opwd;
	t_env	*env_pwd;
	char	*oldpwd_nvalue;

	env_opwd = get_env_str("OLDPWD", shelldata->env);
	if (!env_opwd)
		return (0);
	env_pwd = get_env_str("PWD", shelldata->env);
	if (!env_pwd)
	{
		(free(env_opwd->value), env_opwd->value = NULL);
		env_opwd->ev_hide = 1;
		return (0);
	}
	if (env_pwd->ev_hide == 0)
		env_opwd->ev_hide = 0;
	if (env_pwd->value)
	{
		oldpwd_nvalue = ft_strdup(env_pwd->value);
		if (!oldpwd_nvalue)
			return (shelldata->state = -2, 1);
	}
	else
		oldpwd_nvalue = NULL;
	return (free(env_opwd->value), env_opwd->value = oldpwd_nvalue, 0);
}
