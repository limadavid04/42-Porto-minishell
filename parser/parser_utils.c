/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:54:00 by dlima             #+#    #+#             */
/*   Updated: 2023/11/16 12:36:32 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
FD table when we call save_default_fd

|    fd    |    file |
|__________|_________|
|    0     |   STDIN |
|    1     |   STOUT |
|    2     |  STDERR |
*/
/*
FD table after we call save_default_fd

|    fd    |    file |
|__________|_________|
|    0     |   STDIN |
|    1     |   STOUT |
|    2     |  STDERR |
|    3     |  STDIN  |
|    4     |  STDOUT |
*/
void	save_default_fd(int default_fd[2])
{
	default_fd[IN] = dup(IN);
	default_fd[OUT] = dup(OUT);
}
/*
FD table when we call restore_default_fd

|    fd    |    file       |
|__________|_______________|
|    0     |   old_pipe_in |
|    1     |   new_pipe_out|
|    2     |  STDERR       |
|    3     |  STDIN        |
|    4     |  STDOUT       |
*/
/*
FD table after we call restore_default_fd

|    fd    |    file |
|__________|_________|
|    0     |   STDIN |
|    1     |   STOUT |
|    2     |  STDERR |
*/
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