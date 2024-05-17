/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:03:36 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s);
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return ((void *)0);
	while (len--)
		*(dest + len) = *(s + len);
	return (dest);
}
