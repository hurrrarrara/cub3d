/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:10:30 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != (unsigned char)c && s[i])
		i++;
	if (s[i] != (unsigned char)c)
		return (0);
	return ((char *)(s + i));
}
