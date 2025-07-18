/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   52-ft_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:29:05 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 10:47:49 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_echo_n_option(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_shelldata *shelldata, char **str)
{
	int		i;
	int		print_newline;
	char	*print;
	char	*tmp;

	i = -1;
	print_newline = 1;
	str++;
	while (str[++i] && is_echo_n_option(str[i]))
		print_newline = 0;
	tmp = ft_strsjoin(str + i, ' ');
	if (!tmp)
		return (perror("malloc"), shelldata->state = -2, 1);
	if (print_newline)
	{
		print = ft_strjoin(tmp, "\n");
		free(tmp);
		if (!print)
			return (perror("malloc"), shelldata->state = -2, 1);
	}
	else
		print = tmp;
	if (ft_putstr_fd(1, print) < 0)
		return (free(print), 1);
	return (free(print), 0);
}
