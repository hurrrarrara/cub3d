/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:28:19 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:07:14 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

static void	recur_putnbr_fd(int n, int fd)
{
	if (n < -9 || n > 9)
		recur_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10 > 0) * (n % 10) - (n % 10 < 0) * (n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd == -1)
		return ;
	if (n < 0)
		ft_putchar_fd('-', fd);
	recur_putnbr_fd(n, fd);
}
