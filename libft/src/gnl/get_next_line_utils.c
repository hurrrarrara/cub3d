/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:58:36 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:15:09 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_uc	*gnl_realloc(t_line *line, size_t plen, size_t nlen)
{
	t_uc	*final;
	size_t	i;

	if (nlen >= line->size)
	{
		line->size = BUFFER_SIZE * (line->size == 0) + line->size * 10;
		final = malloc(((line->size) + 1) * sizeof(t_uc));
		if (!final)
			return (gnl_reset(NULL, line), NULL);
		i = 0;
		while (i < (line->size) + 1)
			final[i++] = 0;
		i = 0;
		while (i < plen)
		{
			final[i] = line->str[i];
			i++;
		}
		return (gnl_reset(NULL, line), final);
	}
	return (line->str);
}

size_t	gnl_get_adding(t_uc *s, size_t size)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (i < size && s[i] && s[i] != '\n')
		i++;
	if (i < size && s[i] && s[i] == '\n')
		i++;
	return (i);
}

void	gnl_append(t_line *line, t_buffer *buf, t_uc *buf_str)
{
	const size_t	adding = gnl_get_adding(buf_str, BUFFER_SIZE - buf->offset);
	size_t			i;

	line->str = gnl_realloc(line, line->len, line->len + adding);
	if (!(line->str))
		return ;
	i = -1;
	while (++i < adding)
	{
		(line->str)[line->len + i] = buf_str[i];
		buf_str[i] = 0;
	}
	line->len += adding;
	buf->offset += adding;
}
