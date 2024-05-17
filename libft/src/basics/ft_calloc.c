/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:51:10 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "basics.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	nbytes;

	nbytes = nmemb * size;
	if (nbytes && (nbytes / size != nmemb || nbytes / nmemb != size))
		return ((void *)0);
	ret = malloc(nmemb * size);
	if (!ret)
		return ((void *)0);
	ft_bzero(ret, nbytes);
	return (ret);
}
