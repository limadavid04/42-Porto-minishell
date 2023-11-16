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
#include <sys/wait.h>

# define IN 0
# define OUT 1

typedef struct Status
{
	int		last_pid;
	int		process_count;
	int		old_pipe_in;
	//env;
	//export;
}	t_status;

typedef struct TapeInfo
{
	t_list	**head;
	t_list	*node;
	char	*cmd;
	int		*i;
	int		quote;
	int		inside_word;
}	t_info;

////////////////////////////////////////////----LEXER-----////////////////////////////////////////////

//lexer
t_list	**lexer(char *cmd);
void	get_tokens(t_info *info);

//lexer_utils
int		find_next_delimiter(char *cmd);
int		check_next_char(char *c);;
void	print_linked_list(t_list *head);
void	lst_clear(t_list **lst);
t_list	*create_token(t_list **head, t_list *node, int *i, char *cmd);

//lexer_utils_1
int		is_whitespace(char c);
int		is_special_char(char c);
int		is_double_quote(char c);
int		is_single_quote(char c);
int		is_dollar(char c);

//lexer_utils_2
char	*add_char(char c, char *content);
t_list	*handle_special(t_list **head, t_list *node, int *i, char *cmd);
char	*add_char(char c, char *content);
t_list	*create_space_for_expansion(t_info *info, char *var);
t_list	*expand_var(t_info *info);

///////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////----PARSER-----////////////////////////////////////////////

//parser
void	parser_main(t_list **token_lst,  t_status *status);
void	execute(t_status *status, char **cmd, int default_fd[2]);

//parser_utils
void	save_default_fd(int default_fd[2]);
void	matrix_free(char **matrix);
int		command_length(t_list *cmd_start, t_list *pipe_tkn);
void	restore_default_fd(int default_fd[2]);
///////////////////////////////////////////////////////////////////////////////////////////////////////

// main.c
int	handle_ctrl_d(char *cmd);
void sigint_handler();
void sig_handling();
bool checkQuotes(const char* str);

#endif
