/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33-extract_clean_args_helper.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:51:27 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 17:04:00 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_export_expansion(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_' && (str[i] != '+' || str[i
					+ 1] != '='))
			return (0);
		i++;
	}
	return (1);
}

t_args	*args_tail(t_args *args)
{
	if (!args)
		return (NULL);
	while (args->next)
		args = args->next;
	return (args);
}

void	insert_ext_args_null(t_minishell *shell, t_args **tmp, t_args *prev)
{
	if (!prev)
	{
		shell->args_list = (*tmp)->next;
		if ((*tmp)->next && (*tmp)->is_cmd)
			(*tmp)->next->is_cmd = 1;
	}
	else
	{
		prev->next = (*tmp)->next;
		if ((*tmp)->next && (*tmp)->is_cmd)
			(*tmp)->next->is_cmd = 1;
	}
	destroy_args_node(*tmp);
	*tmp = prev;
}

void	insert_ext_args(t_shelldata *shelldata, t_minishell *shell,
		t_args **tmp, t_args *prev)
{
	t_args	*tmp2;
	t_args	*ext_args;

	ext_args = clean_expand_wildcard(shelldata, *tmp);
	if (!ext_args && shelldata->state < 0)
		return ;
	if (!ext_args)
		insert_ext_args_null(shell, tmp, prev);
	else
	{
		if (!prev)
			shell->args_list = ext_args;
		else
			prev->next = ext_args;
		tmp2 = args_tail(ext_args);
		tmp2->next = (*tmp)->next;
		destroy_args_node(*tmp);
		*tmp = tmp2;
	}
}

void	extract_clean_args_helper(t_shelldata *shelldata, t_minishell *shell)
{
	t_args	*tmp;
	t_args	*prev;

	prev = NULL;
	tmp = shell->args_list;
	if (!ft_strcmp(shell->args_list->str, "export"))
		shell->exp_split = 1;
	while (tmp)
	{
		if (!check_wild_exp_out_quotes(tmp->str) || (shell->exp_split == 1
				&& check_export_expansion(tmp->str)))
			tmp->str = expand_inside_dquotes(shelldata, tmp->str);
		else
			insert_ext_args(shelldata, shell, &tmp, prev);
		if (shelldata->state < 0)
			return ;
		prev = tmp;
		if (!tmp)
			tmp = shell->args_list;
		else
			tmp = tmp->next;
	}
}
