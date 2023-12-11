/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:32:38 by dlima             #+#    #+#             */
/*   Updated: 2023/12/11 16:23:37 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

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

void	init(t_status *status)
{
	status->env = NULL;
	status->exp = NULL;
	status->last_pid = 0;
}

void	init_status(t_status *status, t_list **token_lst)
{
	status->old_pipe_in = -1;
	status->process_count = 0;
	status->token_lst = token_lst;
}
int	main(int argc, char **argv, char **envp)
{
	char		*command;
	t_status	*status;
	t_list		**token_lst;

	(void)argc;
	(void)argv;
	status = malloc(sizeof(t_status));
	init(status);
	create_env(status, envp);
	create_exp(status, envp);
	status->envp = envp;
	while (1)
	{
		sig_handling();
		command = readline("$> ");
		if (handle_ctrl_d(command))
			break ;
		add_history(command);
		if (missing_quotes(command))
			print_error(SYNTAX_ERROR, "Missing Quotes" ,"minishell");
		else
		{
			token_lst = lexer(command);
			init_status(status, token_lst);
			if (!(!check_for_errors_in_redirect(token_lst) || !check_for_pipe_errors(token_lst)))
			{
				parser_main(status);
				if (status->last_pid != 0)
					wait_for_children(status);
			}
			lst_clear(token_lst);
			free(token_lst);
		}
		free(command);
	}
	free_env(status->env);
	free_exp(status->exp);
	free(status);
	return (g_exit_status);
}
