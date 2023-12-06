/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:05:42 by dlima             #+#    #+#             */
/*   Updated: 2023/12/05 16:19:45 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_error(int error_code, char *error_msg, char *file)
{
	g_exit_status = error_code;
	printf("%s: %s\n", file, error_msg);
}
