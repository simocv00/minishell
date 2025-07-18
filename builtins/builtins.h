/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:10:55 by melayyad          #+#    #+#             */
/*   Updated: 2025/07/14 11:37:05 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../execution/execution.h"

//-------------------check_buitlins-------------------
int		builtin_check(char **args);
int		check_buitin_sample_cond(t_minishell *shell);
int		execute_built_in(t_shelldata *shelldata, t_minishell *shell);

//------ft_exit------------------
int		ft_exit(t_shelldata *shelldata, char **args);

//------ft_echo------------------
int		ft_echo(t_shelldata *shelldata, char **str);

//------ft_env------------------
int		ft_env(t_shelldata *shelldata, t_env *env);
t_env	*get_env_str(char *str, t_env *env);

//------ft_unset------------------
int		ft_unset(t_shelldata *shelldata, char **args);

//------ft_pwd------------------
int		ft_pwd(t_shelldata *shelldata);

//ft_export
int		ft_export(t_shelldata *shelldata, char **cmd);
int		export_errors(char *cwd, int type);
char	**ex_split(t_shelldata *shelldata, char *str);
char	*join_and_free(char *s1, char *s2);
void	new_env(char **s, t_shelldata *shelldata, int ev_h);
void	edit_env_node(t_env *node, char **s, t_shelldata *shelldata);
void	sort_envlist(char **env_list);

//-------ft_cd-----------------------
int		ft_cd(t_shelldata *shelldata, char **str);
int		error_messages(int type, char *message, char *file);
int		update_pwd(t_shelldata *shelldata);
int		update_oldpwd(t_shelldata *shelldata);
int		only_cd(t_shelldata *shelldata, char **cmd, int *ex);
int		minus_option(t_shelldata *shelldata, char **cmd, int *ex);
void	print_env(t_shelldata *shelldata, t_env *list);

#endif