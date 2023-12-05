/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:33:32 by dlima             #+#    #+#             */
/*   Updated: 2023/12/05 12:12:05 by dlima            ###   ########.fr       */
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
int is_executable_file(char *cmd)
{
	if (access(cmd ,X_OK ) == 0)
		return (1);
	else
		return (0);
}
int is_directory(char *cmd)
{
	struct stat path_stat;

	if (stat(cmd, &path_stat) == -1) {
        perror("stat");
        return (0);
    }
    stat(cmd, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}
int is_valid_relative_path(char *cmd)
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
