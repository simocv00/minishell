/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sthreecat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:20:03 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/29 13:42:09 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sthreecat(char *s1, char *s2, char *s3)
{
	char	*str;
	int		*a;

	a = (int [4]){0, 0, ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)};
	str = malloc(a[2] + 1);
	if (!str)
		return (NULL);
	if (s1)
		a[0] = ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	if (!s2 && !s3)
		return (str);
	if (s2)
	{
		a[1] = ft_strlen(s2);
		ft_strlcat(str, s2, a[0] + a[1] + 1);
	}
	if (!s3)
		return (str);
	ft_strlcat(str, s3, a[2] + 1);
	return (str);
}
