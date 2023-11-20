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

# define HEREDOC_FILE ".heredoc"

typedef struct TapeInfo
{
	t_list	**head;
	t_list	*node;
	char	*cmd;
	int		*i;
	int		quote;
	int		inside_word;
}	t_info;

typedef struct s_env {
	char			*v_name;
	char			*v_value;
	struct s_env	*next;
}	t_env;

// main.c


// utils/quotes.c
bool	missing_quotes(const char *str);
bool	invalid_redirects(const char *str);
bool	check_input(const char *str);

// lexar/lexar.c
t_list	*state_no_quote(t_info *info);
t_list	*state_double_quote(t_info *info);
t_list	*state_single_quote(t_info *info);
void	get_tokens(t_info *info);
void	lexer(char *cmd);

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
t_list	*create_space_for_expansion(t_info *info, char *var);
t_list	*expand_var(t_info *info);

// signal/signal.c
int		handle_ctrl_d(char *cmd);
void	sig_handling(void);

// builtins/b_cd.c
void	update_oldpwd(t_data *data);
int		handle_cd(char *path, t_data *data);
int		go_old_path(char **path, t_data *data);
void	b_cd(t_data *data, char **cmd)

// builtins/b_echo.c
void	print_words(char **word, int i, int flag);
void	b_echo(char **cmd);

// builtins/b_exit.c
void	two_args(char **cmd, t_state *state);
void 	b_exit(char **cmd);

// builtins/b_export.c


// builtins/b_pwd.c


// builtins/b_unset.c


// builtins/builtins.c
void	x_commands(char **cmd, t_data *data);
int		commands(char **cmd);
#endif
