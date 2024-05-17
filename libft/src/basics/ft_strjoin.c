/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:31 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*dest;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	dest = ft_calloc(sizeof(char), l1 + l2 + 1);
	if (!dest)
		return ((void *)0);
	ft_strlcat(dest, (char *)s1, l1 + l2 + 1);
	ft_strlcat(dest, (char *)s2, l1 + l2 + 1);
	return (dest);
}
