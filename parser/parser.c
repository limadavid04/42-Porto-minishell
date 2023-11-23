/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:58:23 by dlima             #+#    #+#             */
/*   Updated: 2023/11/23 11:16:49 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_list *cmd)
{
	if (!ft_strncmp(cmd->content, "<", ft_strlen(cmd->content))\
		|| !ft_strncmp(cmd->content, ">", ft_strlen(cmd->content))\
		|| !ft_strncmp(cmd->content, ">>", ft_strlen(cmd->content)))
	{
		return (1);
	}
	return (0);
}

int	count_redir(t_list *cmd_start, t_list *pipe_tkn)
{
	int i;

	i = 0;
	while (cmd_start != pipe_tkn)
	{
		if (is_redir(cmd_start))
			i++;
		cmd_start = cmd_start->next;
	}
	return (i);
}

char	**get_cmd(t_list *cmd_start, t_list *pipe_tkn)
{
	char **cmd;
	int	cmd_size;
	int	i;

	i = 0;
	cmd_size = command_length(cmd_start, pipe_tkn);
	cmd_size -= (2 * count_redir(cmd_start, pipe_tkn));
	cmd = malloc(sizeof(char *) * (cmd_size + 1));
	while (cmd_start != pipe_tkn)
	{
		while (is_redir(cmd_start))
		{
			cmd_start = cmd_start->next;
			cmd_start = cmd_start->next;
			if (cmd_start == NULL || cmd_start == pipe_tkn)
			{
				cmd[i] = 0;
				return (cmd);
			}
		}
		cmd[i] = ft_strdup(cmd_start->content);
		// printf("cmd = %s\n", cmd[i]);
		i++;
		cmd_start = cmd_start->next;
	}
	cmd[i] = 0; //changed from cmd[i] == NULL;
	return (cmd);
}


void	create_pipe(t_status *status, t_list *pipe_tkn)
{
	int	pipe_fd[2];

	if (status->old_pipe_in != -1)
	{
		dup2(status->old_pipe_in, IN);
		close(status->old_pipe_in);
	}
	if (pipe_tkn == NULL)
		return ;
	pipe(pipe_fd);
	dup2(pipe_fd[OUT], OUT);
	close(pipe_fd[OUT]);
	status->old_pipe_in = pipe_fd[IN];
}

void	parse_command(t_list *cmd_start, t_list *pipe_tkn,  t_status *status)
{
	char	**cmd;
	int		default_fd[2];

	save_default_fd(default_fd);
	//create pipe
	create_pipe(status, pipe_tkn);
	if (redirect_handler(cmd_start, pipe_tkn))
	{
		cmd = get_cmd(cmd_start, pipe_tkn);
		execute(status, cmd, default_fd);
		matrix_free(cmd);
	}
	restore_default_fd(default_fd);
}
void	parse_tokens(t_status *status)
{
	t_list *cur_tkn;
	t_list *cmd_start;

	cur_tkn = *status->token_lst;
	cmd_start = *status->token_lst;

	while (cur_tkn != NULL)
	{
		if (ft_strncmp(cur_tkn->content, "|", ft_strlen(cur_tkn->content)) == 0)
		{
			parse_command(cmd_start, cur_tkn, status);
			cmd_start = cur_tkn->next;
		}
		cur_tkn = cur_tkn->next;
	}
	if (cmd_start != NULL)
		parse_command(cmd_start, cur_tkn, status);
}

void	parser_main(t_list **token_lst, t_status *status, char **envp)
{
	status->old_pipe_in = -1;
	status->envp = envp;
	status->process_count = 0;
	status->token_lst =  token_lst; //means that this is the first command;
	if (*token_lst == NULL)
		return ;
	parse_tokens(status);
	//close old_pipe_in if it wasn't closed
}
