/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:35:52 by psousa            #+#    #+#             */
/*   Updated: 2023/12/18 11:38:56 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env(t_status *status, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = status->env;
	prev = NULL;
	if (temp != NULL && ft_strcmp(temp->v_name, key) == 0)
	{
		status->env = temp->next;
		free_env2(temp);
		return ;
	}
	while (temp != NULL && ft_strcmp(temp->v_name, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free_env2(temp);
}

void	unset_exp(t_status *status, char *key)
{
	t_exp	*temp;
	t_exp	*prev;

	temp = status->exp;
	prev = NULL;
	if (temp != NULL && ft_strcmp(temp->vexp_name, key) == 0)
	{
		status->exp = temp->next;
		free_exp2(temp);
		return ;
	}
	while (temp != NULL && ft_strcmp(temp->vexp_name, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free_exp2(temp);
}

int	valid_unset(char *key, char *type)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
	{
		export_err(EXIT_FAILURE, "not a valid identifier", type, key);
		return (0);
	}
	i++;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_') || key[i] == '=' )
		{
			export_err(EXIT_FAILURE, "not a valid identifier", type, key);
			return (0);
		}
		i++;
	}
	return (1);
}

void	b_unset(t_status *status, char **cmd)
{
	char	*key;
	int		len;
	int		i;

	if (has_pipe(*status->token_lst))
		return ;
	i = -1;
	while (cmd[++i])
	{
		if (!valid_unset(cmd[i], "unset"))
			continue ;
		len = 0;
		while (cmd[i][len] != '\0')
			len++;
		key = ft_substr(cmd[i], 0, len);
		unset_exp(status, key);
		unset_env(status, key);
		free(key);
	}
	g_exit_status = 0;
}
