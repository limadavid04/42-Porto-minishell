/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:05:59 by dlima             #+#    #+#             */
/*   Updated: 2023/12/19 11:19:04 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_redir_err(t_list	**token_lst)
{
	t_list	*cur;

	cur = *token_lst;
	while (cur != NULL)
	{
		if (!ft_strncmp(cur->content, "<", ft_strlen(cur->content)) \
		|| !ft_strncmp(cur->content, ">", ft_strlen(cur->content)) \
		|| !ft_strncmp(cur->content, ">>", ft_strlen(cur->content)) \
		|| !ft_strncmp(cur->content, "<<", ft_strlen(cur->content)))
		{
			if (cur->next == NULL \
			|| !ft_strncmp(cur->next->content, "<", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, ">", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, ">>", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, "<<", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, "|", ft_strlen(cur->content)))
			{
				print_syntax_err(cur->next);
				return (0);
			}
		}
		cur = cur->next;
	}
	return (1);
}
