/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:10:34 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*dest;

	if (!s || !len)
		return (ft_calloc(sizeof(char), 1));
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_calloc(sizeof(char), 1));
	if (start + len > s_len)
		len = s_len - start;
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return ((void *)0);
	i = -1;
	while (++i < len && s[i])
		dest[i] = s[start + i];
	return (dest);
}
