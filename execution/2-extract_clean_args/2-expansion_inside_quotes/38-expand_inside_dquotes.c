/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36-expand_inside_dquotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:57:09 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/29 12:14:52 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*expand_inside_dquotes_helper(t_shelldata *shelldata, char *str,
		t_sdquotes *sd)
{
	t_exp	exp;

	exp = (t_exp){0, 0, 0, NULL, NULL, NULL};
	while (str[exp.i])
	{
		if (delete_quotes_condition(str, sd, exp.i))
			delete_quotes(str, sd, &exp);
		else if (check_expand_condition(str, sd, exp.i))
		{
			if (expand_cases(shelldata, &str, &exp) < 0)
				return (NULL);
			if (cat_expands(shelldata, &str, &exp) < 0)
				return (NULL);
		}
		else
			exp.i++;
	}
	return (str);
}

char	*expand_inside_dquotes(t_shelldata *shelldata, char *str)
{
	t_sdquotes	sd;

	sd = (t_sdquotes){0, 0, 0, 0};
	return (expand_inside_dquotes_helper(shelldata, str, &sd));
}
