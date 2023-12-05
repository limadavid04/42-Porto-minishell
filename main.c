/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:32:38 by dlima             #+#    #+#             */
/*   Updated: 2023/12/05 14:14:57 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	g_exit_status;

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

	if (waitpid(status->last_pid, &exit_code, 0) != -1)
	{
		status->process_count--;
		if (WIFEXITED(exit_code))
			g_exit_status = WEXITSTATUS(exit_code);
		status->last_pid = 0;
	}
	while (status->process_count != 0)
	{
		wait(0);
		status->process_count--;
	}
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	t_status	*status;
	t_list		**token_lst;

	(void)argc;
	(void)argv;
	status = malloc(sizeof(t_status));
	status->last_pid = 0;
	while (1)
	{
		sig_handling();
		command = readline("$> ");
		if (handle_ctrl_d(command))
			break ;
		add_history(command);
		if (!checkQuotes(command))
		{
			print_error(SYNTAX_ERROR, "Missing Quotes" ,"minishell");
			g_exit_status = 2;
		}
		else
		{
			token_lst = lexer(command);
			if (!check_for_errors_in_redirect(token_lst) || !check_for_pipe_errors(token_lst))
			{
				lst_clear(token_lst);
				free(token_lst);
				free(command);
				continue ;
			}
			parser_main(token_lst, status, envp);
			if (status->last_pid != 0)
				wait_for_children(status);
			lst_clear(token_lst);
			free(token_lst);
		}
		free(command);
	}
	free(status);
	return (0);
}
