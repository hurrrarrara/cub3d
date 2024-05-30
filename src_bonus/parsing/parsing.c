/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:50:42 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/30 13:56:51 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "parsing_bonus.h"

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

void	free_tab(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
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
		return (print_error("Error\nCan't open file\n", 1));
	if (!get_tex(fd, map) || !get_map(fd, map))
	{
		free_map(map);
		return (close(fd), 1);
	}
	if (check_err_map(map))
	{
		free_map(map);
		ft_fprintf(2, "Error\nBad map format\n");
		return (close(fd), 1);
	}
	return (close(fd), 0);
}
