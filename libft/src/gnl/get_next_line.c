/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:58:34 by ihabiby           #+#    #+#             */
/*   Updated: 2024/02/23 13:14:44 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

void	gnl_reset(t_buffer *buffer, t_line *line)
{
	size_t	i;

	i = -1;
	if (buffer)
	{
		while (++i < BUFFER_SIZE)
			buffer->str[i] = 0;
		buffer->offset = 0;
	}
	if (line)
		if (line->str)
			free(line->str);
}

char	*gnl_strdup(t_uc	*s, size_t len)
{
	size_t	i;
	char	*final;

	if (!s)
		return (NULL);
	final = malloc((len + 1) * sizeof(char));
	if (!final)
		return (free(s), NULL);
	i = -1;
	while (s[++i])
		final[i] = s[i];
	final[i] = 0;
	free(s);
	return (final);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf[FD_MAX + 1];
	struct s_line	line;

	line.str = (void *)0;
	line.size = 0;
	line.len = 0;
	if (fd < 0 || fd > FD_MAX)
		return ((void *)0);
	while (!line.str || line.str[line.len - 1] != '\n')
	{
		if (buf[fd].offset == BUFFER_SIZE || !buf[fd].str[buf[fd].offset])
		{
			if (read(fd, buf[fd].str, BUFFER_SIZE) < 0)
				return (gnl_reset(&buf[fd], &line), NULL);
			buf[fd].offset = 0;
			if (!buf[fd].str[buf[fd].offset])
				return (gnl_strdup(line.str, line.len));
		}
		gnl_append(&line, &buf[fd], buf[fd].str + buf[fd].offset);
		if (!(line.str))
			return (gnl_reset(&buf[fd], &line), NULL);
	}
	return (gnl_strdup(line.str, line.len));
}
