/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   29-heredoc_expander_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:38:34 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/03 23:22:10 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_heredoc_noskips(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '*' || c == '?');
}

int	variable_len(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*extract_variable_value(char *variable, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(variable, env->variable))
		{
			if (env->value)
				return (env->value);
			else
				return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}
