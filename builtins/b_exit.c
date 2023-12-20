/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:26:16 by psousa            #+#    #+#             */
/*   Updated: 2023/12/19 11:42:48 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(char **cmd, t_status *status)
{
	lst_clear(status->token_lst);
	free(status->token_lst);
	matrix_free(cmd);
	free_env(status->env);
	free_exp(status->exp);
	close(status->default_fd[IN]);
	close(status->default_fd[OUT]);
	free(status);
}

int	has_pipe(t_list *token_lst)
{
	t_list	*cur_tkn;

	cur_tkn = token_lst;
	while (cur_tkn != NULL)
	{
		if (ft_strncmp(cur_tkn->content, "|", ft_strlen(cur_tkn->content)) == 0)
		{
			return (1);
		}
		cur_tkn = cur_tkn->next;
	}
	return (0);
}

void	exit_args(char **cmd, t_status *status)
{
	long long	exit_code;

	if (!is_number(cmd[1]))
	{
		print_error(2, "numeric argument required", *cmd);
		free_all(cmd, status);
		exit(2);
	}
	else if (is_number(cmd[1]) && !cmd[2])
	{
		exit_code = (char)ft_atol(cmd[1]);
		free_all(cmd, status);
		exit(exit_code);
	}
}

void	b_exit(char **cmd, t_status *status)
{
	int	len;

	len = 0;
	if (has_pipe(*status->token_lst))
		return ;
	while (cmd[len])
		len++;
	printf("exit\n");
	if (len >= 2)
	{
		exit_args(cmd, status);
		if (len > 2)
		{
			print_error(EXIT_FAILURE, "too many arguments", *cmd);
			return ;
		}
	}
	if (len == 1)
		free_all(cmd, status);
	exit(g_exit_status);
}
