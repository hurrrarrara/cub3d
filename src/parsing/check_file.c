/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:34:15 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/30 13:49:34 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_err_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if ((len > 4 && ft_strncmp(&file[len - 4], ".cub", 5)))
		return (1);
	return (len <= 4);
}

int	check_err_sides(t_map *map, size_t i, size_t row, size_t col)
{
	char	c;

	if (row == 0 || i == 0 || row == map->size[1] - 1 || i == map->size[0] - 1)
		return (1);
	c = map->map[i + ((row - 1) * col)];
	if (c != '0' && c != '1' && c != 'N' && c != 'E' && c != 'W' && c != 'S')
		return (1);
	c = map->map[i + ((row + 1) * col)];
	if (c != '0' && c != '1' && c != 'N' && c != 'E' && c != 'W' && c != 'S')
		return (1);
	c = map->map[i - 1 + (row * col)];
	if (c != '0' && c != '1' && c != 'N' && c != 'E' && c != 'W' && c != 'S')
		return (1);
	c = map->map[i + 1 + (row * col)];
	if (c != '0' && c != '1' && c != 'N' && c != 'E' && c != 'W' && c != 'S')
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
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
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
	if (!map->no || !map->so || !map->ea || !map->we || !map->c || !map->f)
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
