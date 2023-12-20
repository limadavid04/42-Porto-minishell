/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:51:33 by dlima             #+#    #+#             */
/*   Updated: 2023/12/20 13:40:53 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redirect_input(t_list *redir, t_status *status)
{
	int		fd;
	char	*new_filename;

	new_filename = process_tokens(redir->next->content, 1, status);
	fd = open(new_filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(EXIT_FAILURE, strerror(errno), new_filename);
		free(new_filename);
		return (0);
	}
	free(new_filename);
	dup2(fd, IN);
	close(fd);
	return (1);
}

static int	redirect_output(t_list	*redir, int append, t_status *status)
{
	int		fd;
	char	*new_filename;

	new_filename = process_tokens(redir->next->content, 1, status);
	if (append == 1)
		fd = open(new_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(EXIT_FAILURE, strerror(errno), new_filename);
		free(new_filename);
		return (0);
	}
	free(new_filename);
	dup2(fd, OUT);
	close(fd);
	return (1);
}

static int	handle_heredoc(t_list	*heredoc, t_status *status)
{
	char	*delim;
	char	*temp;
	int		fd;

	temp = process_tokens(heredoc->next->content, 0, status);
	delim = ft_strjoin(temp, "\n");
	free(temp);
	create_heredoc_subprocess(delim, status);
	free(delim);
	sig_handling();
	if (g_exit_status == 0)
	{
		fd = open(".heredoc", O_RDONLY, 0644);
		dup2(fd, IN);
		close(fd);
		unlink(".heredoc");
		return (1);
	}
	unlink(".heredoc");
	return (0);
}

int	redirect2(t_list *cur, t_status *status)
{
	if (!ft_strncmp(cur->content, "<", ft_strlen(cur->content)))
	{
		if (!redirect_input(cur, status))
			return (0);
	}
	else if (!ft_strncmp(cur->content, "<<", ft_strlen(cur->content)))
	{
		if (!handle_heredoc(cur, status))
			return (0);
	}
	return (1);
}

int	redirect(t_list *cmd_start, t_list *pipe_tkn, t_status *status)
{
	t_list	*cur;

	cur = cmd_start;
	while (cur != pipe_tkn)
	{
		if (!ft_strncmp(cur->content, ">", ft_strlen(cur->content)))
		{
			if (!redirect_output(cur, 0, status))
				return (0);
		}
		else if (!ft_strncmp(cur->content, ">>", ft_strlen(cur->content)))
		{
			if (!redirect_output(cur, 1, status))
				return (0);
		}
		else if (!redirect2(cur, status))
			return (0);
		cur = cur->next;
	}
	return (1);
}
