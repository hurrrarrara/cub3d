/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xtoa_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:40:02 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 15:01:26 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

ssize_t	_itoa_base(int nb, char *base, int base_len)
{
	int				signe;
	unsigned int	unb;

	signe = 0;
	if (nb < 0)
	{
		if (_putstr("-") == -1)
			return (-1);
		unb = -nb;
		signe++;
	}
	else
		unb = nb;
	if (_recur_itoa(unb, base, base_len) == -1)
		return (-1);
	return (_count_pow(unb, base_len) + signe);
}

ssize_t	_ltoa_base(long nb, char *base, int base_len)
{
	int				signe;
	unsigned long	unb;

	signe = 0;
	if (nb < 0)
	{
		if (_putstr("-") == -1)
			return (-1);
		unb = -nb;
		signe++;
	}
	else
		unb = nb;
	if (_recur_itoa(unb, base, base_len) == -1)
		return (-1);
	return (_count_pow(unb, base_len) + signe);
}

ssize_t	_ultoa_base(unsigned long nb, char *base, int base_len)
{
	if (_recur_itoa(nb, base, base_len) == -1)
		return (-1);
	return (_count_pow(nb, base_len));
}

ssize_t	_uitoa_base(unsigned int nb, char *base, int base_len)
{
	if (_recur_itoa(nb, base, base_len) == -1)
		return (-1);
	return (_count_pow(nb, base_len));
}
