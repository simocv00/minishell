/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-t_cmd_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:46:01 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/10 08:54:40 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_line(char *s, char *line, int fd1)
{
	if (!line && errno == EIO)
		exit((free(s), close(fd1), perror("readline"), -1));
	else if (!line && errno == ENOMEM)
		exit((free(s), close(fd1), perror("readline"), -2));
	else if (!line && errno != 0)
		exit((free(s), close(fd1), perror("readline"), 0));
	else if (!line && errno == 0)
	{
		print_ctrd_msg(s);
		exit((free(s), close(fd1), 0));
	}
}

void	fill_with_data_helper(char *str, t_shelldata *shelldata, int fd1,
		int fd2)
{
	char		*s;
	char		*line;
	t_hdocfree	*hdoc;

	(signal(SIGINT, sig_heredoc), hdoc = hdoc_memo(), s = erase_quotes(str));
	hdoc->s = s;
	hdoc->fd = fd1;
	if (!s)
		mini_exit((close(fd1), perror("malloc"), -2));
	(free_shelldata(shelldata, F_ENV | F_CMD, 1), close(fd2),
		line = readline("> "));
	check_line(s, line, fd1);
	while (line && ft_strcmp(line, s))
	{
		(write(fd1, line, strlen(line)), write(fd1, "\n", 1), free(line),
			line = readline("> "));
		check_line(s, line, fd1);
	}
	exit((free(s), close(fd1), 0));
}

int	fill_with_data(char *str, t_shelldata *shelldata, int fd1, int fd2)
{
	int		status;
	pid_t	pid;
	int		exit_status;

	signal(SIGINT, sig_handler2);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		fill_with_data_helper(str, shelldata, fd1, fd2);
	(waitpid(pid, &status, 2), close(fd1));
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status < 0)
			mini_exit((close(fd2), -exit_status));
		if (exit_status)
			return (-1);
		return (0);
	}
	else if (WIFSIGNALED(status))
		return (-1);
	mini_exit((close(fd2), 1));
	return (-1);
}

int	fill_herefoc(char *str, t_shelldata *shelldata)
{
	char	*fp;
	int		fd1;
	int		fd2;
	int		ret_value;

	fp = filepath();
	if (!fp)
		mini_exit((perror("malloc"), 2));
	fd1 = open(fp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd1 == -1)
	{
		return (free(fp), perror("open"), -1);
	}
	fd2 = open(fp, O_RDONLY);
	if (fd2 == -1)
	{
		return (close(fd1), free(fp), perror("open"), -1);
	}
	if (unlink(fp) == -1)
		return (close(fd1), close(fd2), free(fp), perror("unlink"), -1);
	free(fp);
	ret_value = fill_with_data(str, shelldata, fd1, fd2);
	if (ret_value < 0)
		return (close(fd2), -1);
	return (fd2);
}
