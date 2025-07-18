/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25-manage_herdoc_expansion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:38:21 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/07 18:16:36 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	redirection_loop(t_shelldata *shelldata, t_redir *redir, int fd1, int fd2)
{
	char	*buffer;

	buffer = get_next_line(shelldata, redir->redirfd);
	if (!buffer && shelldata->state < 0)
		return (close(fd2), close(fd1), shelldata->state);
	buffer = expand_here_doc(shelldata, buffer);
	if (!buffer && shelldata->state < 0)
		return (close(fd2), close(fd1), shelldata->state);
	while (buffer)
	{
		write(fd1, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(shelldata, redir->redirfd);
		if (!buffer && shelldata->state < 0)
			return (close(fd2), close(fd1), shelldata->state);
		buffer = expand_here_doc(shelldata, buffer);
		if (!buffer && shelldata->state < 0)
			return (close(fd2), close(fd1), shelldata->state);
	}
	return (1);
}

int	re_redicrect_herdoc(t_shelldata *shelldata, t_redir *redir)
{
	int		fd1;
	int		fd2;
	char	*fp;

	fp = filepath();
	if (!fp)
		return (perror("malloc"), shelldata->state = -2);
	fd1 = open(fp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd1 == -1)
		return (free(fp), perror("open"), shelldata->state = -1);
	fd2 = open(fp, O_RDONLY);
	if (fd2 == -1)
		return (free(fp), close(fd2), perror("open"), shelldata->state = -1);
	if (unlink(fp) == -1)
		return (free(fp), close(fd2), close(fd1), perror("unli"),
			shelldata->state = -1);
	free(fp);
	if (redirection_loop(shelldata, redir, fd1, fd2) < 0)
		return (shelldata->state);
	close(fd1);
	close(redir->redirfd);
	redir->redirfd = fd2;
	return (1);
}

int	check_expandable_data(t_shelldata *shelldata, t_redir *redir)
{
	if (ft_chrinstr(redir->redir_name, '\'') >= 0
		|| ft_chrinstr(redir->redir_name, '\"') >= 0)
		return (1);
	return (re_redicrect_herdoc(shelldata, redir));
}
