#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stddef.h>

typedef struct stateVar
{
	int quote;                   // 0- {no quote}; 1- single quote; 2- double quote;
	int inside_word;             // 0 if not inside word; 1-

}   t_state;

void 	lexer(char *cmd);
int		check_next_char(char *c);
int		is_whitespace(char c);
int		is_special_char(char c);
void	printLinkedList(t_list* head);
void	lst_clear(t_list **lst);


#endif
