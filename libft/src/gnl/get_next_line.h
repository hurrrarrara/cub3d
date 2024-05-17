/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:58:31 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:14:15 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef unsigned char	t_uc;

typedef struct s_buffer
{
	t_uc	str[BUFFER_SIZE];
	size_t	offset;
}	t_buffer;

typedef struct s_line
{
	t_uc	*str;
	size_t	size;
	size_t	len;
}	t_line;

char	*get_next_line(int fd);
t_uc	*gnl_realloc(t_line *line, size_t plen, size_t nlen);
void	gnl_append(t_line *line, t_buffer *buffer, t_uc *buf_str);
void	gnl_reset(t_buffer *buffer, t_line *line);

#endif