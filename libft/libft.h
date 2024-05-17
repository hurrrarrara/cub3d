/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:32:37 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:32:58 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "./src/basics/basics.h"
# include <stdlib.h>

typedef unsigned char	t_uc;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

char	*get_next_line(int fd);
int		ft_printf(const char *format, ...);
int		ft_fprintf(const int fd, const char *format, ...);

#endif
