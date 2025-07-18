/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43-extract_wildcards_args.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:35:33 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 18:28:34 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_match_condition(t_pattern_list *pattern_list, struct dirent *entry)
{
	return ((ft_strncmp(entry->d_name, ".", 1)
			|| !ft_strncmp(pattern_list->pattern->str, ".", 1))
		&& check_pattern_new(pattern_list->pattern, entry->d_name));
}

int	check_dir_entries(t_shelldata *shelldata, t_pattern_list *pattern_list,
		t_dirr *d)
{
	d->entry = readdir(d->dir);
	while (d->entry)
	{
		if (check_match_condition(pattern_list, d->entry))
		{
			d->tmp_name = ft_strdup(d->entry->d_name);
			if (!d->tmp_name)
				return (perror("malloc"), free_args(d->tmp),
					shelldata->state = -2, -1);
			if (add_args_sorted(&d->tmp2, d->tmp_name, 0) < 0)
				return (perror("malloc"), free(d->tmp_name), free_args(d->tmp),
					shelldata->state = -2, -1);
			if (d->flag == 0)
				d->flag = 1;
		}
		d->entry = readdir(d->dir);
	}
	if (pattern_list && pattern_list->is_cmd && d->flag)
		d->tmp2->is_cmd = pattern_list->is_cmd;
	add_args_node_back(&d->tmp, d->tmp2);
	return (1);
}

int	add_node_closedir_helper(t_shelldata *shelldata, t_dirr *d)
{
	if (d->dir && closedir(d->dir) == -1 && (errno == ENOMEM || errno == EIO))
		return (perror("closedir"), free_args(d->tmp), shelldata->state = -1,
			-1);
	return (1);
}

t_args	*clean_expand_wildcard_helper(t_shelldata *shelldata,
										t_pattern_list *pattern_list)
{
	t_dirr	d;

	d.tmp = NULL;
	while (pattern_list)
	{
		d.flag = 0;
		d.dir = opendir(".");
		if (d.dir == NULL && (errno == ENOMEM || errno == EIO))
			return (perror("opendir"), free_args(d.tmp), shelldata->state = -1,
				NULL);
		if (d.dir && pattern_list->is_wildcard)
		{
			d.tmp2 = NULL;
			if (check_dir_entries(shelldata, pattern_list, &d) < 0)
				return (NULL);
		}
		if (add_node_closedir_helper(shelldata, &d) < 0)
			return (NULL);
		if (d.flag == 0 && pattern_list->type == PATTERN
			&& pattern_list->pattern)
			add_args_word_back(&d.tmp, pattern_t_str(pattern_list->pattern),
				pattern_list->is_cmd);
		pattern_list = pattern_list->next;
	}
	return (d.tmp);
}

t_args	*clean_expand_wildcard(t_shelldata *shelldata, t_args *arg)
{
	t_pattern_list	*pattern_list;
	t_args			*extracted_arg;

	pattern_list = create_pattern(shelldata, arg->str);
	extracted_arg = NULL;
	if (!pattern_list)
		return (NULL);
	if (arg->is_cmd)
		pattern_list->is_cmd = 1;
	extracted_arg = clean_expand_wildcard_helper(shelldata, pattern_list);
	free_pattern_list_t(pattern_list);
	return (extracted_arg);
}
