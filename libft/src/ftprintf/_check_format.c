/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:10 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 14:57:10 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	_check_var(const char c)
{
	if (c == 'c')
		return (1);
	if (c == 's')
		return (1);
	if (c == 'p')
		return (1);
	if (c == 'd')
		return (1);
	if (c == 'i')
		return (1);
	if (c == 'u')
		return (1);
	if (c == 'x')
		return (1);
	if (c == 'X')
		return (1);
	if (c == '%')
		return (1);
	return (0);
}

int	_check_format(const char *s)
{
	int	n;

	if (!s)
		return (-1);
	n = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (_check_var(*(++s)))
				n++;
			else
				return (-1);
		}
		s++;
	}
	return (n);
}
