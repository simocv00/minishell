/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42-check_pattern_match.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:57:26 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/07 21:51:00 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_strnstrrr(char *str, char *dst, size_t n)
{
	size_t	i;
	size_t	j;

	if (!str && !n)
		return (NULL);
	if (!dst[0] && !n)
		return ((char *)str);
	if (!dst[0] && !str[0])
		return ((char *)str);
	i = 0;
	while (str[i] && i < n)
	{
		j = 0;
		while (dst[j] && str[i + j] && (str[i + j] == dst[j]) && (i + j) < n)
			j++;
		if (dst[j] == '\0')
			return ((char *)(str + i));
		if (i + j >= n)
			return (NULL);
		i++;
	}
	return (NULL);
}

char	*ft_end_n_str(char *str, int n)
{
	int	i;

	i = ft_strlen(str);
	if (i < n)
		return (NULL);
	return (str + i - n);
}

int	check_pattern_new_helper(t_pattern *tmp, char *substr)
{
	int	j;

	while (tmp)
	{
		if (tmp->type == WORD && !tmp->next)
		{
			j = ft_strlen(tmp->str);
			if (ft_strncmp(tmp->str, ft_end_n_str(substr, j), j))
				return (0);
			else
				return (1);
		}
		else if (tmp->type == WORD)
		{
			j = ft_strlen(tmp->str);
			substr = ft_strnstrrr(substr, tmp->str, ft_strlen(substr));
			if (!substr)
				return (0);
			substr = substr + j;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_pattern_new(t_pattern *pattern, char *str)
{
	int			j;
	t_pattern	*tmp;
	char		*substr;

	substr = str;
	if (pattern->type == WORD)
	{
		j = ft_strlen(pattern->str);
		if (ft_strncmp(pattern->str, str, j))
			return (0);
		substr = str + j;
	}
	tmp = pattern->next;
	return (check_pattern_new_helper(tmp, substr));
}
