/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:46:13 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

static size_t	_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*final;
	size_t	i;

	if (!f)
		return ((void *)0);
	final = ft_calloc(_strlen(s) + 1, sizeof(char));
	if (!final)
		return ((void *)0);
	i = -1;
	while (++i < _strlen(s))
		final[i] = (*f)(i, s[i]);
	return (final);
}
