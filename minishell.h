/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:10:55 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 10:57:22 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./builtins/builtins.h"
# include "./execution/execution.h"
# include "./parsing/parsing.h"

char		*prompt_mini(t_shelldata *shelldata);
int			ft_print_join(char *s1, char *s2, char *s3);
int			ft_inprint_join(char *s1, char *s2, char *s3);

t_shelldata	*shelldata_memo(void);

//minishell helper
void		interactive_non_interactive(t_shelldata *shelldata);
void		mini_exit(int status);
void		init_shelldata(t_shelldata *shelldata);
void		free_shelldata(t_shelldata *shelldata, int flag, int hflag);

//env
int			set_environment(t_shelldata *shelldata, char **ev);
int			add_back_env(t_shelldata *shelldata, char *variable, char *value,
				int ev_h);
void		free_env(t_env *env);

#endif