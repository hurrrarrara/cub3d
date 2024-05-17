/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:03 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 14:59:19 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

ssize_t	_print_chr(va_list list)
{
	char	c;

	c = (char)va_arg(list, int);
	return (_putchr(c));
}

ssize_t	_print_str(va_list list)
{
	char	*s;

	s = va_arg(list, char *);
	if (s)
		return (_putstr(s));
	return (write(1, "(null)", 6));
}

ssize_t	_print_ptr(va_list list)
{
	unsigned long	ptr;
	ssize_t			ret;

	ptr = va_arg(list, unsigned long);
	if (ptr)
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		ret = _ultoa_base(ptr, "0123456789abcdef", 16);
		if (ret == -1)
			return (-1);
		return (ret + 2);
	}
	return (write(1, "(nil)", 5));
}

ssize_t	_print_dec(va_list list, char c)
{
	if (c == 'i' || c == 'd')
		return (_itoa_base(va_arg(list, int), "0123456789", 10));
	return (_uitoa_base(va_arg(list, unsigned int), "0123456789", 10));
}

ssize_t	_print_hex(va_list list, char c)
{
	if (c == 'x')
		return (_uitoa_base(va_arg(list, unsigned), "0123456789abcdef", 16));
	return (_uitoa_base(va_arg(list, unsigned), "0123456789ABCDEF", 16));
}
