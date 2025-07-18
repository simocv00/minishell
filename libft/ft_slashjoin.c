/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slashjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:10:19 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/20 16:10:26 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_slashjoin(char *s1, char *s3)
{
	char	*c;
	int		i;
	int		j;

	i = 0;
	c = malloc(ft_strlen(s1) + ft_strlen(s3) + 2);
	if (!c)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	c[i++] = '/';
	j = 0;
	while (s3[j])
	{
		c[i + j] = s3[j];
		j++;
	}
	c[i + j] = '\0';
	return (c);
}
