/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:02 by ihabiby           #+#    #+#             */
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

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*final;
	size_t	s1_len;
	size_t	set_len;

	set_len = _strlen(set);
	s1_len = _strlen(s1) - 1;
	if (set_len && s1)
	{
		while (*s1 && ft_strchr(set,*s1))
			s1++;
		s1_len = _strlen(s1);
		if (s1_len)
			s1_len--;
		while (s1_len && *(s1 + s1_len) && ft_strchr(set,*(s1 + s1_len)))
			s1_len--;
	}
	if (s1 && *s1)
		final = ft_calloc(s1_len + 2, sizeof(char));
	else
		return (ft_calloc(1, sizeof(char)));
	if (!final)
		return ((void *)0);
	ft_strlcpy(final, (char *)s1, s1_len + 2);
	return (final);
}
