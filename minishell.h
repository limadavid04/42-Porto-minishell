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
void	sigint_handler(int sig);
void	sig_handling(void);
#endif
