/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:19:10 by dlima             #+#    #+#             */
/*   Updated: 2023/11/29 13:34:13 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_ctrl_c(int signal, t_status *status)
{
	//static *tmp = status;
	//if (signal = -1)
	//tmp = status
	//else
	//free a tudo
	(void)signal;
	write(1, "\n", 1);
}
// g_exit_status = EXIT_CTRL_C;
void	exec_ctrl_bslash(int signal)
{
	(void)signal;
	printf("Quit (core dumped)\n");
}
// g_exit_status = 131;
void	signals_exec(void)
{

	signal(SIGINT, exec_ctrl_c);
	signal(SIGQUIT, exec_ctrl_bslash);
}
