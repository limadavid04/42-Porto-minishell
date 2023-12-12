/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:58:03 by psousa            #+#    #+#             */
/*   Updated: 2023/12/12 12:26:02 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

int	set_env(char *key, char *newvalue, t_status *status)
{
	t_env	*newenv;
	t_env	*find;

	find = search_env(key, status);
	if (find)
	{
		free(find->v_value);
		find->v_value = ft_strdup(newvalue);
		return (0);
	}
	else
	{
		newenv = new_env(key, newvalue);
		env_back(&status->env, newenv);
		return (0);
	}
	return (-1);
}

void	print_env(t_status *status)
{
	t_env	*print;

	print = status->env;
	while (print)
	{
		printf("%s=%s\n", print->v_name, print->v_value);
		print = print->next;
	}
	g_exit_status = 0;
}

char	**array_env(t_status *status)
{
	int		num;
	int		i;
	t_env	*cur;
	char	**env;

	num = 0;
	cur = status->env;
	while (cur != NULL)
	{
		num++;
		cur = cur->next;
	}
	env = ft_calloc(sizeof(char *), num + 1);
	cur = status->env;
	i = 0;
	while (cur != NULL)
	{
		env[i] = join_three(cur->v_name, "=", cur->v_value);
		cur = cur->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

t_env	*search_env(char *name, t_status *status)
{
	t_env	*search;

	search = status->env;
	while (search != NULL)
	{
		if (ft_strcmp(name, search->v_name) == 0)
			return (search);
		search = search->next;
	}
	return (NULL);
}

char	*get_env(char *name, t_status *status)
{
	t_env	*search;

	search = status->env;
	while (search != NULL)
	{
		if (ft_strcmp(name, search->v_name) == 0)
			return (search->v_value);
		search = search->next;
	}
	return (NULL);
}
