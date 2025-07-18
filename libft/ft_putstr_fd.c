/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:25:05 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/06 15:40:08 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(int fd, char *s)
{
	int	i;

	if (!s)
		return (write(fd, "", 1));
	i = write(fd, s, ft_strlen(s));
	if (i < 0)
		perror("minishell: write error");
	return (i);
}
