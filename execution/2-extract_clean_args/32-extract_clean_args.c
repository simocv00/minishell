/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30-extract_clean_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:51:48 by makarkao          #+#    #+#             */
/*   Updated: 2025/06/28 15:22:13 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	extract_len(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		args = args->next;
		i++;
	}
	return (i);
}

char	**extract_args(t_shelldata *shelldata, t_minishell *shell)
{
	int		i;
	int		len;
	char	**str;
	t_args	*tmp;

	i = 0;
	len = extract_len(shell->args_list);
	str = ft_calloc(len + 1, sizeof(char *));
	if (!str)
		return (perror("malloc"), shelldata->state = -2, NULL);
	while (shell->args_list)
	{
		str[i] = shell->args_list->str;
		tmp = shell->args_list->next;
		free(shell->args_list);
		shell->args_list = tmp;
		i++;
	}
	return (str);
}

void	extract_clean_args(t_shelldata *shelldata, t_minishell *shell)
{
	extract_clean_args_helper(shelldata, shell);
	if (shelldata->state < 0)
		return ;
	if (shell->args_list)
		shell->args = extract_args(shelldata, shell);
	shell->args_extracted = 1;
}
