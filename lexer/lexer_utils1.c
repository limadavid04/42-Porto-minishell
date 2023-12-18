/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:06:25 by dlima             #+#    #+#             */
/*   Updated: 2023/12/18 11:45:24 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_whitespace(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	is_special_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int	is_single_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_double_quote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}
