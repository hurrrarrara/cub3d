/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:39:55 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

static void	_free2d(char **a, size_t nmemb)
{
	while (nmemb--)
		free(a[nmemb]);
	free(a);
}

static size_t	_strchr(char const *s, char c)
{
	char	*p;

	p = (char *)s;
	while (*p != (unsigned char)c && *p)
		p++;
	return (p - s);
}

static size_t	_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	if (!c && *s)
		return (1);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		count++;
		while (*s == c)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**final;
	char	**p;
	size_t	count;

	if (!s)
		return ((void *)0);
	count = _count(s, c);
	final = ft_calloc(count + 1, sizeof(char *));
	if (!final)
		return ((void *)0);
	p = final;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		*p = ft_substr(s, 0, _strchr(s, c));
		if (!*p)
			return (_free2d(final, p - final), (void *)0);
		s += ft_strlen(*p++);
		while (*s && *s == c)
			s++;
	}
	return (final);
}
