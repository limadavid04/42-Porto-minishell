/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:17:40 by dlima             #+#    #+#             */
/*   Updated: 2023/11/21 12:13:04 by dlima            ###   ########.fr       */
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

t_list	*create_space_for_expansion(t_info *info, char *var)
{
	char	*temp;

	if (info->inside_word == 0)
	{
		info->node = ft_lstnew(NULL);
		ft_lstadd_back(info->head, info->node);
		info->node->content = malloc(sizeof(char) * ft_strlen(var) + 1);
		ft_strlcpy(info->node->content, var, ft_strlen(var) + 1);
		info->inside_word = 1;
	}
	else if (info->inside_word == 1)
	{
		temp = malloc(sizeof(char) * ft_strlen(info->node->content) + 1);
		ft_strlcpy(temp, info->node->content, \
		ft_strlen(info->node->content) + 1);
		free(info->node->content);
		info->node->content = ft_strjoin(temp, var);
		free(temp);
	}
	return (info->node);
}

t_list	*expand_var(t_info *info)
{
	char	*cmd;
	int		size;
	char	*var;
	char	*var_name;

	cmd = info->cmd;
	(*info->i)++;
	size = find_next_delimiter(&cmd[*info->i]);
	var_name = malloc(sizeof(char) * size + 1);
	ft_strlcpy(var_name, &cmd[*info->i], size + 1);
	var = getenv(var_name);
	free(var_name);
	*info->i += (size - 1);
	if (var == NULL)
		return (info->node);
	else
		info->node = create_space_for_expansion(info, var);
	return (info->node);
}

int	check_for_errors_in_redirect(t_list	**token_lst)
{
	t_list *cur;

	cur = *token_lst;
	while (cur != NULL)
	{
		if (!ft_strncmp(cur->content, "<", ft_strlen(cur->content))\
		|| !ft_strncmp(cur->content, ">", ft_strlen(cur->content))\
		|| !ft_strncmp(cur->content, ">>", ft_strlen(cur->content)))
		{
			if (cur->next == NULL || !ft_strncmp(cur->next->content, "<", ft_strlen(cur->content)) \
			|| !ft_strncmp(cur->next->content, ">", ft_strlen(cur->content))\
			|| !ft_strncmp(cur->next->content, ">>", ft_strlen(cur->content))\
			|| !ft_strncmp(cur->next->content, "|", ft_strlen(cur->content)))
			{
				printf("Syntax Error\n");
				return (0);
			}
		}
		cur = cur->next;
	}
	return (1);
}
