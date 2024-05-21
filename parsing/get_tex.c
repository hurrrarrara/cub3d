/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:30:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/21 14:44:03 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_path(char *line)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	while (line[i] == ' ' || line[i] == '\n')
	{
		line[i] = '\0';
		i++;
	}
	if (line[i] && line[i] != ' ' && line[i] != '\n')
		return (NULL);
	return (ft_strdup(&line[start]));
}

int	get_info(char *line, t_map *map, size_t i)
{
	if (ft_strncmp(&line[i], "NO ", 3) == 0 && !map->no)
		map->no = get_path(&line[2]);
	else if (ft_strncmp(&line[i], "SO ", 3) == 0 && !map->so)
		map->so = get_path(&line[2]);
	else if (ft_strncmp(&line[i], "WE ", 3) == 0 && !map->we)
		map->we = get_path(&line[2]);
	else if (ft_strncmp(&line[i], "EA ", 3) == 0 && !map->ea)
		map->ea = get_path(&line[2]);
	else if (ft_strncmp(&line[i], "F ", 2) == 0 && !map->f)
		map->f = get_color(&line[1]);
	else if (ft_strncmp(&line[i], "C ", 2) == 0 && !map->c)
		map->c = get_color(&line[1]);
	else if (!line_empty(line))
		return (0);
	return (1);
}

int	get_tex(int fd, t_map *map)
{
	size_t	i;
	char	*line;

	line = get_next_line(fd);
	while (line && check_err_tex(map))
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (!get_info(line, map, i))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
