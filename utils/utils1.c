/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:42:04 by psousa            #+#    #+#             */
/*   Updated: 2023/12/20 13:15:38 by dlima            ###   ########.fr       */
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

char	*join_three(char *one, char *two, char *three)
{
	char	*tmp;
	char	*final;

	if (!(one && two && three))
		return (NULL);
	tmp = ft_strjoin(one, two);
	final = ft_strjoin(tmp, three);
	free(tmp);
	return (final);
}

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	export_err(int error_code, char *error_msg, char *type, char *key)
{
	g_exit_status = error_code;
	ft_putstr_fd(type, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
}
