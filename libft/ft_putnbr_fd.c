/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:25:00 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 16:24:16 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_pstv(int fd, long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n >= 10)
		i += ft_putnbr_pstv(fd, n / 10);
	return (i += ft_putchar_fd(fd, (n % 10) + '0'));
}

int	ft_putnbr_fd(int fd, int n)
{
	long	x;

	x = (long)n;
	if (x < 0)
		ft_putchar_fd(fd, '-');
	return (ft_putnbr_pstv(fd, x));
}
