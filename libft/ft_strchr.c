/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <psousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:22:34 by psousa            #+#    #+#             */
/*   Updated: 2022/11/15 14:11:55 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	nik;
	int		i;

	nik = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == nik)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == nik)
		return ((char *)s + i);
	return (0);
}
