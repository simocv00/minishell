/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28-heredoc_expander.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:31:35 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/29 12:15:48 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	expand_qmark(t_shelldata *shelldata, char **str, t_exp *exp)
{
	exp->j = 1;
	exp->variable_value = ft_itoa(shelldata->exit_status);
	if (!exp->variable_value)
		return (free(*str), shelldata->state = -2, -2);
	exp->k = ft_strlen(exp->variable_value);
	*((*str) + exp->i) = '\0';
	return (1);
}

int	expand_var(t_shelldata *shelldata, char **str, t_exp *exp)
{
	exp->j = variable_len((*str) + exp->i + 1);
	exp->variable = ft_substr((*str) + exp->i + 1, 0, exp->j);
	if (!exp->variable)
		return (free(*str), shelldata->state = -2, -2);
	exp->variable_value = extract_variable_value(exp->variable, shelldata->env);
	if (exp->variable_value)
	{
		exp->variable_value = ft_strdup(exp->variable_value);
		if (!exp->variable_value)
			return (free(*str), free(exp->variable), shelldata->state = -2, -2);
	}
	exp->k = ft_strlen(exp->variable_value);
	*((*str) + exp->i) = '\0';
	return (1);
}

int	cat_expands(t_shelldata *shelldata, char **str, t_exp *exp)
{
	exp->tmp = *str;
	*str = ft_sthreecat(exp->tmp, exp->variable_value, (*str) + exp->i + exp->j
			+ 1);
	exp->i = exp->i + exp->k;
	if (exp->tmp)
		(free(exp->tmp), exp->tmp = NULL);
	if (exp->variable)
		(free(exp->variable), exp->variable = NULL);
	if (exp->variable_value)
		(free(exp->variable_value), exp->variable_value = NULL);
	if (!(*str))
		return (shelldata->state = -2, -2);
	return (1);
}

int	expand_cases(t_shelldata *shelldata, char **str, t_exp *exp)
{
	if ((*str)[exp->i + 1] == '?')
	{
		if (expand_qmark(shelldata, str, exp) < 0)
			return (-1);
	}
	else if ((*str)[exp->i + 1] == '*')
	{
		exp->j = 1;
		exp->k = 0;
		*((*str) + exp->i) = '\0';
	}
	else if (expand_var(shelldata, str, exp) < 0)
		return (-1);
	return (1);
}

char	*expand_here_doc(t_shelldata *shelldata, char *str)
{
	t_exp	exp;

	exp = (t_exp){0, 0, 0, NULL, NULL, NULL};
	if (!str || !str[0])
		return (NULL);
	while (str[exp.i])
	{
		if (str[exp.i] == '$' && check_heredoc_noskips(str[exp.i + 1]))
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
