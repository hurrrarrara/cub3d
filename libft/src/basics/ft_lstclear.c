/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:55 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*n;
	t_list	*l;

	if (!lst || !*lst || !del)
		return ;
	l = *lst;
	n = l->next;
	while (n)
	{
		ft_lstdelone(l, del);
		l = n;
		n = l->next;
	}
	if (l)
		ft_lstdelone(l, del);
	*lst = 0;
}
