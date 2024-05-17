/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:16:43 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:14:42 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (-(*s2));
	if (s1 && !s2)
		return (*s1);
	while (s1[i] && s2[i] && i < n -1)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}
