/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:19:35 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/21 17:10:39 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_realloc_2d_2(char **newmap, char **map, char *line)
{
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	newmap = malloc(sizeof (char *) * (i + 2));
	if (!newmap)
	{
		i = 0;
		while (map[i])
			free(map[i++]);
		free(map);
		return (NULL);
	}
	newmap[i + 1] = NULL;
	i = -1;
	while (map[++i])
		newmap[i] = map[i];
	newmap[i] = line;
	free(map);
	return (newmap);
}

char	**ft_realloc_2d(char **map, char *line)
{
	char	**newmap;
	size_t	i;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!map)
	{
		newmap = malloc(sizeof (char *) * 2);
		if (!newmap)
			return (NULL);
		newmap[1] = NULL;
		newmap[0] = line;
		return (newmap);
	}
	ft_realloc_2d_2(newmap, map, line);
	/*i = 0;
	while (map[i])
		i++;
	newmap = malloc(sizeof (char *) * (i + 2));
	if (!newmap)
	{
		i = 0;
		while (map[i])
			free(map[i++]);
		free(map);
		return (NULL);
	}
	newmap[i + 1] = NULL;
	i = -1;
	while (map[++i])
		newmap[i] = map[i];
	newmap[i] = line;
	free(map);*/
	return (newmap);
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

int	get_map_2(char *line, t_map *map, char **map2d, int fd)
{
	map->map = malloc(sizeof (char) * map->size[0] * map->size[1] + 1);
	if (!map->map)
		return (0);
	map2d_to_map(map, map2d);
	free(map2d);
	if (check_err_end_file(line, fd))
		return (0);
	return (1);
}

int	get_map(int fd, t_map *map)
{
	char	*line;
	char	**map2d;

	map2d = NULL;
	line = get_next_line(fd);
	while (line && line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line_ismap(line))
	{
		map2d = ft_realloc_2d(map2d, line);
		if (!map2d)
			return (free(line), 1);
		if (ft_strlen(line) > map->size[0])
			map->size[0] = ft_strlen(line);
		map->size[1]++;
		line = get_next_line(fd);
	}
	if (get_map_2(line, map, map2d, fd))
		return (0);
	return (1);
}
