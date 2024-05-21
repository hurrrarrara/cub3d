/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:50:42 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/21 17:33:33 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_map(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->c = NULL;
	map->f = NULL;
	map->map = NULL;
	map->size[0] = 0;
	map->size[1] = 0;
}

void	free_map(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->ea);
	free(map->we);
	free(map->map);
	free(map->f);
	free(map->c);
}

int	parsing(t_map *map, char **argv)
{
	int		fd;

	if (!check_err_extension(argv[1]))
	{
		perror("Error\nBad file extension\n");
		return (1);
	}
	init_map(map);
	fd = open(argv[1], O_RDONLY);
	if (!get_tex(fd, map) || !get_map(fd, map) || check_err_tex(map))
	{
		free_map(map);
		perror("Error\nBad file format\n");
		return (1);
	}
	if (check_err_map(map))
	{
		free_map(map);
		perror("Error\nBad map format\n");
		return (1);
	}
	return (0);
}
