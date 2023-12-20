/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:26:37 by psousa            #+#    #+#             */
/*   Updated: 2023/12/12 16:17:43 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_words(char **word, int i, int flag)
{
	while (word[i])
	{
		printf("%s", word[i]);
		if (word [i + 1])
			printf(" ");
		i++;
	}
	if (flag == 1)
		printf("\n");
}

void	b_echo(char **cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (!cmd || !cmd[i])
	{
		printf("\n");
		return ;
	}
	while (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		flag = 0;
		i++;
	}
	print_words(cmd, i, flag);
	g_exit_status = 0;
}
