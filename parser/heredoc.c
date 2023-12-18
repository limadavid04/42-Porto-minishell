/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:01:17 by dlima             #+#    #+#             */
/*   Updated: 2023/12/18 11:48:32 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_heap(t_status *status, char *delim, int fd)
{
	if (status->old_pipe_in != -1)
		close(status->old_pipe_in);
	lst_clear(status->token_lst);
	free(status->token_lst);
	free_env(status->env);
	free_exp(status->exp);
	free(status);
	close(fd);
	free(delim);
}

void	save_fd_heredoc(t_status *status, int old_fd[2])
{
	old_fd[IN] = dup(IN);
	old_fd[OUT] = dup(OUT);
	dup2(status->default_fd[IN], IN);
	close(status->default_fd[IN]);
	dup2(status->default_fd[OUT], OUT);
	close(status->default_fd[OUT]);
}

void	restore_fd_heredoc(t_status *status, int old_fd[2])
{
	status->default_fd[IN] = dup(IN);
	status->default_fd[OUT] = dup(OUT);
	dup2(old_fd[IN], IN);
	close(old_fd[IN]);
	dup2(old_fd[OUT], OUT);
	close(old_fd[OUT]);
}

void	get_heredoc_input(char *delim, int fd)
{
	char	*line;
	char	*temp;

	while (1)
	{
		temp = readline("> ");
		line = ft_strjoin(temp, "\n");
		free(temp);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (!ft_strncmp(line, delim, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void init_heredoc_struct(t_heredoc *heredoc, t_status *status, int fd, char *delim)
{
	heredoc->delim = delim;
	heredoc->status = status;
	heredoc->fd = fd;
}

void	create_heredoc_subprocess(char *delim, t_status *status)
{
	int			pid;
	t_heredoc	heredoc_struct;
	int			old_fd[2];
	int			fd;
	int			exit_code;

	signal(SIGINT, exec_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	save_fd_heredoc(status, old_fd);
	pid = fork();
	if (pid == 0)
	{
		close(old_fd[IN]);
		close(old_fd[OUT]);
		g_exit_status = 0;
		fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		init_heredoc_struct(&heredoc_struct, status, fd, delim);
		signals_heredoc(&heredoc_struct);
		get_heredoc_input(delim, fd);
		free_heap(status, delim, fd);
		exit(g_exit_status);
	}
	restore_fd_heredoc(status, old_fd);
	waitpid(pid, &exit_code, 0);
	g_exit_status = WEXITSTATUS(exit_code);
}
