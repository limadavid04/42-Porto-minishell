/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:33:32 by dlima             #+#    #+#             */
/*   Updated: 2023/12/18 14:28:23 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_executable_file(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	else
		return (0);
}

int	is_directory(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
	{
		perror("stat");
		return (0);
	}
	stat(cmd, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
