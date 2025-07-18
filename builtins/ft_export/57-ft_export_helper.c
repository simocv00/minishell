/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   57-ft_export_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:27:44 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 01:58:19 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_errors(char *cwd, int type)
{
	if (type == 0)
	{
		ft_print_join("minishell: export: `", cwd,
			"': not a valid identifier\n");
		return (1);
	}
	return (1);
}

char	**ex_split(t_shelldata *shelldata, char *str)
{
	char	**s;
	size_t	*a;

	a = (size_t[3]){0, ft_strlen(str), 1};
	s = ft_calloc(4, sizeof(char *));
	if (!s)
		return (shelldata->state = -2, NULL);
	while (str[a[0]] && str[a[0]] != '=' && str[a[0]] != '+')
		a[0]++;
	s[0] = ft_substr(str, 0, a[0]);
	if (!s[0])
		return (free(s), shelldata->state = -2, NULL);
	if (str[a[0]] == '+')
		a[2]++;
	s[1] = ft_substr(str, a[0], a[2]);
	if (!s[1])
		return (free_strs(s), shelldata->state = -2, NULL);
	if (a[2] + a[0] < a[1])
	{
		s[2] = ft_substr(str, a[2] + a[0], a[1] - a[2] - a[0]);
		if (!s[2])
			return (free_strs(s), shelldata->state = -2, NULL);
	}
	return (s);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

void	new_env(char **s, t_shelldata *shelldata, int ev_h)
{
	add_back_env(shelldata, s[0], s[2], ev_h);
	free(s[1]);
	free(s);
}

void	edit_env_node(t_env *node, char **s, t_shelldata *shelldata)
{
	char	*new_value;

	if (s[1][0] == '+')
	{
		new_value = join_and_free(node->value, s[2]);
		if (!new_value)
		{
			shelldata->state = -2;
			free_strs(s);
			return ;
		}
		node->value = new_value;
	}
	else
	{
		free(node->value);
		node->value = s[2];
	}
	node->ev_hide = 0;
	free(s[0]);
	free(s[1]);
	free(s);
}
