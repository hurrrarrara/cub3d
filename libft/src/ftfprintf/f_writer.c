/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_writer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:00 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:21:42 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "futils.h"

static ssize_t	f_chooser(const int fd, const char *s, va_list list)
{
	if (*s == 'c')
		return (f_print_chr(fd, list));
	else if (*s == 's')
		return (f_print_str(fd, list));
	else if (*s == 'p')
		return (f_print_ptr(fd, list));
	else if (*s == 'd' || *s == 'u' || *s == 'i')
		return (f_print_dec(fd, list, *s));
	else if (*s == 'x' || *s == 'X')
		return (f_print_hex(fd, list, *s));
	return (f_putstr(fd, "%"));
}

ssize_t	f_writer(const int fd, const char *s, va_list list)
{
	ssize_t	ret;
	size_t	tt;

	tt = 0;
	while (*s)
	{
		if (*s != '%')
		{
			ret = write(fd, s, 1);
			if (ret == -1)
				return (ret);
			tt += ret;
		}
		else if (*s == '%')
		{
			s++;
			ret = f_chooser(fd, s, list);
			if (ret == -1)
				return (-1);
			tt += ret;
		}
		s++;
	}
	return (tt);
}
