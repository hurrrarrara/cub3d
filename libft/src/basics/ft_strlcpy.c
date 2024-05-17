/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:47:28 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (!size)
		return (len);
	size--;
	while (size-- && *src)
		*dest++ = *src++;
	*(dest) = 0;
	return (len);
}
