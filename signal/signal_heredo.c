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
