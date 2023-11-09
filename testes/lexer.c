/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:25:48 by dlima             #+#    #+#             */
/*   Updated: 2023/11/09 13:07:43 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list	*create_node_in_back(t_list **head, t_list *node, int *i, char *cmd)
{
	node = ft_lstnew(NULL);
	ft_lstadd_back(head, node);
	node->content = add_char(cmd[*i],(char*)node->content);
	return (node);
}
t_list *handle_special(t_list **head, t_list *node, int *i, char *cmd)
{
	node = create_node_in_back(head, node, i, cmd);
	if (check_next_char(&cmd[*i]))
	{
		(*i)++;
		node->content = add_char(cmd[*i],(char*)node->content);
	}
	return (node);
}
char	*add_char(char c, char *content)
{
	char *temp;
	char *buff;
	char *new_content;

	if (content == NULL)
	{
		new_content = malloc(sizeof(char) * 1 + 1);
		new_content[0] = c;
		new_content[1] = '\0';
	}
	else
	{
		buff = malloc(sizeof(char) * 1 + 1);
		buff[0] = c;
		buff[1] = '\0';
		temp = malloc(sizeof(char) * (ft_strlen(content) + 1) + 1);
		ft_strlcpy(temp, content, ft_strlen(content) + 1);
		free(content);
		new_content = ft_strjoin(temp, buff);
		free(buff);
		free(temp);
	}
	return (new_content);
}
t_list	*state_no_quote(t_info *info)
{
		char	*cmd;
		int		*i;
		t_list	*node;

		node = info->node;
		cmd = info->cmd;
		i = info->i;
		if (!is_whitespace(cmd[*i]) && info->inside_word == 0)
		{
			if (is_special_char(cmd[*i]))
				node = handle_special(info->head, node, i, cmd);
			else
			{
				node = create_node_in_back(info->head, node, i, cmd);
				info->inside_word = 1;
			}
		}
		else if (info->inside_word == 1)
		{
			if (is_whitespace(cmd[*i]) || is_special_char(cmd[*i]))
				info->inside_word = 0;
			if (is_special_char(cmd[*i]))
				node = handle_special(info->head, node, i, cmd);
			else
				node->content = add_char(cmd[*i],(char*)node->content);
		}
		return (node);
}

// void	state_single_quote(t_info *info)
// {

// 	char	*cmd;
// 	int		*i;
// 	t_list	*node;

// 	node = info->node;
// 	cmd = info->cmd;
// 	i = info->i;
// 	if (!is_whitespace(cmd[*i]) && info->inside_word == 0)
// 	{
// 		if (is_special_char(cmd[*i]))
// 			node = handle_special(info->head, node, i, cmd);
// 		else
// 		{
// 			node = create_node_in_back(info->head, node, i, cmd);
// 			info->inside_word = 1;
// 		}
// 	}
// 	else if (info->inside_word == 1)
// 	{
// 		if (is_whitespace(cmd[*i]) || is_special_char(cmd[*i]))
// 			info->inside_word = 0;
// 		if (is_special_char(cmd[*i]))
// 			node = handle_special(info->head, node, i, cmd);
// 		else
// 			node->content = add_char(cmd[*i],(char*)node->content);
// 	}
// 	return (node);
// }

void lexer(char *cmd)
{
	t_info *info;
	int i;

	i = 0;
	info = malloc(sizeof(t_info));
	info->i = &i;
	info->cmd = cmd;
	info->quote = 0;
	info->inside_word = 0;
	info->head = malloc(sizeof(t_list *));
	*info->head = NULL;
	info->node = NULL;
	// >> << > <

	while (cmd[i] != '\0')
	{
		// if (info->quote == 0 && is_single_quote(cmd[i]))
		// 	info->quote == 1;
		// else if (info->quote == 0 && is_double_quote(cmd[i]))
		// 			info->quote == 2;
		// else if (info->quote == 0 && !is_double_quote(cmd[i]) && !is_single_quote(cmd[i]))
			info->node = state_no_quote(info);
		// else if (info->quote == 1)
		// 	state_single_quote(info);
		// else if (info->quote == 2)
		// 	state_double_quote(info);
			//state_double_quote(info);
		i++;
	}
	if (*info->head != NULL)
		printLinkedList(*info->head);
	else
		printf("head is null cuz");
	// 	printf("The linked list is empty.\n");
	lst_clear(info->head);

}


// ls -la
// echo "$PATH" '$PATH'
