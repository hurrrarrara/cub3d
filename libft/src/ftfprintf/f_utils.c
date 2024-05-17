/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:03 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/20 22:41:47 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "futils.h"

ssize_t	f_print_chr(const int fd, va_list list)
{
	char	c;

	c = (char)va_arg(list, int);
	return (f_putchr(fd, c));
}

ssize_t	f_print_str(const int fd, va_list list)
{
	char	*s;

	s = va_arg(list, char *);
	if (s)
		return (f_putstr(fd, s));
	return (write(fd, "(null)", 6));
}

ssize_t	f_print_ptr(const int fd, va_list list)
{
	unsigned long	ptr;
	ssize_t			ret;

	ptr = va_arg(list, unsigned long);
	if (ptr)
	{
		if (write(fd, "0x", 2) == -1)
			return (-1);
		ret = f_ultoa_base(fd, ptr, "0123456789abcdef", 16);
		if (ret == -1)
			return (-1);
		return (ret + 2);
	}
	return (write(fd, "(nil)", 5));
}

ssize_t	f_print_dec(const int fd, va_list list, char c)
{
	if (c == 'i' || c == 'd')
		return (f_itoa_base(fd, va_arg(list, int), "0123456789", 10));
	return (f_uitoa_base(fd, va_arg(list, unsigned int), "0123456789", 10));
}

ssize_t	f_print_hex(const int fd, va_list list, char c)
{
	if (c == 'x')
		return (f_uitoa_base(fd, va_arg(list, unsigned), \
			"0123456789abcdef", 16));
	return (f_uitoa_base(fd, va_arg(list, unsigned), "0123456789ABCDEF", 16));
}
