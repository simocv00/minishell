/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:54:05 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 15:47:32 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tstrslen(char **strs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j])
				k++;
			j++;
		}
		i++;
	}
	return (k);
}

size_t	ft_strslen(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

char	*ft_strsjoin(char **strs, char c)
{
	char	*s;
	int		*a;
	int		size;

	if (!strs[0])
		return (ft_strdup(""));
	if (c)
		size = ft_strslen(strs);
	else
		size = 1;
	s = malloc((size - 1) + ft_tstrslen(strs) + 1);
	if (!s)
		return (NULL);
	a = (int [3]){0, 0, 0};
	while (strs[a[0]])
	{
		a[2] = 0;
		while (strs[a[0]][a[2]] != '\0')
			s[a[1]++] = strs[a[0]][a[2]++];
		if (c && strs[a[0] + 1])
			s[a[1]++] = c;
		a[0]++;
	}
	s[a[1]] = '\0';
	return (s);
}
