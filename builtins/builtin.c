/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:25:59 by psousa            #+#    #+#             */
/*   Updated: 2023/12/14 17:11:37 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	x_commands(char **cmd, t_status *status)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		b_echo(cmd + 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		b_cd(status, cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		b_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
			print_exp(status);
		else
			b_export(status, cmd + 1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
		b_unset(status, cmd + 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		if (cmd[1] == NULL)
			print_env(status);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		b_exit(cmd, status);
}

int	commands(char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	else
		return (0);
}
