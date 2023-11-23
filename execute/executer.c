/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:13 by dlima             #+#    #+#             */
/*   Updated: 2023/11/21 12:50:45 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_status *status, char **cmd, int default_fd[2])
{
	int	pid;

	if (!cmd[0])
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
		close(default_fd[IN]);
		close(default_fd[OUT]);
		if (execvp(cmd[0], cmd) == -1)
			printf("%s: command not found\n", cmd[0]);
		exit(0);
	}
}
