/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:26:49 by psousa            #+#    #+#             */
/*   Updated: 2023/11/22 12:26:52 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

void	update_oldpwd(t_status *status)
{
	char	newpwd[256];

	getcwd(newpwd, sizeof(newpwd));
	set_env("OLDPWD", get_enviro("PWD", status), status);
	set_env("PWD", newpwd, status);
}

int	handle_cd(char *path, t_status *status)
{
	if (!path)
		g_exit_status = 127;
	else
		g_exit_status = chdir(path);
	if (g_exit_status == 127)
		return (g_exit_status);
	update_oldpwd(status);
	return (g_exit_status);
}

int	go_old_path(char **path, t_status *status)
{
	*path = get_enviro("OLDPWD", status);
	if (!*path)
	{
		printf("OLDPWD not set\n");
		g_exit_status = 1;
		return (1);
	}
	printf("%s\n", get_enviro("OLDPWD", status));
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	b_cd(t_status *status, char **cmd)
{
	char	*path;

	path = cmd[1];
	if (cmd[1] && cmd[2])
	{
		printf("too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (path == NULL || *path == '\0')
		path = get_enviro("HOME", status);
	else if (*path == '-' && *(path + 1) == '-' && *(path + 2) == '\0')
		path = get_enviro("HOME", status);
	else if (*path == '-' && *(path + 1) == '\0')
	{
		if (go_old_path(&path, status))
			return ;
	}
	if (handle_cd(path, status) == 127)
	{
		g_exit_status = 1;
		print_error();
	}
}
