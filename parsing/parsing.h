/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:44:04 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 14:55:30 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define F_ENV 1
# define F_LINE 2
# define F_CMD 4
# define F_SHELL 8
# define COL_MINI "\001\033[1;38;5;15;48;5;161m\002"
# define COL_PATH "\001\033[1;38;5;26;48;5;51m\002"
# define COL_USER "\001\033[1;38;5;3;48;5;220m\002"
# define ARROW_PINK2CYAN "\001\033[38;5;161;48;5;51m\002\001\002"
# define ARROW_CYAN2GOLD "\001\033[1;38;5;51;48;5;220m\002\001\002"
# define ARROW_GOLD2DEF "\001\033[38;5;220;49m\002"
# define ARROW_CYAN2DEF "\001\033[38;5;51;49m\002\001\002"
# define CLR_RESET "\001\033[0m\002"

extern volatile sig_atomic_t	g_sigint;

typedef enum e_type
{
	C_CMD = -1,
	NONE = 0,
	WORD = 1,
	C_PARENTHES = 2,
	O_PARENTHES = 3,
	PIPE = 4,
	AND = 5,
	OR = 6,
	HEREDOC = 7,
	APPEND = 8,
	INFILE = 9,
	OUTFILE = 10,
	INFILE_NAME = 11,
	OUTFILE_NAME = 12,
	APPEND_NAME = 13,
	DELIMITER = 14,
	WILDCARD = 15,
	EXPANSION = 16,
	S_PACE = 17,
	PATTERN = 18
}								t_type;

typedef struct s_sdquotes
{
	int							sflag;
	int							dflag;
	int							scount;
	int							dcount;
}								t_sdquotes;

typedef struct s_eraseq
{
	int							i;
	int							j;
	int							len;
	int							dollar_c;
}								t_eraseq;

typedef struct s_hdocfree
{
	int							fd;
	char						*s;
}								t_hdocfree;

typedef struct s_cmds
{
	t_type						type;
	char						*str;
	int							herdocfd;
	struct s_cmds				*next;
	struct s_cmds				*previous;
}								t_cmds;

typedef struct s_cmdsplit
{
	int							i;
	int							j;
}								t_cmdsplit;

typedef struct s_args
{
	char						*str;
	int							is_cmd;
	struct s_args				*next;
}								t_args;

typedef struct s_redir
{
	t_type						type;
	char						*redir_name;
	int							redirfd;
	struct s_redir				*next;
}								t_redir;

typedef struct s_minishell
{
	pid_t						pid;
	int							pipefd[2];
	int							args_extracted;
	int							exp_split;
	char						*path;
	char						**args;
	t_args						*args_list;
	char						**env;
	t_type						type;
	t_redir						*redir;
	struct s_minishell			*next;
	struct s_minishell			*c_cmd;
	struct s_minishell			*previous;
}								t_minishell;

typedef struct s_env
{
	char						*variable;
	char						*value;
	int							ev_hide;
	struct s_env				*next;
}								t_env;

typedef struct s_shelldata
{
	t_env						*env;
	t_cmds						*cmd;
	t_minishell					*shell;
	char						*line;
	char						*cwd;
	void						*sigint_h;
	void						*sigquit_h;
	int							state;
	int							std_incpy;
	int							std_outcpy;
	int							lvl;
	int							exit_status;
}								t_shelldata;

typedef struct s_data
{
	t_type						type;
	t_args						*args;
	t_minishell					*c_cmd;
	t_redir						*redir;
}								t_data;

// parsing split line
int								t_cmd_addback(t_shelldata *shelldata,
									char *content);
void							free_t_cmds(t_cmds *cmd, int hflag);
int								is_white_spaces(char c);
int								is_operation(char c);
int								is_parenthesis(char c);
int								is_skippable(char c);
void							error_message(char *str);
t_type							check_type(t_cmds *new, char *str);
int								split_line(t_shelldata *shelldata);
void							parse_line(t_shelldata *shelldata);

// syntax
int								is_type_operation(t_type type);
int								is_type_redirection(t_type type);
int								is_type_file(t_type type);
int								is_type_parenthesis(t_type type);
int								is_type_symbole(t_type type);
int								check_parsing(t_shelldata *shelldata);
int								c_parenthes_checker(t_cmds *list, int *pcount,
									int *cflag);
int								operations_checker(t_cmds *list, int *cflag);
int								o_parenthes_checker(t_cmds *list, int *pcount);
int								redirection_checker(t_shelldata *shelldata,
									t_cmds **list);
// here doc
t_hdocfree						*hdoc_memo(void);
int								fill_herefoc(char *str, t_shelldata *shelldata);
char							*erase_quotes(char *str);
void							print_ctrd_msg(char *s);
char							*filepath(void);
// signal
void							sig_handler1(int sig);
void							sig_handler2(int sig);
void							sig_handler3(int sig);
void							destroy_hdoc(void);
void							sig_heredoc(int sig);

// extracting t_minishell
t_minishell						*extract_minishell_cmd(t_cmds *xarg);
t_minishell						*extract_minishell_cmd_helper(t_cmds **xarg);

// extracting t_minishell helper
int								is_indata(t_type type);
int								is_outdata(t_type type);
t_data							*init_data(void);
void							free_data(t_data *data);

// t_redir ops
t_redir							*ft_lstnew_redir_data(t_cmds *xarg);
int								t_cmd_addback_redir_data(t_data *lst,
									t_cmds *xarg);
void							free_redir(t_redir *redir);

// t_args ops
t_args							*ft_lstnew_word(t_cmds *xarg);
int								t_cmd_addback_word(t_data *lst, t_cmds *xarg);
void							free_args(t_args *args);
void							destroy_args_node(t_args *args);
void							free_strs(char **strs);

// t_minishell x t_data ops
t_minishell						*ft_lstnew_operation(t_type type);
int								t_cmd_addback_operation(t_minishell **lst,
									t_type type);
t_minishell						*ft_lstnew_cmd_data(t_data *data, t_type type);
int								t_cmd_addback_data(t_minishell **lst,
									t_data *data, t_type type);
void							free_minishell(t_minishell *minishell);

#endif