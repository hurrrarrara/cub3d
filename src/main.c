/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:59:22 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/30 14:52:07 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "raycast.h"
#include "src/basics/basics.h"
#include "struct.h"
#include "init.h"
#include "mlx.h"
#include "parsing.h"
#include <stdio.h>

void	debug_print_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->allocated)
	{
		if (i && !(i % map->width))
			printf("\n");
		printf("%c", map->map[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 2)
	{
		ft_putstr_fd("Error\nBad number of arguments, need one\n", 2);
		return (1);
	}
	if (parsing(&data.map, av))
		return (1);
	data.map.width = data.map.size[0];
	data.map.height = data.map.size[1];
	data.map.allocated = data.map.width * data.map.height;
	init_data(&data);
	mlx_mouse_hide(data.mlx, data.win);
	raycaster(data.cam, data.map, data.render_vars);
	mlx_put_image_to_window(data.mlx, data.win, data.final_render.img, 0, 0);
	data.pause_toggle = 0;
	mlx_loop(data.mlx);
	return (0);
}
