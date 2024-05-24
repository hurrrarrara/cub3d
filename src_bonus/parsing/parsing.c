/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:50:42 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/24 17:50:49 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "src/basics/basics.h"
#include <stdio.h>

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

t_bool	check_file(const char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd >= 0)
		return (fd);
	write(2, "Error\n", 6);
	perror(file);
	return (fd);
}

int	parsing(t_map *map, char **argv)
{
	int		fd;

	if (check_err_extension(argv[1]))
	{
		write(2, "Error\nBad file extension\n", 25);
		return (1);
	}
	init_map(map);
	fd = check_file(argv[1]);
	if (fd < 0)
		return (1);
	if (!get_tex(fd, map) || !get_map(fd, map) || check_err_tex(map))
	{
		free_map(map);
		write(2, "Error\nBad file format\n", 22);
		return (close(fd), 1);
	}
	if (check_err_map(map))
	{
		free_map(map);
		write(2, "Error\nBad map format\n", 21);
		return (close(fd), 1);
	}
	return (close(fd), 0);
}
