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

void	exit_args(char **cmd)
{
	long long	exit_code;

	if (!is_number(cmd[1]))
	{
		// print_error("numeric argument required", 2, cmd);
		printf("numeric argument required");
		//free all
		exit_code = (char)ft_atol(cmd[1]);
		//free cmd
		exit(exit_code);
	}
	else if (is_number(cmd[1]) && !cmd[2])
	{
		//free all
		exit_code = (char)ft_atol(cmd[1]);
		//free cmd
		exit(exit_code);
	}
}

void	b_exit(char **cmd)
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
		exit_args(cmd);
		if (len > 2)
		{
			// print_error("too many arguments", 1, cmd);
			printf("too many arguments");
			return ;
		}
	}
	//if (len == 1)
		//free all
	//free cmd
	exit(g_exit_status);
}
