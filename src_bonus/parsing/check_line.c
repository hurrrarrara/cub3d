/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:01:42 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/21 17:34:58 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	line_empty(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

int	line_ismap(char *line)
{
	size_t	i;

	i = 0;
	if (line_empty(line))
		return (0);
	while (line[i])
	{
		if (line[i] != '\n' && line[i] != ' ' && line[i] != '0' && \
			line[i] != '1' && line[i] != 'N' && line[i] != 'S' && \
			line[i] != 'W' && line[i] != 'E' && line[i] != '2')
			return (0);
		i++;
	}
	return (1);
}
