/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:26:16 by psousa            #+#    #+#             */
/*   Updated: 2023/11/22 12:26:17 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

void	exit_args(t_status *status, char **cmd)
{
	long long	exit_code;

	if (!is_number(cmd[1]))
	{
		// print_error("numeric argument required", 2, cmd);
		printf("numeric argument required");
		free_all(status);
		exit_code = (char)ft_atol(cmd[1]);
		matrix_free(cmd);
		exit(exit_code);
	}
	else if (is_number(cmd[1]) && !cmd[2])
	{
		free_all(status);
		exit_code = (char)ft_atol(cmd[1]);
		matrix_free(cmd);
		exit(exit_code);
	}
}

void	b_exit(t_status *status, char **cmd)
{
	int	len;

	len = 0;
	// if (has_pipe(status))
	// 	return ;
	while (cmd[len])
		len++;
	printf("exit\n");
	if (len >= 2)
	{
		exit_args(status, cmd);
		if (len > 2)
		{
			//print_error("too many arguments", 1, cmd);
			printf("too many arguments");
			return ;
		}
	}
	if (len == 1)
		free_all(status);
	matrix_free(cmd);
	exit(g_exit_status);
}
