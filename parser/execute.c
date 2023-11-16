/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:13 by dlima             #+#    #+#             */
/*   Updated: 2023/11/16 19:12:22 by dlima            ###   ########.fr       */
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
    // char *args[] = {"ls", "-l", NULL};
	// (void)cmd;

	status->process_count++;
	pid = fork();
	if (pid != 0)
		status->last_pid = pid;
	else
	{//child
		printf("cmd = %s\n", cmd[0]);
		printf("arg = %s\n", cmd[1]);
		if (status->old_pipe_in != -1)
			close(status->old_pipe_in);
		close(default_fd[IN]);
		close(default_fd[OUT]);
		// execve("/bin/cat:/bin/ls", cmd);
		// execvp(cmd[0], cmd);
		exit(0);
	}
	// return ;
}
