/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:30:55 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (!little[0])
		return (big);
	while (big[++i] && i < len)
	{
		j = 0;
		while (big[i + j] && i + j < len && big[i + j] == little[j])
			j++;
		if (little[j] == 0)
			return (big + i);
	}
	return ((void *)0);
}
