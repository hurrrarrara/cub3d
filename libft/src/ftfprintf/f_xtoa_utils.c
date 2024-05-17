/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_xtoa_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:56:53 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:24:03 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "futils.h"

int	f_count_pow(unsigned long n, int base_len)
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

ssize_t	f_recur_itoa(const int fd, unsigned long nb, char *base, int base_len)
{
	if (nb >= (unsigned )base_len)
	{
		if (f_recur_itoa(fd, nb / base_len, base, base_len) == -1)
			return (-1);
	}
	return (f_putchr(fd, base[(nb % base_len)]));
}
