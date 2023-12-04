/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:41:31 by psousa            #+#    #+#             */
/*   Updated: 2023/11/16 10:41:35 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

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
		if (check_input(command) == 0)
		{
			token_lst = lexer(command);
			if (!check_for_errors_in_redirect(token_lst))
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
	return (g_exit_status);
}
