/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:24:33 by dlima             #+#    #+#             */
/*   Updated: 2023/12/20 12:58:08 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_list *cmd)
{
	if (!ft_strncmp(cmd->content, "<", ft_strlen(cmd->content)) \
		|| !ft_strncmp(cmd->content, ">", ft_strlen(cmd->content)) \
		|| !ft_strncmp(cmd->content, ">>", ft_strlen(cmd->content)) \
		|| !ft_strncmp(cmd->content, "<<", ft_strlen(cmd->content)))
	{
		return (1);
	}
	return (0);
}

int	find_next_delimiter(char *cmd)
{
	int	i;

	i = 0;
	while ((cmd[i] >= 65 && cmd[i] <= 90) || (cmd[i] >= 97 && cmd[i] <= 122) \
	|| (cmd[i] >= 48 && cmd[i] <= 57) || cmd[i] == 95)
		i++;
	return (i);
}

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

char	*join_var_expansion_with_token(char *new_token, char *var)
{
	char	*temp;

	temp = malloc(sizeof(char) * ft_strlen(new_token) + 1);
	ft_strlcpy(temp, new_token, ft_strlen(new_token) + 1);
	free(new_token);
	new_token = ft_strjoin(temp, var);
	free(temp);
	return (new_token);
}

char	*get_var(int size, char *src, t_status *status)
{
	char	*var;
	char	*var_name;

	var_name = malloc(sizeof(char) * size + 1);
	ft_strlcpy(var_name, src, size + 1);
	var = get_env(var_name, status);
	free(var_name);
	return (var);
}
