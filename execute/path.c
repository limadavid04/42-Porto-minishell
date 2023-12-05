/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:01:17 by dlima             #+#    #+#             */
/*   Updated: 2023/12/05 12:03:21 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *get_file_full_path(char *cmd, char *dir)
{
	char *file;
	char *slash_cmd;

	slash_cmd = ft_strjoin("/", cmd);
	file = ft_strjoin(dir, slash_cmd);
	free(slash_cmd);
	return (file);
}
char *find_exec_bin(char **dir, char *cmd)
{
	char *file;
	int i;

	i = 0;
	while (dir[i])
	{
		file = get_file_full_path(cmd, dir[i]);
		if (!access(file, F_OK) && !is_directory(file) && is_executable_file(file))
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
char	*search_for_file(char *cmd, t_status *status)
{
	char *path;
	char **dir;

	path = get_path(status->envp);
	if (path == NULL)
		return (NULL);
	dir = ft_split(path, ':');
	return (find_exec_bin(dir, cmd));
}

int	validate_cmd(char **cmd, t_status *status)
{
	char *executable;

	if (!ft_strncmp(*cmd, "", ft_strlen(*cmd)))
	{
		print_error(CMD_NOT_FOUND, "Command not found", "''");
		return (0);
	}
	if (ft_strchr(*cmd, '/') != 0)
	{
		if (!is_valid_relative_path(*cmd))
			return (0);
		return (1);
	}
	executable = search_for_file(*cmd, status);
	if (executable == NULL)
	{
		print_error(CMD_NOT_FOUND, "Command not found", *cmd);
		return (0);
	}
	else
	{
		free(*cmd);
		*cmd = executable;
		return (1);
	}
	return (0);
}
