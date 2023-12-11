/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:41:47 by psousa            #+#    #+#             */
/*   Updated: 2023/12/11 13:08:23 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
#include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# define HEREDOC_FILE ".heredoc"
# define SYNTAX_MSG "minishell: syntax error near unexpected token "
# define EXIT_CTRL_C 130
#define SUCCESS 0
#define GENERAL_ERROR 1
#define SYNTAX_ERROR 2
#define CMD_CANNOT_EXECUTE 126
#define CMD_NOT_FOUND 127
#define INVALID_ARGUMENT 128
# define IN 0
# define OUT 1

extern int g_exit_status;

typedef struct Status
{
	int		last_pid;
	int		process_count;
	int		old_pipe_in;
	char	**envp;
	t_list	**token_lst;
	int		*default_fd;
	char	**cmd;
}	t_status;

typedef struct Heredoc
{
	t_status	*status;
	int			fd;
	char		*delim;
}	t_heredoc;


typedef struct TapeInfo
{
	t_list	**head;
	t_list	*node;
	char	*cmd;
	int		*i;
	int		quote;
	int		inside_word;
}	t_info;

// main.c
int		wait_for_children(t_status *status);

// utils/quotes.c
bool	missing_quotes(const char *str);
bool	invalid_redirects(const char *str);
bool	check_input(const char *str);
// utils/utils.c
void print_error(int error_code, char *error_msg, char *file);
void print_syntax_err(struct s_list *token);

// lexar/lexar.c
t_list	*state_no_quote(t_info *info);
t_list	*state_double_quote(t_info *info);
t_list	*state_single_quote(t_info *info);
void	get_tokens(t_info *info);
t_list	**lexer(char *cmd);

// lexar/lexar_utils.c
int		find_next_delimiter(char *cmd);
int		check_next_char(char *c);
void	print_linked_list(t_list *head);
void	lst_clear(t_list **lst);
t_list	*create_token(t_list **head, t_list *node, int *i, char *cmd);

// lexar/lexar_utils1.c
int		is_whitespace(char c);
int		is_special_char(char c);
int		is_dollar(char c);
int		is_single_quote(char c);
int		is_double_quote(char c);

// lexar/lexar_utils2.c
t_list	*handle_special(t_list **head, t_list *node, int *i, char *cmd);
char	*add_char(char c, char *content);
int		check_for_errors_in_redirect(t_list	**token_lst);
int		check_for_pipe_errors(t_list **token_lst);

// signal/signal.c
int		handle_ctrl_d(char *cmd);
void	handle_ctrl_c(int sig);
void	sig_handling(void);

// signal/exec_signal.c
void	exec_ctrl_c(int signal);
void	exec_ctrl_bslash(int signal);
void	signals_exec(void);

// signal/signal_heredoc.c
void	signals_heredoc(t_heredoc *heredoc);


// parser/parser.c
void	parser_main(t_status *status);
// void	parse_tokens(t_list *token_lst, t_status *status);
// void	parse_CMD(t_list *cmd_start, t_list *pipe_tkn, t_status *status);
void	create_pipe(t_status *status, t_list *pipe_tkn);
char	**get_cmd(t_list *cmd_start, t_list *pipe_tkn);

// parser/parser_utils.c
void	save_default_fd(int default_fd[2]);
void	restore_default_fd(int default_fd[2]);
int		command_length(t_list *cmd_start, t_list *pipe_tkn);
void	matrix_free(char **matrix);
int		count_redir(t_list *cmd_start, t_list *pipe_tkn);

// parser/parser_utils1.c
int		is_redir(t_list *cmd);

// parser/parser_utils2.c
char	**strip_tokens(char **cmd);
char	*expand_var(char *new_token, char *token, int *i);
char	*process_tokens(char *token, int expand);


//parser/redirect_handler.c
int		redirect_handler(t_list *cmd_start, t_list *pipe_tkn, t_status *status);

//parser/heredoc.c
void	create_heredoc_subprocess(char *delim, t_status *status);
void	free_heap(t_status *status, char *delim, int fd);


// execute/executer.c
void	execute(t_status *status, char **cmd, int default_fd[2]);

// execute/path.c
int		validate_cmd(char **cmd, t_status *status);

// execute/path_utils.c
char	*get_path(char **envp);
int		is_executable_file(char *cmd);
int		is_directory(char *cmd);
int		is_valid_relative_path(char *cmd);


// builtins/b_cd.c
/*
void	update_oldpwd(t_data *data);
int		handle_cd(char *path, t_data *data);
int		go_old_path(char **path, t_data *data);
void	b_cd(t_data *data, char **cmd)
*/

// builtins/b_echo.c
/*
void	print_words(char **word, int i, int flag);
void	b_echo(char **cmd);
*/

// builtins/b_exit.c
/*
void	two_args(char **cmd, t_state *state);
void 	b_exit(char **cmd);
*/

// builtins/b_export.c
// builtins/b_pwd.c
// builtins/b_unset.c
// builtins/builtins.c
/*
void	x_commands(char **cmd, t_data *data);
int		commands(char **cmd);
*/
#endif
