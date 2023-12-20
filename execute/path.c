/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:01:17 by dlima             #+#    #+#             */
/*   Updated: 2023/12/19 12:34:18 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_file_full_path(char *cmd, char *dir)
{
	char	*file;
	char	*slash_cmd;

	slash_cmd = ft_strjoin("/", cmd);
	file = ft_strjoin(dir, slash_cmd);
	free(slash_cmd);
	return (file);
}

static char	*find_exec_bin(char **dir, char *cmd)
{
	char	*file;
	int		i;

	i = 0;
	while (dir[i])
	{
		file = get_file_full_path(cmd, dir[i]);
		if (!access(file, F_OK) && !is_directory(file) \
		&& is_executable_file(file))
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

static char	*search_for_file(char *cmd, t_status *status)
{
	char	*path;
	char	**dir;

	path = get_env("PATH", status);
	if (path == NULL)
		return (NULL);
	dir = ft_split(path, ':');
	return (find_exec_bin(dir, cmd));
}

static int	is_valid_relative_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (is_directory(cmd))
		{
			print_error(CMD_CANNOT_EXECUTE, "Is a directory", cmd);
			return (0);
		}
		else if (!is_executable_file(cmd))
		{
			print_error(CMD_CANNOT_EXECUTE, "permission denied", cmd);
			return (0);
		}
		else
			return (1);
	}
	print_error(CMD_NOT_FOUND, "No such file or directory", cmd);
	return (0);
}

int	validate_cmd(char **cmd, t_status *status)
{
	char	*executable;

	if (!ft_strncmp(*cmd, "", ft_strlen(*cmd)))
	{
		print_error(CMD_NOT_FOUND, "Command not found", "''");
		return (0);
	}
	if (ft_strchr(*cmd, '/') != 0)
		return (is_valid_relative_path(*cmd));
	executable = search_for_file(*cmd, status);
	if (executable == NULL)
		print_error(CMD_NOT_FOUND, "Command not found", *cmd);
	else
	{
		free(*cmd);
		*cmd = executable;
		return (1);
	}
	return (0);
}
