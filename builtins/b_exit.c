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

// #include "../minishell.h"

// void	two_args(char **cmd, t_state *state)
// {
// 	long long	exit_code;

// 	if (ft_isnumber(cmd[1]))
// 	{
// 		//free all funtion
// 		exit_code = (char)ft_atol(cmd[1]);
// 		free_split(cmd);
// 		exit(exit_code);
// 	}
// 	else
// 	{
// 		print_error("numeric argument required", 2);
// 		//free all funtion
// 	}
// }

// void b_exit(char **cmd)
// {
// 	int len;

// 	len = 0;

// 	while (cmd[len])
// 		len++;
// 	printf("exit\n");
// 	if (len >= 2)
// 	{
// 		two_args(cmd, data);
// 		if (len > 2)
// 		{
// 			print_error("too many arguments", 1, cmd);
// 			return ;
// 		}
// 	}
// 	if (len == 1)
// 		//free all funtion
// 	}
