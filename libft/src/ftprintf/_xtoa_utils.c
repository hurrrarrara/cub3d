/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xtoa_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:56:53 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 15:01:45 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	_count_pow(unsigned long n, int base_len)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n = n / base_len;
	}
	return (count);
}

ssize_t	_recur_itoa(unsigned long nb, char *base, int base_len)
{
	if (nb >= (unsigned )base_len)
	{
		if (_recur_itoa(nb / base_len, base, base_len) == -1)
			return (-1);
	}
	return (_putchr(base[(nb % base_len)]));
}
