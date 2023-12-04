/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:30:01 by dlima             #+#    #+#             */
/*   Updated: 2023/11/28 12:59:22 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_next_delimiter(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && !is_special_char(cmd[i]) && !is_whitespace(cmd[i]) \
	&& !is_double_quote(cmd[i]) && !is_single_quote(cmd[i]) && cmd[i] != '$')
		i++;
	return (i);
}

char	*expand_var(char *new_token, char *token, int *i)
{
	int		size;
	char	*var;
	char	*var_name;
	char	*temp;

	(*i)++;
	size = find_next_delimiter(&token[*i]);
	var_name = malloc(sizeof(char) * size + 1);
	ft_strlcpy(var_name, &token[*i], size + 1);
	var = getenv(var_name);
	free(var_name);
	*i += (size - 1);
	if (var == NULL)
		return (new_token);
	else
	{
		temp = malloc(sizeof(char) *ft_strlen(new_token) + 1);
		ft_strlcpy(temp, new_token, ft_strlen(new_token) + 1);
		free(new_token);
		new_token = ft_strjoin(temp, var);
		free(temp);
	}
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

char	*process_tokens(char *token)
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
		else if (quote != 1 && is_dollar(token[i]))
			new_token = expand_var(new_token, token, &i);
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

char	**strip_tokens(char **cmd)
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
		new_cmd[i] = process_tokens(cmd[i]);
		i++;
	}
	new_cmd[arg_nbr] = NULL;
	matrix_free(cmd);
	return (new_cmd);
}