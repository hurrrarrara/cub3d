/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:33:36 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

static unsigned long	_bytes_cast(unsigned char c, size_t nbytes)
{
	unsigned long	c_long;

	c_long = (unsigned char)c;
	c_long |= c_long << 8;
	c_long |= c_long << 16;
	if (nbytes > 4)
		c_long |= c_long << 32;
	return (c_long);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	c_long;
	size_t			nbytes;

	if (!n)
		return (s);
	nbytes = sizeof(unsigned long int);
	c_long = _bytes_cast(c, nbytes);
	while ((n) % nbytes)
		*(unsigned char *)(s + --n) = (unsigned char)c;
	while (n)
	{
		n -= nbytes;
		*(unsigned long *)(s + n) = c_long;
	}
	return (s);
}
