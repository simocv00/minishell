/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   56-ft_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:27:44 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 11:51:55 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	helper_function(char **s, t_shelldata *shelldata)
{
	t_env	*node;

	if (shelldata->env)
	{
		node = get_env_str(s[0], shelldata->env);
		if (node)
			edit_env_node(node, s, shelldata);
		else
			new_env(s, shelldata, 0);
	}
	else
		new_env(s, shelldata, 0);
}

static void	helper_function1(char **s, t_shelldata *shelldata)
{
	t_env	*node;

	if (shelldata->env)
	{
		node = get_env_str(s[0], shelldata->env);
		if (!node)
			new_env(s, shelldata, 1);
		else
			(free(s[0]), free(s[1]), free(s));
	}
	else
		new_env(s, shelldata, 1);
}

int	valid_input_nn(char *str, int *err)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (*err = export_errors(str, 0), 0);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_' && (str[i] != '+' || str[i
					+ 1] != '='))
			return (*err = export_errors(str, 0), 0);
		i++;
	}
	return (1);
}

int	ft_export(t_shelldata *shelldata, char **cmd)
{
	int		i;
	int		err;
	char	**strs;

	if (!cmd[1])
		return (print_env(shelldata, shelldata->env), 0);
	i = 1;
	err = 0;
	while (cmd[i])
	{
		if (valid_input_nn(cmd[i], &err))
		{
			strs = ex_split(shelldata, cmd[i]);
			if (!strs && shelldata->state < 0)
				return (perror("malloc"), 2);
			if (!strs[1][0])
				helper_function1(strs, shelldata);
			else
				helper_function(strs, shelldata);
			if (shelldata->state < 0)
				return (perror("malloc"), 2);
		}
		i++;
	}
	return (err);
}
