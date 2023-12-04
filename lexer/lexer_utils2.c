/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:17:40 by dlima             #+#    #+#             */
/*   Updated: 2023/12/04 15:08:26 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*handle_special(t_list **head, t_list *node, int *i, char *cmd)
{
	node = create_token(head, node, i, cmd);
	if (check_next_char(&cmd[*i]))
	{
		(*i)++;
		node->content = add_char(cmd[*i], (char *)node->content);
	}
	return (node);
}

char	*add_char(char c, char *content)
{
	char	*temp;
	char	*buff;
	char	*new_content;

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
		temp = malloc(sizeof(char) * ft_strlen(content) + 1);
		ft_strlcpy(temp, content, ft_strlen(content) + 1);
		free(content);
		new_content = ft_strjoin(temp, buff);
		free(buff);
		free(temp);
	}
	return (new_content);
}

int	check_for_errors_in_redirect(t_list	**token_lst)
{
	t_list	*cur;

	cur = *token_lst;
	while (cur != NULL)
	{
		if (!ft_strncmp(cur->content, "<", ft_strlen(cur->content)) \
		|| !ft_strncmp(cur->content, ">", ft_strlen(cur->content)) \
		|| !ft_strncmp(cur->content, ">>", ft_strlen(cur->content))
		|| !ft_strncmp(cur->content, "<<", ft_strlen(cur->content)))

		{
			if (cur->next == NULL \
			|| !ft_strncmp(cur->next->content, "<", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, ">", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, ">>", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, "<<", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, "|", ft_strlen(cur->content)))
			{
				print_error(SYNTAX_ERROR, "Syntax error", "minishell");
				return (0);
			}
		}
		cur = cur->next;
	}
	return (1);
}
