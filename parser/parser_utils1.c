/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:24:33 by dlima             #+#    #+#             */
/*   Updated: 2023/12/18 11:49:25 by dlima            ###   ########.fr       */
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
