/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:25:10 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/29 11:46:56 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_string(char **str, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	ctw(char const *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		while (str[i] != c && str[i])
			i++;
		if (str[--i] != c)
			j++;
		i++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (j);
}

static char	*add_s(char **str, char const *s, t_spvar v, char c)
{
	str[v.k] = malloc(sizeof(char) * ((v.j) + 1));
	v.j = 0;
	if (!str[v.k])
		return (free_string(str, v.k), (NULL));
	while (s[v.i] != c && s[v.i])
		str[v.k][(v.j)++] = s[(v.i)++];
	str[v.k][v.j] = '\0';
	return (str[v.k]);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	t_spvar	v;

	v = (t_spvar){0, 0, 0};
	str = malloc(sizeof(char *) * (ctw(s, c) + 1));
	if (!str)
		return (NULL);
	while ((s[v.i] == c) && s[v.i])
		(v.i)++;
	while (s[v.i])
	{
		if (s[v.i] != c)
		{
			v.j = 0;
			while (s[(v.i) + (v.j)] != c && s[(v.i) + (v.j)])
				(v.j)++;
			if (!(add_s(str, s, v, c)))
				return (NULL);
			v.i = v.i + v.j;
			(v.k)++;
		}
		while (s[v.i] == c && s[v.i])
			(v.i)++;
	}
	return (str[v.k] = 0, (str));
}
