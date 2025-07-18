# ───────────────────────────── core files ────────────────────────────────
CORE_SRCS := \
    1-minishell.c \
    2-prompt_minishell.c \
    3-minishell_helper.c \
    4-t_env_set_env.c

# ───────────────────────────── built-ins files ───────────────────────────
BUILTIN_SRCS := \
    builtins/55-ft_pwd.c \
    builtins/ft_export/57-ft_export_helper.c \
    builtins/ft_export/58-ft_export_helper_2.c \
    builtins/ft_export/56-ft_export.c \
    builtins/ft_cd/60-ft_cd_helper.c \
    builtins/ft_cd/59-ft_cd.c \
    builtins/51-ft_exit.c \
    builtins/50-check_builtin.c \
    builtins/54-ft_unset.c \
    builtins/52-ft_echo.c \
    builtins/53-ft_env.c

# ───────────────────────────── execution files ──────────────────────────
EXEC_SRCS := \
    execution/1-manage_data_flow/25-manage_data_flow.c \
    execution/1-manage_data_flow/26-manage_data_flow_helper.c \
    execution/1-manage_data_flow/27-handle_ambiguous_redirection.c \
    execution/1-manage_data_flow/here_doc_redirection/32-heredoc_expander_helper.c \
    execution/1-manage_data_flow/here_doc_redirection/28-manage_herdoc_expansion.c \
    execution/1-manage_data_flow/here_doc_redirection/29-get_next_line.c \
    execution/1-manage_data_flow/here_doc_redirection/30-get_next_line_utils.c \
    execution/1-manage_data_flow/here_doc_redirection/31-heredoc_expander.c \
    execution/23-execution_subshell.c \
    execution/22-execution.c \
    execution/24-execution_helper.c \
    execution/2-extract_clean_args/2-expansion_inside_quotes/39-expand_inside_quotes_helper.c \
    execution/2-extract_clean_args/2-expansion_inside_quotes/37-extract_word_len.c \
    execution/2-extract_clean_args/2-expansion_inside_quotes/38-expand_inside_dquotes.c \
    execution/2-extract_clean_args/32-extract_clean_args.c \
    execution/2-extract_clean_args/46-check_wild_exp_out_quotes.c \
    execution/2-extract_clean_args/4-create_pattern_list/42-extract_pattern_list.c \
    execution/2-extract_clean_args/3-expansion_outside_quotes/41-join_pattern_t_near_words.c \
    execution/2-extract_clean_args/3-expansion_outside_quotes/40-extract_env_var_token.c \
    execution/2-extract_clean_args/33-extract_clean_args_helper.c \
    execution/2-extract_clean_args/5-wildcard/43-extract_wildcards_args.c \
    execution/2-extract_clean_args/5-wildcard/44-check_pattern_match.c \
    execution/2-extract_clean_args/1-create_pattern/36-tokenize_string_to_pattern.c \
    execution/2-extract_clean_args/1-create_pattern/35_pattern_t_operations.c \
    execution/2-extract_clean_args/1-create_pattern/34-create_pattern.c \
    execution/2-extract_clean_args/45-add_args_t_in_order.c \
    execution/4-extract_execve_env/49-extrcat_execve_env.c \
    execution/3-extract_path/47-extract_path.c \
    execution/3-extract_path/48-extract_path_helper.c

# ───────────────────────────── parsing files ────────────────────────────
PARSING_SRCS := \
    parsing/3-here_doc/13-t_cmd_heredoc.c \
    parsing/3-here_doc/14-t_cmd_heredoc_helper.c \
    parsing/3-here_doc/15-t_cmd_skip_quotes.c \
    parsing/3-here_doc/16-t_cmd_signals.c \
    parsing/5-parse_line.c \
    parsing/1-split_line/7-t_cmd_list.c \
    parsing/1-split_line/6-t_cmd_parsing.c \
    parsing/1-split_line/9-t_cmd_type_check.c \
    parsing/1-split_line/8-t_cmd_helper.c \
    parsing/2-syntax_check/11-t_cmd_syntax_error_helper.c \
    parsing/2-syntax_check/10-t_cmd_syntax_error.c \
    parsing/2-syntax_check/12-t_cmd_syntax_helper.c \
    parsing/4-extract_t_minishell_cmd/data_structures_operations/20-t_args_tot_data_operations.c \
    parsing/4-extract_t_minishell_cmd/data_structures_operations/19-t_redir_tot_data_operations.c \
    parsing/4-extract_t_minishell_cmd/data_structures_operations/21-t_data_to_t_minishell.c \
    parsing/4-extract_t_minishell_cmd/18-t_minishell_extraction_helper.c \
    parsing/4-extract_t_minishell_cmd/17-t_minishell_extraction.c

# ─────────────────────────────  all source files ───────────────────────
SRCS := ${CORE_SRCS} ${BUILTIN_SRCS} ${EXEC_SRCS} ${PARSING_SRCS}

OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./libft
INCLUDE = -L ./libft -lft
CMAKE = make -C
LIBFTDIR = libft/
LIBFT = ./libft/libft.a
LIBS = minishell.h builtins/builtins.h parsing/parsing.h execution/execution.h

all: ${NAME}

%.o: %.c ${LIBS}
	$(CC) $(CFLAGS) -c $< -o $@

${LIBFT}:
	${CMAKE} ${LIBFTDIR}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} -lreadline -o ${NAME} ${INCLUDE}


clean:
	${CMAKE} ${LIBFTDIR} clean
	${RM} ${OBJS}

fclean: clean
	${CMAKE} ${LIBFTDIR} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean all re