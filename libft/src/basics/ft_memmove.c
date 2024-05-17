/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:46:51 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (dest || src)
	{
		if (dest < src)
			while (++i < n)
				*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		else
			while (n--)
				*((unsigned char *)dest + n) = *((unsigned char *)src + n);
	}
	return (dest);
}
