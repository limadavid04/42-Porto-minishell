/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <psousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:40:18 by psousa            #+#    #+#             */
/*   Updated: 2022/11/15 14:11:55 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_leng(char const *chr)
{
	int	len;

	len = 0;
	while (chr[len] != '\0')
		len += 1;
	return (len);
}

static int	ft_check(char c, const char *s)
{
	size_t	f;

	f = 0;
	while (s[f])
	{
		if (s[f] == c)
			return (1);
		f++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*chr;
	size_t	d;
	size_t	get;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	get = 0;
	while (s1[get] && ft_check(s1[get], set))
		get++;
	end = get_leng(s1);
	while (end > get && ft_check(s1[end - 1], set))
		end--;
	chr = (char *)malloc(sizeof(*s1) * (end - get + 1));
	if (!chr)
		return (NULL);
	d = 0;
	while (get < end)
		chr[d++] = s1[get++];
	chr[d] = 0;
	return (chr);
}
