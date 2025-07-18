/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27-get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:38:59 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 10:26:03 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_strcpy(char *str, char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_sttrchr(char *str, ssize_t *j, char c)
{
	size_t	i;

	i = *j;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_sub(char *str, char *s, ssize_t *k, size_t size2)
{
	char	*tmp;
	ssize_t	i;

	i = -1;
	tmp = malloc((size2 + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	if (str)
		while (str[++i])
			tmp[i] = str[i];
	else
		i = 0;
	while (s[*k] != '\n' && s[*k] != '\0')
		tmp[i++] = s[(*k)++];
	if (s[*k] == '\n')
		tmp[i++] = s[(*k)];
	tmp[i] = '\0';
	if (str)
		free(str);
	return (tmp);
}
