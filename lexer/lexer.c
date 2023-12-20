/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:25:48 by dlima             #+#    #+#             */
/*   Updated: 2023/12/20 13:07:09 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*state_no_quote(t_info *info)
{
	char	*cmd;

	cmd = info->cmd;
	if (!is_whitespace(cmd[*info->i]) && info->inside_word == 0)
	{
		if (is_special_char(cmd[*info->i]))
			info->node = handle_special(info->head, info->node, info->i, cmd);
		else
		{
			info->node = create_token(info->head, info->node, info->i, cmd);
			info->inside_word = 1;
		}
	}
	else if (info->inside_word == 1)
		info->node = state_no_quote_inside_word(info);
	return (info->node);
}

static t_list	*state_double_quote(t_info *info)
{
	char	*cmd;
	int		*i;
	t_list	*node;

	node = info->node;
	cmd = info->cmd;
	i = info->i;
	if (is_double_quote(cmd[*i]) && info->quote == 2)
	{
		info->quote = 0;
		node->content = add_char(cmd[*i], (char *)node->content);
	}
	else
	{
		info->quote = 2;
		if (info->inside_word == 0)
		{
			node = create_token(info->head, node, i, cmd);
			info->inside_word = 1;
		}
		else if (info->inside_word == 1)
			node->content = add_char(cmd[*i], (char *)node->content);
	}
	return (node);
}

static t_list	*state_single_quote(t_info *info)
{
	char	*cmd;
	int		*i;
	t_list	*node;

	node = info->node;
	cmd = info->cmd;
	i = info->i;
	if (is_single_quote(cmd[*i]) && info->quote == 1)
	{
		info->quote = 0;
		node->content = add_char(cmd[*i], (char *)node->content);
	}
	else
	{
		info->quote = 1;
		if (info->inside_word == 0)
		{
			node = create_token(info->head, node, i, cmd);
			info->inside_word = 1;
		}
		else if (info->inside_word == 1)
			node->content = add_char(cmd[*i], (char *)node->content);
	}
	return (node);
}

static void	get_tokens(t_info *info)
{
	int		i;
	char	*cmd;

	cmd = info->cmd;
	i = 0;
	info->i = &i;
	while (cmd[i] != '\0')
	{
		if ((info->quote == 0 && is_single_quote(cmd[i])) \
		|| info->quote == 1)
			info->node = state_single_quote(info);
		else if ((info->quote == 0 && is_double_quote(cmd[i])) \
		|| info->quote == 2)
			info->node = state_double_quote(info);
		else if (info->quote == 0 && !is_double_quote(cmd[i]) \
		&& !is_single_quote(cmd[i]))
			info->node = state_no_quote(info);
		i++;
	}
}

t_list	**lexer(char *cmd)
{
	t_info	*info;
	t_list	**token_lst;

	info = malloc(sizeof(t_info));
	info->cmd = cmd;
	info->quote = 0;
	info->inside_word = 0;
	info->head = malloc(sizeof(t_list *));
	*info->head = NULL;
	info->node = NULL;
	get_tokens(info);
	token_lst = info->head;
	free(info);
	return (token_lst);
}
