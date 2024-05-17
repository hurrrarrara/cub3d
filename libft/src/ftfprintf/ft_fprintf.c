/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:56:49 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:21:50 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "futils.h"

static int	f_check_var(const char c)
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

static int	f_check_format(const char *s)
{
	int	n;

	if (!s)
		return (-1);
	n = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (f_check_var(*(++s)))
				n++;
			else
				return (-1);
		}
		s++;
	}
	return (n);
}

int	ft_fprintf(const int fd, const char *format, ...)
{
	va_list		list;
	ssize_t		tt;
	const int	n_args = f_check_format(format);

	if (n_args < 0)
		return (-1);
	va_start(list, format);
	tt = f_writer(fd, format, list);
	va_end(list);
	return (tt);
}
