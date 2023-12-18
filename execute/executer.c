/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:13 by dlima             #+#    #+#             */
/*   Updated: 2023/12/18 11:39:43 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	throw_execve_error(char **cmd, t_status *status)
{
	print_error(errno, strerror(errno), cmd[0]);
	lst_clear(status->token_lst);
	free(status->token_lst);
	matrix_free(cmd);
	matrix_free(status->envp);
	free_env(status->env);
	free_exp(status->exp);
	free(status);
	exit(g_exit_status);
}

void	execute(t_status *status, char **cmd)
{
	int	pid;

	if (!cmd[0] || !validate_cmd(&cmd[0], status))
		return ;
	status->process_count++;
	pid = fork();
	signals_exec();
	if (pid != 0)
		status->last_pid = pid;
	else
	{
		if (status->old_pipe_in != -1)
			close(status->old_pipe_in);
		close(status->default_fd[IN]);
		close(status->default_fd[OUT]);
		status->envp = array_env(status);
		if (execve(cmd[0], cmd, status->envp) == -1)
			throw_execve_error(cmd, status);
	}
}
