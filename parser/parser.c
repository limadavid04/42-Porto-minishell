/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:58:23 by dlima             #+#    #+#             */
/*   Updated: 2023/11/16 12:36:32 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**get_cmd(t_list *cmd_start, t_list *pipe_tkn)
{
	char **cmd;
	int	cmd_size;
	int	i;

	i = 0;
	cmd_size = command_length(cmd_start, pipe_tkn);
	// printf("cmd size = %d\n", cmd_size);
	cmd = malloc(sizeof(char *) * (cmd_size + 1));
	while (cmd_start != pipe_tkn)
	{
		cmd[i] = ft_strdup(cmd_start->content);
		// printf("cmd = %s\n", cmd[i]);
		i++;
		cmd_start = cmd_start->next;
	}
	cmd[i] = NULL;
	return (cmd);

}

void	parse_command(t_list *cmd_start, t_list *pipe_tkn)
{
	char	**cmd;
	int		default_fd[2];
	//save the STDIN and STDOUT before overwriting fd 0 and 1;
	default_fd[IN] = 0;
	default_fd[OUT] = 1;

	// printf("before default_fd[IN] = %d\n", default_fd[IN]);
	// printf("before default_fd[OUT] = %d\n", default_fd[OUT]);
	save_default_fd(default_fd);
	printf("default_fd[IN] = %d\n", default_fd[IN]);
	printf("default_fd[OUT] = %d\n", default_fd[OUT]);
	restore_default_fd(default_fd);
	cmd = get_cmd(cmd_start, pipe_tkn);

	matrix_free(cmd);

	//check command redirects;
	//create pipe
	//execute

	//restore fd's 0 and 1 back to stdin and stdout for next command to properly execute

}
void	parse_tokens(t_list *token_lst)
{
	t_list *cur_tkn;
	t_list *cmd_start;
	char	pipe;

	pipe = '|';
	cur_tkn = token_lst;
	cmd_start = token_lst;

	while (cur_tkn != NULL)
	{
		if (ft_strncmp(cur_tkn->content, &pipe, 1) == 0)
		{
			parse_command(cmd_start, cur_tkn);
			cmd_start = cur_tkn->next;
			// parse_tokens(cmd_start, old_pipe_in);
		}
		cur_tkn = cur_tkn->next;
	}
	//parse last command
	if (cmd_start != NULL)
		parse_command(cmd_start, cur_tkn);
}
void	parser_main(t_list **token_lst)
{

	//recieve status as parameter
	//define int old_pipe_in to save the fd of the read end of the last pipe;
	if (*token_lst == NULL)
		return ;
	parse_tokens(*token_lst);
}
	// while (cmd[i])
	// {
	// 	printf("cmd = %s\n", cmd[i]);
	// 	i++;
	// }
