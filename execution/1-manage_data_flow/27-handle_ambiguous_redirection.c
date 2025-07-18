/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27-handle_ambiguous_redirection.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:49:55 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 15:47:06 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_ambig(t_shelldata *shelldata, t_redir *redir, t_redir *redirin,
		t_redir *redirout)
{
	if (redir->type != DELIMITER && check_ambiguous_redir(shelldata, redir) < 0)
	{
		if (redirin)
			close(redirin->redirfd);
		if (redirout)
			close(redirout->redirfd);
		return (-1);
	}
	return (1);
}

int	pattern_list_len(t_pattern_list *pattern_list)
{
	int	i;

	i = 0;
	while (pattern_list)
	{
		i++;
		pattern_list = pattern_list->next;
	}
	return (i);
}

int	check_ambiguous_redir(t_shelldata *shelldata, t_redir *redir)
{
	t_pattern_list	*pattern_list;
	t_args			*args;

	if (!check_wild_exp_out_quotes(redir->redir_name))
	{
		redir->redir_name = expand_inside_dquotes(shelldata, redir->redir_name);
		return (1);
	}
	pattern_list = create_pattern(shelldata, redir->redir_name);
	if (pattern_list_len(pattern_list) != 1)
	{
		(free_pattern_list_t(pattern_list), shelldata->state = -1);
		return (ft_print_join("minishell: ", redir->redir_name,
				": ambiguous redirect\n"), -1);
	}
	args = clean_expand_wildcard_helper(shelldata, pattern_list);
	free_pattern_list_t(pattern_list);
	if (!args || args->next)
	{
		(free_args(args), shelldata->state = -1);
		return (ft_print_join("minishell: ", redir->redir_name,
				": ambiguous redirect\n"), -1);
	}
	return (free(redir->redir_name), redir->redir_name = args->str,
		free(args), 1);
}
