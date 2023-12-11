/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:signal/signal_heredo.c
/*   signal_heredo.c                                    :+:      :+:    :+:   */
========
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
>>>>>>>> david-work:signal/signal_heredoc.c
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:19:10 by dlima             #+#    #+#             */
/*   Updated: 2023/12/11 13:08:24 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_ctrl_c_heredoc(int signal, t_heredoc *heredoc)
{
<<<<<<<< HEAD:signal/signal_heredo.c
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
========
	static t_heredoc *here_static;
	if (signal == -1)
		here_static = heredoc;
	else
	{
		g_exit_status = 130;
		free_heap(here_static->status, here_static->delim, here_static->fd);
		exit(g_exit_status);
	}
}
void	signals_heredoc(t_heredoc *heredoc)
{
	exec_ctrl_c_heredoc(-1, heredoc);
	signal(SIGINT, (void *)exec_ctrl_c_heredoc);
>>>>>>>> david-work:signal/signal_heredoc.c
}
