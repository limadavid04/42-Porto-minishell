/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:32:38 by dlima             #+#    #+#             */
/*   Updated: 2023/11/16 18:03:27 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DO:
// write function to check for >>>> and <<<< and ||| etc
//Parser

//MAKE FILE IS NOT CLEANING THE minishell BINARY!!
#include "minishell.h"

void	sigint_handler()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	handle_ctrl_d(char *cmd)
{
	if (!cmd)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

void	sig_handling(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

bool	checkQuotes(const char *str)
{
	int len = strlen(str);
	int doubleQuoteCount = 0;
	int singleQuoteCount = 0;
	bool insideDoubleQuotes = false;
	int i = 0;

	while (i < len)
	{
		if (str[i] == '"')
		{
			doubleQuoteCount++;
			insideDoubleQuotes = !insideDoubleQuotes;
		}
		else if (str[i] == '\'' && !insideDoubleQuotes)
		{
			singleQuoteCount++;
		}
		i++;
	}
	return (doubleQuoteCount % 2 == 0 && singleQuoteCount % 2 == 0);
}
int	wait_for_children(t_status *status)
{
	int	exit_code;

	waitpid(status->last_pid, &exit_code, 0);
	status->process_count--;
	while (status->process_count != 0)
	{
		wait(0);
		status->process_count--;
	}
	return (exit_code);
}
int	main()
{
	char		*command;
	t_status	*status;
	t_list		**token_lst;

	status = malloc(sizeof(t_status));
	// status->last_pid = 0;
	while (1)
	{
		sig_handling();
		command = readline("$> ");
		if (handle_ctrl_d(command))
			break ;
		add_history(command);
		if (!checkQuotes(command))
		{
			printf("Error: Missing Quotes\n");
		}
		else
		{
			token_lst = lexer(command);
			parser_main(token_lst, status);
			wait_for_children(status);
			lst_clear(token_lst);
			free(token_lst);
		}
		free(command);
	}
	return (0);
}
