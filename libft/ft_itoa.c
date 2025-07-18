/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:23:52 by makarkao          #+#    #+#             */
/*   Updated: 2024/11/14 23:59:58 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	leninteger(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int x)
{
	char			*str;
	int				i;
	unsigned int	n;

	n = x;
	i = leninteger(n) + 1;
	if (x <= 0)
	{
		n = -x;
		i = leninteger(n) + 2;
	}
	str = malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	str[--i] = '\0';
	if (n == 0)
		str[--i] = '0';
	if (x < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[--i] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
