/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _putstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:07 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 18:51:48 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static	size_t	_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

ssize_t	_putstr(char *s)
{
	return (write(1, s, _strlen(s)));
}

ssize_t	_putchr(char c)
{
	return (write(1, &c, 1));
}
