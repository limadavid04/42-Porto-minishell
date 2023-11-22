/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:13 by dlima             #+#    #+#             */
/*   Updated: 2023/11/22 14:42:57 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
Parent fd's -> child needs to close unused fd's
|    fd    |    file       |
|__________|_______________|
|    0     |   old_pipe_in |
|    1     |   pipe_fd[OUT]|
|    2     |  STDERR       |
|    3     |  STDIN        |
|    4     |  STDOUT       |
|    5     |  pipe_fd[IN]  |
*/
void	execute(t_status *status, char **cmd, int default_fd[2], t_list **token_lst)
{
	int pid;

	if (!cmd[0])
		return ;
	status->process_count++;
	pid = fork();
	if (pid != 0)
		status->last_pid = pid;
	else
	{//child
		if (status->old_pipe_in != -1)
			close(status->old_pipe_in);
		close(default_fd[IN]);
		close(default_fd[OUT]);
		if (execvp(cmd[0], cmd) == -1)
		{
			perror("minishell");
			lst_clear(token_lst);
			free(token_lst);
			matrix_free(cmd);
			free(status);
		}
		exit(0);
	}
	// return ;
}
