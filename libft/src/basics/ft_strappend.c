/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:28:08 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:28:11 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

char	*ft_strappend(char *src, const char c)
{
	char	*final;

	final = ft_calloc(ft_strlen(src) + 2, sizeof(char));
	if (!final)
		return (NULL);
	ft_memmove(final, src, ft_strlen(src));
	final[ft_strlen(src)] = c;
	if (src)
		free(src);
	return (final);
}
