/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numericheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:01:53 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/11 14:54:08 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tabspace(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_whitespaces(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_numericheck(char *num)
{
	int	i;
	int	sp_flag;

	i = 0;
	sp_flag = 0;
	if (!num)
		return (-1);
	if (!num[0])
		return (1);
	while (ft_whitespaces(num[i]))
		i++;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i] || ft_tabspace(num[i]))
	{
		if (!ft_isdigit(num[i]) && !ft_tabspace(num[i]))
			return (1);
		if (ft_tabspace(num[i]) && sp_flag == 0)
			sp_flag = 1;
		if (sp_flag == 1 && !ft_tabspace(num[i]))
			return (1);
		i++;
	}
	return (0);
}
