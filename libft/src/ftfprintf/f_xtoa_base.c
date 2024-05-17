/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_xtoa_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:40:02 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:25:13 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "futils.h"

ssize_t	f_itoa_base(const int fd, int nb, char *base, int base_len)
{
	int				signe;
	unsigned int	unb;

	signe = 0;
	if (nb < 0)
	{
		if (f_putstr(fd, "-") == -1)
			return (-1);
		unb = -nb;
		signe++;
	}
	else
		unb = nb;
	if (f_recur_itoa(fd, unb, base, base_len) == -1)
		return (-1);
	return (f_count_pow(unb, base_len) + signe);
}

ssize_t	f_ltoa_base(const int fd, long nb, char *base, int base_len)
{
	int				signe;
	unsigned long	unb;

	signe = 0;
	if (nb < 0)
	{
		if (f_putstr(fd, "-") == -1)
			return (-1);
		unb = -nb;
		signe++;
	}
	else
		unb = nb;
	if (f_recur_itoa(fd, unb, base, base_len) == -1)
		return (-1);
	return (f_count_pow(unb, base_len) + signe);
}

ssize_t	f_ultoa_base(const int fd, unsigned long nb, char *base, int base_len)
{
	if (f_recur_itoa(fd, nb, base, base_len) == -1)
		return (-1);
	return (f_count_pow(nb, base_len));
}

ssize_t	f_uitoa_base(const int fd, unsigned int nb, char *base, int base_len)
{
	if (f_recur_itoa(fd, nb, base, base_len) == -1)
		return (-1);
	return (f_count_pow(nb, base_len));
}
