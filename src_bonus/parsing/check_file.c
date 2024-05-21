/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:34:15 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/21 19:12:54 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_err_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len > 4 && ft_strncmp(&file[len - 5], ".cub", 5))
		return (1);
	return (0);
}

int	check_err_sides(t_map *map, size_t i, size_t row, size_t col)
{
	char	c;

	c = map->map[i + ((row - 1) * col)];
	if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'E' && c != 'W' \
		&& c != 'S')
		return (1);
	c = map->map[i + ((row + 1) * col)];
	if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'E' && c != 'W' \
		&& c != 'S')
		return (1);
	c = map->map[i - 1 + (row * col)];
	if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'E' && c != 'W' \
		&& c != 'S')
		return (1);
	c = map->map[i + 1 + (row * col)];
	if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'E' && c != 'W' \
		&& c != 'S')
		return (1);
	return (0);
}

int	check_err_map(t_map *map)
{
	size_t	row;
	size_t	col;
	size_t	player;
	char	c;

	row = -1;
	player = 0;
	while (++row < map->size[1])
	{
		col = -1;
		while (++col < map->size[0])
		{
			c = map->map[col + (row * map->size[0])];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '2')
			{
				if (check_err_sides(map, col, row, map->size[0]))
					return (1);
			}
			else if (c != ' ' && c != '1')
				return (1);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player++;
		}
	}
	return (player != 1);
}

int	check_err_tex(t_map *map)
{
	if (!map->no)
		return (1);
	else if (!map->so)
		return (1);
	else if (!map->ea)
		return (1);
	else if (!map->we)
		return (1);
	else if (!map->c)
		return (1);
	else if (!map->f)
		return (1);
	return (0);
}

int	check_err_end_file(char *line, int fd)
{
	while (line)
	{
		if (!line_empty(line))
		{
			close(fd);
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
