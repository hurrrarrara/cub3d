/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:19:35 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/21 15:52:02 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_realloc_2d(char **map, char *line)
{
	char	**newmap;
	size_t	i;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!map)
	{
		newmap = malloc(sizeof (char *) * 2);
		newmap[1] = NULL;
		newmap[0] = line;
		return (newmap);
	}
	else
	{
		i = 0;
		while (map[i])
			i++;
		newmap = malloc(sizeof (char *) * (i + 2));
		newmap[i + 1] = NULL;
		i = -1;
		while (map[++i])
			newmap[i] = map[i];
		newmap[i] = line;
		free(map);
		return (newmap);
	}
}

void	map2d_to_map(t_map *map, char **map2d)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	y = 0;
	while (map2d && map2d[y])
	{
		x = 0;
		while (map2d[y][x])
		{
			map->map[i++] = map2d[y][x];
			x++;
		}
		free(map2d[y]);
		while (x < map->size[0])
		{
			map->map[i++] = ' ';
			x++;
		}
		y++;
	}
	map->map[i] = '\0';
}

int	get_map(int fd, t_map *map)
{
	char	*line;
	char	**map2;

	map2 = NULL;
	line = get_next_line(fd);
	while (line && line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line_ismap(line))
	{
		map2 = ft_realloc_2d(map2, line);
		if (ft_strlen(line) > map->size[0])
			map->size[0] = ft_strlen(line);
		map->size[1]++;
		line = get_next_line(fd);
	}
	map->map = malloc(sizeof (char) * map->size[0] * map->size[1] + 1);
	map2d_to_map(map, map2);
	free(map2);
	if (check_err_end_file(line, fd, map))
		return (0);
	return (1);
}
