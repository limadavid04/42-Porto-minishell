/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:13 by dlima             #+#    #+#             */
/*   Updated: 2023/12/04 12:36:17 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_path(char **envp)
{
	int	i;
	int	j;
	char *path_name;

	path_name = ft_strdup("PATH=");
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (path_name[j] != '\0')
		{
			if (envp[i][j] == path_name[j])
				j++;
			else
				break ;
		}
		if (j == 5)
		{
			free(path_name);
			return (envp[i] + 5);
		}
		i++;
	}
	free(path_name);
	return (NULL);
}
char *get_file_full_path(char *cmd, char *dir)
{
	char *file;
	char *slash_cmd;

	slash_cmd = ft_strjoin("/", cmd);
	file = ft_strjoin(dir, slash_cmd);
	free(slash_cmd);
	return (file);
}
char	*search_for_file(char *cmd, t_status *status)
{
	char *path;
	char **dir;
	int	i;
	char *file;

	i = 0;
	path = get_path(status->envp);
	if (path == NULL)
		return (NULL);
	dir = ft_split(path, ':');
	while (dir[i])
	{
		file = get_file_full_path(cmd, dir[i]);
		if (!access(file, F_OK))
		{
			matrix_free(dir);
			return (file);
		}
		free(file);
		i++;
	}
	matrix_free(dir);
	return (NULL);
}

int	get_absolute_path(char **cmd, t_status *status)
{

	char *new_command;

	if (*cmd[0] == '.' || *cmd[0] == '/')
		return (1);
	if (!access(*cmd, F_OK))
		return (1);
	new_command = search_for_file(*cmd, status);
	if (new_command == NULL)
		return (0);
	else
	{
		free(*cmd);
		*cmd = new_command;
		return (1);
	}
	return (0);
}
void	execute(t_status *status, char **cmd, int default_fd[2])
{
	int pid;

	if (!cmd[0] || !get_absolute_path(&cmd[0], status))
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
			perror("minishell");
			lst_clear(status->token_lst);
			free(status->token_lst);
			matrix_free(cmd);
			free(status);
		}
		exit(0);
	}
}
