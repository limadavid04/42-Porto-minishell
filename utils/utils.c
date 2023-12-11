/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:05:42 by dlima             #+#    #+#             */
/*   Updated: 2023/12/06 14:05:21 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void print_syntax_err(struct s_list *token)
{
	g_exit_status = SYNTAX_ERROR;
	ft_putstr_fd(SYNTAX_MSG,2);
	write(1, "`", 2);
	if (token == NULL)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd((char *)token->content, 2);
	write(1, "'", 2);
	ft_putstr_fd("\n", 2);
}

void print_error(int error_code, char *error_msg, char *file)
{
	g_exit_status = error_code;
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	// printf("%s: %s\n", file, error_msg);
}
