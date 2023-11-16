/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:41:31 by psousa            #+#    #+#             */
/*   Updated: 2023/11/16 10:41:35 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*command;

	(void)envp;
	if (argc > 1 && argv)
	{
		printf("Error: Wrong arguments!");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		sig_handling();
		command = readline("$> ");
		if (handle_ctrl_d(command))
			break ;
		add_history(command);
		if (check_input(command) == 0)
			lexer(command);
		free(command);
	}
	return (EXIT_SUCCESS);
}
