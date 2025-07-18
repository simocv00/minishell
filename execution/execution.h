/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <melayyad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:35:57 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/13 22:01:03 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"
# include <dirent.h>
# include <sys/stat.h>

# define BUFFER_SIZE 100
# define OUT_FLAG 577
/*O_WRONLY | O_CREAT | O_TRUNC*/
# define APPEND_FLAG 1089
/*O_WRONLY | O_CREAT | O_APPEND*/

typedef struct s_gnlsv
{
	ssize_t					k;
	char					*s;
}							t_gnlsv;

typedef struct s_gnlnsv
{
	ssize_t					j;
	ssize_t					i;
	char					*l;
}							t_gnlnsv;

typedef struct s_exp
{
	int						i;
	int						j;
	int						k;
	char					*variable;
	char					*variable_value;
	char					*tmp;
}							t_exp;

typedef struct s_pattern
{
	t_type					type;
	char					*str;
	struct s_pattern		*next;
}							t_pattern;

typedef struct s_pattern_list
{
	t_type					type;
	t_pattern				*pattern;
	int						is_cmd;
	int						is_wildcard;
	struct s_pattern_list	*next;
}							t_pattern_list;

typedef struct s_dir
{
	int						flag;
	DIR						*dir;
	t_args					*tmp;
	t_args					*tmp2;
	char					*tmp_name;
	struct dirent			*entry;

}							t_dirr;

typedef struct s_pcheck
{
	int						i;
	int						path_state;
	char					**direcs;
	char					*path_value;
	char					*cmd_path;
	char					*p_denied;
}							t_pcheck;

// execute 18
void						execute_cmd(t_shelldata *shelldata);
int							execute_and_or(t_shelldata *shelldata,
								t_minishell *shell);
int							execute_subshell(t_shelldata *shelldata,
								t_minishell *shell);
void						close_pipes(t_minishell *shell);
// exec 19
void						skip_to_next_command(t_minishell **cmd,
								t_type type);
void						kill_children(t_minishell *shell);
int							wiat_for_children(t_minishell *shell);

// manage flow
void						manage_redirections(t_shelldata *shelldata,
								t_redir *redir);
void						manage_data_flow(t_shelldata *shelldata,
								t_minishell *shell);
// get next line
char						*get_next_line(t_shelldata *shelldata, int fd);
char						*ft_get_nxt_line_prc(t_shelldata *shelldata,
								t_gnlsv *v, t_gnlnsv *x, int fd);
char						*ft_strcpy(char *str, char *s);
size_t						ft_sttrchr(char *str, ssize_t *j, char c);
char						*ft_sub(char *str, char *s, ssize_t *k,
								size_t size2);
// expander her-doc
int							check_expandable_data(t_shelldata *shelldata,
								t_redir *redir);
int							expand_cases(t_shelldata *shelldata, char **str,
								t_exp *exp);
char						*expand_here_doc(t_shelldata *shelldata, char *str);
char						*extract_variable_value(char *variable, t_env *env);
int							variable_len(char *str);
char						*ft_sthreecat(char *s1, char *s2, char *s3);
int							check_heredoc_noskips(char c);
int							expand_qmark(t_shelldata *shelldata, char **str,
								t_exp *exp);
int							expand_var(t_shelldata *shelldata, char **str,
								t_exp *exp);
int							cat_expands(t_shelldata *shelldata, char **str,
								t_exp *exp);
// manage ambiguoua
int							check_ambig(t_shelldata *shelldata, t_redir *redir,
								t_redir *redirin, t_redir *redirout);
int							check_ambiguous_redir(t_shelldata *shelldata,
								t_redir *redir);

/// expand inside dquotes------------------------------------------
char						*expand_inside_dquotes(t_shelldata *shelldata,
								char *str);
int							delete_quotes_condition(char *str, t_sdquotes *sd,
								int i);
int							check_expand_condition(char *str, t_sdquotes *sd,
								int i);
void						delete_quotes(char *str, t_sdquotes *sd,
								t_exp *exp);
void						move_back(char *str, int k);

/// t_pattern operations
void						destroy_pattern_t_node(t_pattern *list);
int							add_back_pattern(t_pattern **list, char *str,
								t_type type);
void						free_pattern_t(t_pattern *list);
char						*pattern_t_str(t_pattern *list);

//----------------------------------------------------------------
int							extract_len(t_args *args);
void						extract_clean_args_helper(t_shelldata *shelldata,
								t_minishell *shell);
void						extract_clean_args(t_shelldata *shelldata,
								t_minishell *shell);

// tokenize string
t_pattern					*tokenize_string(t_shelldata *shelldata, char *str);
int							extract_word_len(const char *str, int i);

// extract_env_var_token-------------------------------------------
void						extract_env_var_token(t_shelldata *shelldata,
								t_pattern **list, char *str, int k);
int							check_split_chars(char c);

// join_near_words-----------------------------------------------
void						join_near_words(t_shelldata *shelldata,
								t_pattern **pattern);

// create pattern_list---------------------------------------------------
void						free_pattern_list_t(t_pattern_list *pattern_list);
t_pattern_list				*create_pattern(t_shelldata *shelldata, char *str);
t_pattern_list				*create_pattern_list(t_shelldata *shelldata,
								t_pattern **list);

// clean_expand_wildcard----------------------------------------------
t_args						*clean_expand_wildcard(t_shelldata *shelldata,
								t_args *arg);
t_args						*clean_expand_wildcard_helper(
								t_shelldata *shelldata,
								t_pattern_list *pattern_list);

// pattern_match_checker--------------------------------------------------
int							check_pattern_new(t_pattern *pattern, char *str);

// add args sorted------------------------------------------------------------
int							add_args_sorted(t_args **args_list, char *str,
								int is_cmd);
int							add_args_word_back(t_args **args_list, char *str,
								int is_cmd);
void						add_args_node_back(t_args **args_list,
								t_args *new_args);

// check_wild_exp_auotes------------------------------------------------
int							check_wild_exp_out_quotes(char *str);
void						check_wild_exp_out_quotes_helper(char *str,
								t_sdquotes *sd, int i);
int							check_quotes_flags(char *str, t_sdquotes sd, int i);

char						*extract_path(t_shelldata *shelldata, char *str);
void						check_stat_errno(t_shelldata *shelldata, char *str);
int							cmd_normal_check(t_shelldata *shelldata, char *str);
int							cmd_path_check(t_shelldata *shelldata,
								char *cmd_path, t_pcheck *pcheck);

//----extract_env----------------------
int							env_length(t_env *env);
void						extract_execve_env(t_shelldata *shelldata,
								t_minishell *shell);

#endif