#ifndef LEXER_H
# define LEXER_H

# include "./libft.h"
# include <stddef.h>

# define SPACE " \t\n\v\f\r"
# define OPERATOR "|><&()"

typedef struct stateVar
{
	int quote;                   // 0- {no quote}; 1- single quote; 2- double quote;
	int inside_word;             // 0 if not inside word; 1- 

}   t_state;

typedef struct s_tokens
{
	void			*content;
	struct s_tokens	*next;
}					t_tokens;

// typedef struct chars
// {
 
// }   t_chars;

#endif