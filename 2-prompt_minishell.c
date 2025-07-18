/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-prompt_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:42:15 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 15:00:57 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_join(char *s1, char *s2, char *s3)
{
	char		*sjoin;
	t_shelldata	*shelldata;

	shelldata = shelldata_memo();
	sjoin = ft_sthreecat(s1, s2, s3);
	if (!sjoin)
		return (shelldata->state = -2, perror("malloc"), -1);
	ft_putstr_fd(2, sjoin);
	free(sjoin);
	return (1);
}

int	ft_inprint_join(char *s1, char *s2, char *s3)
{
	char		*sjoin;
	t_shelldata	*shelldata;

	shelldata = shelldata_memo();
	sjoin = ft_sthreecat(s1, s2, s3);
	if (!sjoin)
		return (shelldata->state = -2, perror("malloc"), -1);
	if (ft_putstr_fd(1, sjoin) < 0)
		return (free(sjoin), -1);
	free(sjoin);
	return (1);
}

void	modify_prompt(char *prompt)
{
	int	i;

	i = 0;
	prompt[0] = 0;
	ft_concat(prompt, COL_PATH "minishell> " ARROW_CYAN2DEF CLR_RESET " ", &i);
}

char	*prompt_mini(t_shelldata *shelldata)
{
	int			i;
	char		*user_value;
	static char	prompt[1024];

	i = 0;
	prompt[0] = 0;
	ft_concat(prompt, "\n", &i);
	ft_concat(prompt, COL_MINI " minishell$ " ARROW_PINK2CYAN COL_PATH " ", &i);
	if (!shelldata->cwd)
		ft_concat(prompt, "path/?", &i);
	else
		ft_concat(prompt, shelldata->cwd, &i);
	ft_concat(prompt, " " ARROW_CYAN2DEF "\n" COL_USER " ", &i);
	ft_concat(prompt, "@", &i);
	user_value = extract_variable_value("USER", shelldata->env);
	if (!user_value)
		ft_concat(prompt, "unknown_user", &i);
	else
		ft_concat(prompt, user_value, &i);
	ft_concat(prompt, " " ARROW_GOLD2DEF "\001\002" " \x7f" CLR_RESET, &i);
	if (i >= 999)
		modify_prompt(prompt);
	return (prompt);
}
