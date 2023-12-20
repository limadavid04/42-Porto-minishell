/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:01:11 by dlima             #+#    #+#             */
/*   Updated: 2023/12/19 12:37:52 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_ctrl_c_heredoc(int signal, t_heredoc *heredoc)
{
	static t_heredoc	*here_static;

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
}
