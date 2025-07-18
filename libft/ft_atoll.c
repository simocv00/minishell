/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:59:43 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/08 10:45:28 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str, int *flag)
{
	int					i;
	int					s;
	unsigned long long	n;
	unsigned long long	llmin_value;

	i = 0;
	n = 0;
	s = 1;
	llmin_value = (unsigned long long)LLONG_MIN;
	if (!str[i])
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if ((s > 0 && n > LLONG_MAX) || (s < 0 && n > llmin_value))
			return ((*flag)++, 0);
		i++;
	}
	return (n * s);
}
