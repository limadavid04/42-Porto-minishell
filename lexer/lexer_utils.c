/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:05:59 by dlima             #+#    #+#             */
/*   Updated: 2023/11/10 11:17:19 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_next_delimiter(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && !is_special_char(cmd[i]) && !is_whitespace(cmd[i]) \
	&& !is_double_quote(cmd[i]) && !is_single_quote(cmd[i]) && cmd[i] != '$')
		i++;
	return (i);
}

int	check_next_char(char *c)
{
	if ((*c) == '>')
	{
		if (*(c + 1) == '>')
			return (1);
	}
	else if ((*c) == '<')
	{
		if (*(c + 1) == '<')
			return (1);
	}
	return (0);
}

void	print_linked_list(t_list	*head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

void	lst_clear(t_list **lst)
{
	t_list	*temp;
	t_list	*nxt;

	if (lst == NULL)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		nxt = temp->next;
		free(temp->content);
		free(temp);
		temp = nxt;
	}
	*lst = NULL;
}

t_list	*create_token(t_list **head, t_list *node, int *i, char *cmd)
{
	node = ft_lstnew(NULL);
	ft_lstadd_back(head, node);
	node->content = add_char(cmd[*i], (char *)node->content);
	return (node);
}
