/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:25:48 by dlima             #+#    #+#             */
/*   Updated: 2023/11/08 16:48:08 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	state_no_quote(char *cmd, t_state *state, t_list *head, t_list *node, int *i)
{
		if (!is_whitespace(cmd[*i]) && state->quote == 0 && state->inside_word == 0)
		{
			node = ft_lstnew(NULL);
			ft_lstadd_back(&head, node);
			node->content = add_char(cmd[*i],(char*)node->content);
			if (is_special_char(cmd[*i]))
			{
				if (check_next_char(&cmd[*i]))
				{
					(*i)++;
					node->content = add_char(cmd[*i],(char*)node->content);
				}
			}
			else
				state->inside_word = 1;
		}
		else if (state->quote == 0 && state->inside_word == 1)
		{
			if (is_whitespace(cmd[*i]))
				state->inside_word = 0;
			else if (is_special_char(cmd[*i]))
			{
				node = ft_lstnew(NULL);
				ft_lstadd_back(&head, node);
				node->content = add_char(cmd[*i],(char*)node->content);
				if (check_next_char(&cmd[*i]))
				{
					(*i)++;
					node->content = add_char(cmd[*i],(char*)node->content);
				}
				state->inside_word = 0;
			}
			else
				node->content = add_char(cmd[*i],(char*)node->content);
		}
}
void lexer(char *cmd)
{
	t_state *state;

	state = malloc(sizeof(t_state));
	state->quote = 0;
	state->inside_word = 0;

	t_list *head;
	t_list *node;

	head = NULL;
	node = NULL;

	int i = 0;
	// >> << > <
	while (cmd[i] != '\0')
	{

		state_no_quote(cmd, state, head, node, &i);
		i++;
	}
	if (head != NULL)
		printLinkedList(head);
	else
		printf("The linked list is empty.\n");
	lst_clear(&head);
	// free(head)
	// free the nodes and memory allocation ft_lstclear()
}


// ls -la
// echo "$PATH" '$PATH'
