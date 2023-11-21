/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:13 by dlima             #+#    #+#             */
/*   Updated: 2023/11/21 11:19:06 by dlima            ###   ########.fr       */
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
void	execute(t_status *status, char **cmd, int default_fd[2])
{
	int pid;
	//check path
	//check if it is executable in current working dir
	//check if it exists in any of the PATH Dir

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
		// printf("cmd = %s\n", cmd[0]);
		//clonar o path antes the passar para o child
		if (execvp(cmd[0], cmd) == -1)
		{
			//dar free as merdas
			printf("command not found");
		}
		exit(0);
	}
	// return ;
}
