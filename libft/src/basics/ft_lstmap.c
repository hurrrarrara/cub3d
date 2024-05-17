/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:46:48 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*nxt;
	void	*cnt;

	if (!lst || !f || !del)
		return ((void *)0);
	cnt = (*f)(lst->content);
	new = ft_lstnew(cnt);
	if (!new)
		return ((*del)(cnt), (void *)0);
	nxt = new;
	while (lst->next)
	{
		lst = lst->next;
		cnt = (*f)(lst->content);
		nxt->next = ft_lstnew(cnt);
		if (!nxt->next)
			return ((*del)(cnt), ft_lstclear(&new, del), (void *)0);
		nxt = nxt->next;
	}
	return (new);
}
