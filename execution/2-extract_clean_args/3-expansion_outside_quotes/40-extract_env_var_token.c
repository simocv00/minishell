/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40-extract_env_var_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:36:42 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 20:52:56 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_split_chars(char c)
{
	return (!ft_isalnum(c) && c != '@' && c != '*' && c != '#' && c != '?'
		&& c != '-' && c != '$' && c != '_' && c != '&');
}

int	white_spaces_case(t_pattern **list, char *str, int i, int *j)
{
	while (is_white_spaces(str[i + *j]))
		(*j)++;
	if (add_back_pattern(list, NULL, S_PACE) < 0)
		return (-1);
	return (1);
}

int	astrisk_case(t_pattern **list, char *str, int i, int *j)
{
	char	*tmp;

	while (str[i + *j] == '*')
		(*j)++;
	tmp = ft_substr(str, i, *j);
	if (!tmp)
		return (-1);
	if (add_back_pattern(list, tmp, WILDCARD) < 0)
		return (free(tmp), -1);
	return (1);
}

int	word_cases(t_pattern **list, char *str, int *a)
{
	char	*tmp;

	while (str[a[0] + a[1]] && (!is_white_spaces(str[a[0] + a[1]]) || a[2] == 1)
		&& str[a[0] + a[1]] != '*')
		(a[1])++;
	tmp = ft_substr(str, a[0], a[1]);
	if (!tmp)
		return (-1);
	if (add_back_pattern(list, tmp, WORD) < 0)
		return (free(tmp), -1);
	return (1);
}

void	extract_env_var_token(t_shelldata *shelldata, t_pattern **list,
		char *str, int k)
{
	int	*a;

	a = (int [3]){0, 0, k};
	while (str[a[0]])
	{
		a[1] = 0;
		if (is_white_spaces(str[a[0]]) && k == 0)
		{
			if (white_spaces_case(list, str, a[0], &a[1]) < 0)
				return (shelldata->state = -2, (void)0);
		}
		else if (str[a[0]] == '*')
		{
			if (astrisk_case(list, str, a[0], &a[1]) < 0)
				return (shelldata->state = -2, (void)0);
		}
		else if (str[a[0]] != '*' && (!is_white_spaces(str[a[0]]) || k == 1))
		{
			if (word_cases(list, str, a) < 0)
				return (shelldata->state = -2, (void)0);
		}
		a[0] = a[0] + a[1];
	}
}
