/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:44:30 by dlima             #+#    #+#             */
/*   Updated: 2023/12/19 12:02:19 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *str)
{
	int	negative;

	negative = 0;
	if (ft_strlen(str) == 0)
		return (0);
	if (*str == '-')
	{
		str++;
		negative = 1;
	}
	if (!*str)
		return (0);
	if (*str == '-' && *(str + 1) == '\0')
		return (1);
	if (!is_all_digits(str))
		return (0);
	if (ft_strlen(str) > 19)
		return (0);
	if (!negative && ft_strcmp("9223372036854775807", str) < 0)
		return (0);
	if (negative && ft_strcmp("9223372036854775808", str) < 0)
		return (0);
	return (1);
}

void	print_syntax_err(struct s_list *token)
{
	g_exit_status = SYNTAX_ERROR;
	ft_putstr_fd(SYNTAX_MSG, 2);
	write(1, "`", 2);
	if (token == NULL)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd((char *)token->content, 2);
	write(1, "'", 2);
	ft_putstr_fd("\n", 2);
}

void	print_error(int error_code, char *error_msg, char *file)
{
	g_exit_status = error_code;
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
}

long long	ft_atol(const char *str)
{
	long long	i;
	long long	sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	free_env2(t_env *tmp)
{
	if (!tmp)
		return ;
	free(tmp->v_name);
	free(tmp->v_value);
	free(tmp);
}
