/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:25:29 by makarkao          #+#    #+#             */
/*   Updated: 2024/11/15 00:00:55 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = ft_strlen(src);
	if (!dst && size == 0)
		return (j);
	k = 0;
	i = ft_strlen(dst);
	if (size <= i)
		return (size + j);
	while (k < j && k < size - 1 - i)
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = 0;
	return (i + j);
}
