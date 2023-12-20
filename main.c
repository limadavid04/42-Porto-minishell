/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:32:38 by dlima             #+#    #+#             */
/*   Updated: 2023/12/20 13:47:53 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static int	wait_for_children(t_status *status)
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

static void	init(t_status *status)
{
	status->env = NULL;
	status->exp = NULL;
	status->last_pid = 0;
}

static void	init_status_new_cmd(t_status *status, t_list **token_lst)
{
	status->old_pipe_in = -1;
	status->process_count = 0;
	status->token_lst = token_lst;
}

static int	interpret_new_command(t_status *status)
{
	char		*command;
	t_list		**token_lst;

	sig_handling();
	command = readline("$> ");
	if (handle_ctrl_d(command))
		return (1);
	add_history(command);
	if (missing_quotes(command))
		print_error(SYNTAX_ERROR, "Missing Quotes", "minishell");
	else
	{
		token_lst = lexer(command);
		init_status_new_cmd(status, token_lst);
		if (!(!check_pipe_err(token_lst) || !check_redir_err(token_lst)))
		{
			parser_main(status);
			if (status->last_pid != 0)
				wait_for_children(status);
		}
		lst_clear(token_lst);
		free(token_lst);
	}
	free(command);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_status	*status;

	(void)argv;
	if (argc != 1)
	{
		print_error(EXIT_FAILURE, TOO_MANY_ARGS_ERR, "minishell");
		return (g_exit_status);
	}
	status = malloc(sizeof(t_status));
	init(status);
	create_env(status, envp);
	create_exp(status, envp);
	while (1)
	{
		if (interpret_new_command(status))
			break ;
	}
	free_env(status->env);
	free_exp(status->exp);
	free(status);
	return (g_exit_status);
}
