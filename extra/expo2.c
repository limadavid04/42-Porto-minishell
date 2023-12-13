/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:58:10 by psousa            #+#    #+#             */
/*   Updated: 2023/12/12 15:12:45 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

t_exp	*search_exp(char *name, t_status *status)
{
	t_exp	*search;

	search = status->exp;
	while (search != NULL)
	{
		if (ft_strcmp(name, search->vexp_name) == 0)
			return (search);
		search = search->next;
	}
	return (NULL);
}

int	set_exp(char *name, char *new_value, t_status *status)
{
	t_exp	*new_exp;
	t_exp	*search;

	search = search_exp(name, status);
	if (search)
	{
		if (search->vexp_value != NULL)
			free(search->vexp_value);
		if (new_value == NULL)
			search->vexp_value = NULL;
		else
			search->vexp_value = ft_strdup(new_value);
		return (0);
	}
	else
	{
		new_exp = new__exp(name, new_value);
		add_exp(&status->exp, new_exp);
		return (0);
	}
	return (-1);
}

char	*get_exp(char *name, t_status *status)
{
	t_exp	*search;

	search = status->exp;
	while (search != NULL)
	{
		if (ft_strcmp(name, search->vexp_name) == 0)
			return (search->vexp_value);
		search = search->next;
	}
	return (NULL);
}

void	print_exp(t_status *status)
{
	t_exp	*print;

	print = status->exp;
	while (print)
	{
		if (print->vexp_value == NULL)
			printf("declare -x %s\n", print->vexp_name);
		else
			printf("declare -x %s=\"%s\"\n", print->vexp_name, \
					print->vexp_value);
		print = print->next;
	}
	g_exit_status = 0;
}
