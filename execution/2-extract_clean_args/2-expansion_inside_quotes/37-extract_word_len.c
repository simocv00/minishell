/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35-extract_word_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:34:38 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 10:24:55 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	quotes_parse_helper(const char *str, int i, char q)
{
	int	d;
	int	j;

	d = 0;
	j = 0;
	while (str[i + j] && (str[i + j] == q || d % 2 == 1))
	{
		if (str[i + j] == q)
			d++;
		j++;
	}
	return (j);
}

int	extract_word_len(const char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && str[i + j] != '*' && (str[i + j] != '$' || (str[i
					+ j] == '$' && !ft_isalnum(str[i + j + 1]) && str[i + j
					+ 1] != '_')))
	{
		if (str[i + j] == '\'')
			j += quotes_parse_helper(str, i + j, '\'');
		else if (str[i + j] == '\"')
			j += quotes_parse_helper(str, i + j, '\"');
		else
			j++;
	}
	return (j);
}
