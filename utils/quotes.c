/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:42:04 by psousa            #+#    #+#             */
/*   Updated: 2023/11/16 10:42:06 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	missing_quotes(const char *str)
{
	size_t	i;
	int		redirect_count;

	redirect_count = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '>' || str[i] == '<')
		{
			redirect_count++;
			if (redirect_count > 2)
			{
				printf("Error: Invalid Redirects\n");
				return (true);
			}
		}
		else
			redirect_count = 0;
		i++;
	}
	return (false);
}

bool	invalid_redirects(const char *str)
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
		printf("Error: Missing Quotes\n");
		return (true);
	}
	return (false);
}

bool	check_input(const char *str)
{
	if (invalid_redirects(str) || missing_quotes(str))
		return (true);
	return (false);
}
