/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:30:01 by dlima             #+#    #+#             */
/*   Updated: 2023/12/20 13:04:44 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_var(char *new_token, char *token, int *i, t_status *status)
{
	int		size;
	char	*var;

	(*i)++;
	if (token[*i] == '?')
	{
		var = ft_itoa(g_exit_status);
		new_token = join_var_expansion_with_token(new_token, var);
		free(var);
		return (new_token);
	}
	size = find_next_delimiter(&token[*i]);
	if (size == 0)
	{
		new_token = add_char('$', new_token);
		(*i)--;
		return (new_token);
	}
	var = get_var(size, &token[*i], status);
	*i += (size - 1);
	if (var != NULL)
		new_token = join_var_expansion_with_token(new_token, var);
	return (new_token);
}

static char	*handle_double_quote(char *new_token, char cur_char, int *quote)
{
	if (!is_double_quote(cur_char))
		new_token = add_char(cur_char, new_token);
	else if (is_double_quote(cur_char))
		*quote = 0;
	return (new_token);
}

static char	*handle_single_quote(char *new_token, char cur_char, int *quote)
{
	if (!is_single_quote(cur_char))
		new_token = add_char(cur_char, new_token);
	else if (is_single_quote(cur_char))
		*quote = 0;
	return (new_token);
}

char	*process_tokens(char *token, int expand, t_status *status)
{
	int		i;
	char	*new_token;
	int		quote;

	quote = 0;
	i = 0;
	new_token = ft_strdup("");
	while (token[i] != '\0')
	{
		if (quote == 0 && is_single_quote(token[i]))
			quote = 1;
		else if (quote == 0 && is_double_quote(token[i]))
			quote = 2;
		else if (quote != 1 && is_dollar(token[i]) && expand == 1)
			new_token = expand_var(new_token, token, &i, status);
		else if (quote == 0 && !is_double_quote(token[i]) \
		&& !is_single_quote(token[i]))
			new_token = add_char(token[i], new_token);
		else if (quote == 1)
			new_token = handle_single_quote(new_token, token[i], &quote);
		else if (quote == 2)
			new_token = handle_double_quote(new_token, token[i], &quote);
		i++;
	}
	return (new_token);
}

char	**strip_tokens(char **cmd, t_status *status)
{
	char	**new_cmd;
	int		i;
	int		arg_nbr;

	i = 0;
	arg_nbr = 0;
	while (cmd[arg_nbr])
		arg_nbr++;
	new_cmd = malloc(sizeof(char *) * (arg_nbr + 1));
	while (cmd[i])
	{
		new_cmd[i] = process_tokens(cmd[i], 1, status);
		i++;
	}
	new_cmd[arg_nbr] = NULL;
	matrix_free(cmd);
	return (new_cmd);
}
