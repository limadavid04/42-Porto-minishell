/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:13 by dlima             #+#    #+#             */
/*   Updated: 2023/12/05 10:56:46 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	execute(t_status *status, char **cmd, int default_fd[2])
{
	int pid;

	if (!cmd[0] || !validate_cmd(&cmd[0], status))
		return ;
	// printf("in execute cmd = %s\n", cmd[0]);
	status->process_count++;
	pid = fork();
	signals_exec();
	if (pid != 0)
		status->last_pid = pid;
	else
	{
		if (status->old_pipe_in != -1)
			close(status->old_pipe_in);
		close(default_fd[IN]);
		close(default_fd[OUT]);
		if (execve(cmd[0], cmd, status->envp) == -1)
		{
			print_error(errno, strerror(errno), cmd[0]);
			lst_clear(status->token_lst);
			free(status->token_lst);
			matrix_free(cmd);
			free(status);
		}
		exit(0);
	}
}
