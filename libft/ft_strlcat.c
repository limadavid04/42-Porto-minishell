/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <psousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:32:12 by psousa            #+#    #+#             */
/*   Updated: 2022/11/16 14:02:03 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lens;
	size_t	lend;

	if (size == 0)
		return (ft_strlen(src));
	lens = ft_strlen(src);
	lend = ft_strlen(dest);
	j = lend;
	i = 0;
	if (size < lend)
		return (lens + size);
	while (src[i] && j < (size - 1))
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (lend + lens);
}
