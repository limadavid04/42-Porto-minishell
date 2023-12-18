/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:36:35 by psousa            #+#    #+#             */
/*   Updated: 2023/12/18 11:38:42 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rename_export(t_status *status, char *key)
{
	if (get_exp(key, status) == NULL)
		set_exp(key, NULL, status);
}

int	valid_export(char *key, char *type)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
	{
		printf("%s: `%s': not a valid identifier\n", type, key);
		return (0);
	}
	i++;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
		{
			printf("%s: `%s': not a valid identifier\n", type, key);
			return (0);
		}
		i++;
	}
	return (1);
}

void	export_single(char *cmd, t_status *status)
{
	char	*key;
	char	*value;
	int		len;

	len = 0;
	while (cmd[len] != '\0' && cmd[len] != '=')
		len++;
	key = ft_substr(cmd, 0, len);
	if (!valid_export(key, "export"))
	{
		free(key);
		return ;
	}
	if (cmd[len] != '=')
	{
		rename_export(status, key);
		free(key);
		return ;
	}
	value = ft_strdup(cmd + len + 1);
	set_env(key, value, status);
	set_exp(key, value, status);
	free(key);
	free(value);
}

void	b_export(t_status *status, char **cmd)
{
	int	i;

	i = -1;
	// if (has_pipe(status))
	// 	return ;
	while (cmd[++i])
		export_single(cmd[i], status);
	g_exit_status = 0;
}
