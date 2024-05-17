/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _writer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:00 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 15:00:13 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static ssize_t	_chooser(const char *s, va_list list)
{
	if (*s == 'c')
		return (_print_chr(list));
	else if (*s == 's')
		return (_print_str(list));
	else if (*s == 'p')
		return (_print_ptr(list));
	else if (*s == 'd' || *s == 'u' || *s == 'i')
		return (_print_dec(list, *s));
	else if (*s == 'x' || *s == 'X')
		return (_print_hex(list, *s));
	return (_putstr("%"));
}

ssize_t	_writer(const char *s, va_list list)
{
	ssize_t	ret;
	size_t	tt;

	tt = 0;
	while (*s)
	{
		if (*s != '%')
		{
			ret = write(1, s, 1);
			if (ret == -1)
				return (ret);
			tt += ret;
		}
		else if (*s == '%')
		{
			s++;
			ret = _chooser(s, list);
			if (ret == -1)
				return (-1);
			tt += ret;
		}
		s++;
	}
	return (tt);
}
