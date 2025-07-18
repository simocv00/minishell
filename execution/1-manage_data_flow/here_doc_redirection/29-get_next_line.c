/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26-get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:27:29 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/06 14:01:49 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_get_nxt_line_prc(t_shelldata *shelldata, t_gnlsv *v, t_gnlnsv *x,
		int fd)
{
	while (v->s[0] != 0)
	{
		x->j += ft_sttrchr(v->s, &(v->k), '\n');
		x->l = ft_sub(x->l, v->s, &(v->k), (x->j - v->k));
		if (!x->l)
			return (free(v->s), v->s = NULL, perror("malloc"),
				shelldata->state = -2, NULL);
		if (v->s[v->k] == '\n')
		{
			(v->k)++;
			break ;
		}
		if (v->s[v->k] == '\0')
		{
			x->i = read(fd, v->s, BUFFER_SIZE);
			if (x->i == -1)
				return (free(x->l), free(v->s), v->s = NULL,
					shelldata->state = -2, NULL);
			v->s[x->i] = '\0';
			v->k = 0;
		}
	}
	if (v->s[0] == 0)
		(free(v->s), v->s = NULL);
	return (x->l);
}

char	*get_next_line(t_shelldata *shelldata, int fd)
{
	static t_gnlsv	v;
	t_gnlnsv		x;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	x.j = 0;
	x.l = NULL;
	if (v.s == NULL || v.s[v.k] == 0)
	{
		if (!v.s)
		{
			v.s = malloc(sizeof(char) * (((size_t)BUFFER_SIZE) + 1));
			if (!v.s)
				return (shelldata->state = -2, perror("malloc"), NULL);
		}
		x.i = read(fd, v.s, BUFFER_SIZE);
		if (x.i == -1)
			return (free(v.s), v.s = NULL, shelldata->state = -2, NULL);
		v.s[x.i] = '\0';
		v.k = 0;
	}
	return (ft_get_nxt_line_prc(shelldata, &v, &x, fd));
}
