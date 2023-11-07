/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <psousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:57:59 by psousa            #+#    #+#             */
/*   Updated: 2022/11/15 14:11:55 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t						i;
	unsigned char				*src;
	unsigned char				*dest;

	src = (unsigned char *)str1;
	dest = (unsigned char *)str2;
	i = 0;
	while (i < n && *(src + i) == *(dest + i))
		i++;
	if (i == n)
		return (0);
	return (*(src + i) - *(dest + i));
}
