/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:54:00 by dlima             #+#    #+#             */
/*   Updated: 2023/12/18 11:48:57 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_default_fd(int default_fd[2])
{
	default_fd[IN] = dup(IN);
	default_fd[OUT] = dup(OUT);
}

void	restore_default_fd(int default_fd[2])
{
	dup2(default_fd[IN], IN);
	close (default_fd[IN]);
	dup2(default_fd[OUT], OUT);
	close(default_fd[OUT]);
}

int	command_length(t_list *cmd_start, t_list *pipe_tkn)
{
	t_list	*temp;
	size_t	size;

	temp = cmd_start;
	size = 0;
	while (temp != pipe_tkn)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void	matrix_free(char **matrix)
{
	int	x;

	x = 0;
	while (matrix[x])
	{
		free(matrix[x]);
		x++;
	}
	free(matrix);
}

int	count_redir(t_list *cmd_start, t_list *pipe_tkn)
{
	int	i;

	i = 0;
	while (cmd_start != pipe_tkn)
	{
		if (is_redir(cmd_start))
			i++;
		cmd_start = cmd_start->next;
	}
	return (i);
}
