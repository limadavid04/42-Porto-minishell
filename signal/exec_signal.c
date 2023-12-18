/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:41:31 by psousa            #+#    #+#             */
/*   Updated: 2023/12/18 11:43:00 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_ctrl_c(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	exec_ctrl_bslash(int signal)
{
	(void)signal;
	printf("Quit (core dumped)\n");
}

void	signals_exec(void)
{
	signal(SIGINT, exec_ctrl_c);
	signal(SIGQUIT, exec_ctrl_bslash);
}
