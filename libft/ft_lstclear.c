/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psousa <psousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:48:14 by psousa            #+#    #+#             */
/*   Updated: 2022/11/21 13:54:18 by psousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*nxt;

	if (lst == NULL || del == NULL)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		nxt = temp->next;
		del(temp->content);
		free(temp);
		temp = nxt;
	}
	*lst = NULL;
}
