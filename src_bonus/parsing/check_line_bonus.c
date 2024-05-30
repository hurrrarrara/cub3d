/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:01:42 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/30 14:49:05 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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
