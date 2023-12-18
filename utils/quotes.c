/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:42:04 by psousa            #+#    #+#             */
/*   Updated: 2023/12/18 11:44:14 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	missing_quotes(const char *str)
{
	size_t	i;
	bool	inside_single_quotes;
	bool	inside_double_quotes;

	inside_single_quotes = false;
	inside_double_quotes = false;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (str[i] == '\"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		i++;
	}
	if (inside_single_quotes || inside_double_quotes)
	{
		return (true);
	}
	return (false);
}
