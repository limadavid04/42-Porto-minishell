#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stddef.h>

// typedef struct stateVar
// {
// 	int quote;                   // 0- {no quote}; 1- single quote; 2- double quote;
// 	int inside_word;             // 0 if not inside word; 1-

// }   t_state;

typedef struct TapeInfo
{
	t_list **head;
	t_list *node;
	char *cmd;
	int *i;
	int quote;                   // 0- {no quote}; 1- single quote; 2- double quote;
	int inside_word;             // 0 if not inside word; 1-


}   t_info;

void 	lexer(char *cmd);
int		check_next_char(char *c);
int		is_whitespace(char c);
int		is_special_char(char c);
void	printLinkedList(t_list* head);
void	lst_clear(t_list **lst);
int		is_double_quote(char c);
int		is_single_quote(char c);
char	*add_char(char c, char *content);
int		is_dollar(char c);


#endif
