#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// typedef struct stateVar
// {
// 	int quote;                   // 0- {no quote}; 1- single quote; 2- double quote;
// 	int inside_word;             // 0 if not inside word; 1-

// }   t_state;

typedef struct TapeInfo
{
	t_list	**head;
	t_list	*node;
	char	*cmd;
	int		*i;
	int		quote;
	int		inside_word;
}	t_info;

void	lexer(char *cmd);
int		check_next_char(char *c);
int		is_whitespace(char c);
int		is_special_char(char c);
void	print_linked_list(t_list *head);
void	lst_clear(t_list **lst);
int		is_double_quote(char c);
int		is_single_quote(char c);
char	*add_char(char c, char *content);
int		is_dollar(char c);
void	get_tokens(t_info *info);
int		find_next_delimiter(char *cmd);
t_list	*create_token(t_list **head, t_list *node, int *i, char *cmd);
t_list	*handle_special(t_list **head, t_list *node, int *i, char *cmd);
char	*add_char(char c, char *content);

// main.c
int	handle_ctrl_d(char *cmd);
void sigint_handler();
void sig_handling();
bool checkQuotes(const char* str);

#endif