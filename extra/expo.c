/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:58:07 by psousa            #+#    #+#             */
/*   Updated: 2023/12/18 14:42:24 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exp2(t_exp *tmp)
{
	if (!tmp)
		return ;
	free(tmp->vexp_name);
	free(tmp->vexp_value);
	free(tmp);
}

void	free_exp(t_exp *exp)
{
	t_exp	*tmp;

	while (exp)
	{
		tmp = exp;
		exp = exp->next;
		free_exp2(tmp);
	}
}

t_exp	*new__exp(char *vexp_name, char *vexp_value)
{
	t_exp	*new_exp;

	new_exp = malloc(sizeof(t_exp));
	if (!new_exp)
		return (0);
	new_exp->vexp_name = ft_strdup(vexp_name);
	if (vexp_value == NULL)
		new_exp->vexp_value = NULL;
	else
		new_exp->vexp_value = ft_strdup(vexp_value);
	new_exp->next = NULL;
	return (new_exp);
}

void	add_exp(t_exp **exp, t_exp *new)
{
	t_exp	*curr;

	if (*exp == NULL || ft_strcmp((*exp)->vexp_name, new->vexp_name) >= 0)
	{
		new->next = *exp;
		*exp = new;
	}
	else
	{
		curr = *exp;
		while (curr->next != NULL && ft_strcmp(curr->next->vexp_name, \
				new->vexp_name) < 0)
			curr = curr->next;
		new->next = curr->next;
		curr->next = new;
	}
}

void	create_exp(t_status *status, char **exp)
{
	size_t	len;
	int		i;
	char	*vexp_name;
	char	*vexp_value;
	t_exp	*new_exp;

	i = 0;
	while (exp[i])
	{
		if (ft_strchr(exp[i], '='))
		{
			len = ft_strchr(exp[i], '=') - exp[i];
			vexp_name = malloc(len + 1);
			ft_memcpy(vexp_name, exp[i], len);
			vexp_name[len] = '\0';
			vexp_value = ft_strdup(ft_strchr(exp[i], '=') + 1);
			new_exp = new__exp(vexp_name, vexp_value);
			add_exp(&status->exp, new_exp);
		}
		free(vexp_name);
		free(vexp_value);
		i++;
	}
}
