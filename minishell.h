/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:41:47 by psousa            #+#    #+#             */
/*   Updated: 2023/11/16 10:41:50 by psousa           ###   ########.fr       */
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
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
#include <errno.h>


# define HEREDOC_FILE ".heredoc"
# define EXIT_CTRL_C 130
#define SUCCESS 0
#define GENERAL_ERROR 1
#define SYNTAX_ERROR 2
#define CMD_CANNOT_EXECUTE 126
#define CMD_NOT_FOUND 127
#define INVALID_ARGUMENT 128
# define IN 0
# define OUT 1


typedef struct s_exp {
	char			*v_name;
	char			*v_value;
	struct s_exp	*next;
}	t_exp;

typedef struct s_env {
	char			*v_name;
	char			*v_value;
	struct s_env	*next;
}	t_env;

typedef struct Status
{
	int		last_pid;
	int		process_count;
	int		old_pipe_in;
	char	**envp;
	t_list	**token_lst;
	int		*default_fd;
	char	**cmd;
	t_env	*env;
	t_exp	*exp;
}	t_status;
//env;
//export;

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
void print_error(int error_code, char *error_msg, char *file);

//utils/utils.c
long long	ft_atol(const char *str);
int		is_number(char *str);
void	free_env2(t_env *tmp);
char	*join_three(char *one, char *two, char *three);
int		is_all_digits(char *str);

// signal/signal.c
int		handle_ctrl_d(char *cmd);
void	handle_ctrl_c(int sig);
void	sig_handling(void);

// signal/exec_signal.c
void	exec_ctrl_c(int signal);
void	exec_ctrl_bslash(int signal);
void	signals_exec(void);

// lexar/lexar.c
t_list	*state_no_quote(t_info *info);
t_list	*state_double_quote(t_info *info);
t_list	*state_single_quote(t_info *info);
void	get_tokens(t_info *info);
t_list	**lexer(char *cmd);

// lexar/lexar_utils.c
int	check_next_char(char *c);
void	print_linked_list(t_list	*head);
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

// parser/parser.c
void	parser_main(t_list **token_lst, t_status *status, char **envp);
void	parse_command(t_list *cmd_start, t_list *pipe_tkn, t_status *status);
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

//parser/redirect_handler.c
int		redirect_handler(t_list *cmd_start, t_list *pipe_tkn, t_status *status);

// execute/executer.c
void throw_execve_error(char **cmd, t_status *status);
void	execute(t_status *status, char **cmd, int default_fd[2]);

// execute/path.c
char *get_file_full_path(char *cmd, char *dir);
char *find_exec_bin(char **dir, char *cmd);
char	*search_for_file(char *cmd, t_status *status);
int is_valid_relative_path(char *cmd);
int	validate_cmd(char **cmd, t_status *status);

// execute/path_utils.c
char *get_path(char **envp);
int is_executable_file(char *cmd);
int is_directory(char *cmd);

// builtins/b_cd.c
void	update_oldpwd(t_status *status);
int		handle_cd(char *path, t_status *status);
int		go_old_path(char **path, t_status *status);
void	b_cd(t_status *status, char **cmd);

// builtins/b_echo.c
void	print_words(char **word, int i, int flag);
int		ft_strcmp(char *s1, char *s2);
void	b_echo(char **cmd);

// builtins/b_exit.c
void	exit_args(char **cmd);
void	b_exit(char **cmd);

// builtins/b_export.c
void	single_export(t_status *status, char *key);
int		valid_export(char *key, char *type);
void	export_single(char *cmd, t_status *status);
void	b_export(t_status *status, char **cmd);

// builtins/b_export1.c
void	free_exp2(t_exp *tmp);
void	free_exp(t_exp *exp);
t_exp	*new__exp(char *vexp_name, char *vexp_value);
void	add_exp(t_exp **exp, t_exp *new);
void	exp_create(t_status *status, char **exp);

// builtins/b_export2.c
t_exp	*search_exp(char *name, t_status *status);
int	set_exp(char *name, char *new_value, t_status *status);
char	*get_exp(char *name, t_status *status);
void	print_exp(t_status *status);

// builtins/b_pwd.c
void	b_pwd(void);

// builtins/b_unset.c
void	unset_env(t_status *status, char *key);
void	unset_exp(t_status *status, char *key);
int		valid_unset(char *key, char *type);
void	b_unset(t_status *status, char **cmd);

// builtins/builtins.c
void	x_commands(char **cmd, t_status *status);
int		commands(char **cmd);

//enviroment/enviro.c
void	free_env(t_env *env);
t_env	*new_env(char *v_name, char *v_value);
t_env	*get_last_env(t_env *env);
void	env_back(t_env **env, t_env *new);
void	create_env(t_status *status, char **env);

//enviroment/enviro2.c
int		set_env(char *key, char *newvalue, t_status *status);
void	print_env(t_status *status);
char	**array_env(t_status *status);
t_env	*search_env(char *name, t_status *status);
char	*get_env(char *name, t_status *status);

#endif
