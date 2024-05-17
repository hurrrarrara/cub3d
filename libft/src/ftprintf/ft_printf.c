/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:56:49 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 15:04:33 by ihabiby          ###   ########.fr       */
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

static int	_check_format(const char *s)
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

int	ft_printf(const char *format, ...)
{
	va_list		list;
	ssize_t		tt;
	const int	n_args = _check_format(format);

	if (n_args < 0)
		return (-1);
	va_start(list, format);
	tt = _writer(format, list);
	va_end(list);
	return (tt);
}
