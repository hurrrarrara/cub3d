/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_putstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:07 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:21:31 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "futils.h"

static	size_t	f_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

ssize_t	f_putstr(const int fd, char *s)
{
	return (write(fd, s, f_strlen(s)));
}

ssize_t	f_putchr(const int fd, char c)
{
	return (write(fd, &c, 1));
}
