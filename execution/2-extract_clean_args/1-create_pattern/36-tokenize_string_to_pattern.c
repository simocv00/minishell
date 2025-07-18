/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36-tokenize_string_to_pattern.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:16:42 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 20:52:46 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_exp_split(char *str)
{
	int			i;
	t_sdquotes	sd;

	i = ft_strlen(str) - 1;
	sd = (t_sdquotes){0, 0, 0, 0};
	while (i >= 0 && str[i])
	{
		if (check_quotes_flags(str, sd, i))
			check_wild_exp_out_quotes_helper(str, &sd, i);
		else if (str[i] == '$' && sd.sflag == 0 && sd.dflag == 0)
		{
			if (str[i + 1] != '\'' && str[i + 1] != '\"')
			{
				if (check_split_chars(str[i + 1]))
					return (1);
				else
					return (0);
			}
		}
		i--;
	}
	return (0);
}

int	tokenize_simple_word(t_shelldata *shelldata, t_pattern **list, char *str,
		int i)
{
	int		j;
	char	*tmp;

	j = extract_word_len(str, i);
	tmp = ft_substr(str, i, j);
	if (!tmp)
		return (shelldata->state = -2, free_pattern_t(*list), -1);
	tmp = expand_inside_dquotes(shelldata, tmp);
	if (!tmp && shelldata->state < 0)
		return (free_pattern_t(*list), -1);
	if (add_back_pattern(list, tmp, WORD) < 0)
		return (free(tmp), free_pattern_t(*list), -1);
	return (j);
}

int	tokenize_expansion(t_shelldata *shelldata, t_pattern **list, char *str,
		int *a)
{
	int		j;
	char	*tmp;
	char	*var_value;

	(a[0])++;
	j = variable_len(str + a[0]);
	tmp = ft_substr(str + a[0], 0, j);
	if (!tmp)
		return (shelldata->state = -2, free_pattern_t(*list), -1);
	var_value = extract_variable_value(tmp, shelldata->env);
	free(tmp);
	if (var_value)
	{
		extract_env_var_token(shelldata, list, var_value, a[2]);
		if (shelldata->state < 0)
			return (free_pattern_t(*list), -1);
	}
	return (j);
}

int	tokenize_wildcad(t_shelldata *shelldata, t_pattern **list, char *str, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str[i + j] == '*')
		j++;
	tmp = ft_substr(str, i, j);
	if (!tmp)
		return (shelldata->state = -2, free_pattern_t(*list), -1);
	if (add_back_pattern(list, tmp, WILDCARD) < 0)
		return (free(tmp), free_pattern_t(*list), -1);
	return (j);
}

t_pattern	*tokenize_string(t_shelldata *shelldata, char *str)
{
	int			*a;
	t_pattern	*list;

	a = (int [3]){0, 0, check_exp_split(str)};
	list = NULL;
	while (str[a[0]])
	{
		if (str[a[0]] != '*' && (str[a[0]] != '$' || (str[a[0]] == '$'
					&& !ft_isalnum(str[a[0] + 1]) && str[a[0] + 1] != '_')))
			a[1] = tokenize_simple_word(shelldata, &list, str, a[0]);
		else if (str[a[0]] == '*')
			a[1] = tokenize_wildcad(shelldata, &list, str, a[0]);
		else if (str[a[0]] == '$')
			a[1] = tokenize_expansion(shelldata, &list, str, a);
		if (a[1] < 0)
			return (NULL);
		a[0] = a[0] + a[1];
	}
	return (list);
}
