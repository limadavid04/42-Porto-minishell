/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:05:07 by dlima             #+#    #+#             */
/*   Updated: 2023/12/20 13:05:53 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*state_no_quote_inside_word(t_info *info)
{
	char	*cmd;

	cmd = info->cmd;
	if (is_whitespace(cmd[*info->i]))
		info->inside_word = 0;
	else if (is_special_char(cmd[*info->i]))
	{
		info->node = handle_special(info->head, info->node, info->i, cmd);
		info->inside_word = 0;
	}
	else
		info->node->content = add_char(cmd[*info->i], \
		(char *)info->node->content);
	return (info->node);
}
