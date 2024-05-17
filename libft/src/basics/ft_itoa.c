/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:40:02 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

static int	_count_pow(int n)
{
	int	count;

	count = 1 + (n < 0 || !n);
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*_recur_itoa(char *s, int n)
{
	if (n < -9 || n > 9)
		s = _recur_itoa(s, n / 10);
	*s = (n % 10 > 0) * (n % 10) - (n % 10 < 0) * (n % 10) + '0';
	return (s + 1);
}

char	*ft_itoa(int n)
{
	char	*final;
	int		nchr;

	nchr = _count_pow(n);
	final = ft_calloc(nchr, sizeof(char));
	if (!final)
		return ((void *)0);
	if (n < 0)
		final[0] = '-';
	_recur_itoa(final + (n < 0), n);
	return (final);
}
