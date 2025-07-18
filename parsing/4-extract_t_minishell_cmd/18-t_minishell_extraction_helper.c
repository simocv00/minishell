/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16-t_minishell_extraction_helper.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:57:57 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/03 15:37:08 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_indata(t_type type)
{
	if (type == INFILE_NAME || type == DELIMITER)
		return (1);
	return (0);
}

int	is_outdata(t_type type)
{
	if (type == OUTFILE_NAME || type == APPEND_NAME)
		return (1);
	return (0);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->args = NULL;
	data->c_cmd = NULL;
	data->redir = NULL;
	data->type = NONE;
	return (data);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->args)
		free_args(data->args);
	if (data->c_cmd)
		free_minishell(data->c_cmd);
	if (data->redir)
		free_redir(data->redir);
	free(data);
}
