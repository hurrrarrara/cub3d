/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:58:48 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 03:33:11 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define_bonus.h"
#include "math_utils_bonus.h"
#include "struct_bonus.h"
#include <stdint.h>

void	draw_player(t_img *img, const int32_t i)
{
	uint8_t	x;
	uint8_t	y;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			((uint32_t *)img->addr)[i + x + y * img->width] = PLAYER_COLOR;
			x++;
		}
		y++;
	}
}


t_i32point2	get_start(t_data *data)
{
	t_i32point2	start;

	start.x = ft_i16max(0, data->cam.world_pos.x - ((MINIMAP_WIDTH / MINIMAP_CUB_WIDTH) / 2) - 1);
	start.y = ft_i16max(0, data->cam.world_pos.z - ((MINIMAP_HEIGHT / MINIMAP_CUB_WIDTH) / 2) - 1);

	return (start);
}


t_i32point2	get_end(t_data *data)
{
	t_i32point2	start;

	start.x = ft_i16min(data->map.width, data->cam.world_pos.x + ((MINIMAP_WIDTH / MINIMAP_CUB_WIDTH) / 2) + 2);
	start.y = ft_i16min(data->map.height, data->cam.world_pos.z + ((MINIMAP_HEIGHT / MINIMAP_CUB_WIDTH) / 2) + 2);

	return (start);
}

void	draw_chunk(t_data *data, t_i32point2 start, uint8_t type)
{
	const uint32_t	color = (type == 1) * FLOOR_COLOR + \
		(type == 2) * WALL_COLOR + (type == 3) * DOOR_CLOSE_COLOR + (type == 4) * DOOR_OPEN_COLOR;
	int32_t	x;
	int32_t	y;
	t_i32point2	end;

	end.x = ft_i32min(MINIMAP_CUB_WIDTH, data->minimap.width - start.x);
	end.y = ft_i32min(MINIMAP_CUB_WIDTH, data->minimap.height - start.y);

	y = 0;
	while (y < end.y)
	{
		x = 0;
		while (x < end.x)
		{
			((uint32_t *)data->minimap.addr)[start.x + x + ((start.y + y) * data->minimap.width)] = color;
			x++;
		}
		y++;
	}
	
}

void	draw_minimap(t_data *data)
{
	t_i32point2	start = get_start(data);
	t_i32point2	end = get_end(data);
	int16_t	x;
	int16_t	y;

	y = 0;
	while (y < end.y - start.y)
	{
		x = 0;
		while (x < end.x - start.x)
		{
			draw_chunk(data, \
				(t_i32point2){
					ft_i32max(0, (MINIMAP_WIDTH / 2) - (data->cam.world_pos.x - (start.x + x)) * MINIMAP_CUB_WIDTH), \
					ft_i32max(0, (MINIMAP_HEIGHT / 2) - (data->cam.world_pos.z - (start.y + y)) * MINIMAP_CUB_WIDTH)}, \
			data->map.map[start.x + x + (start.y + y) * data->map.width]);
			x++;
		}
		y++;
	}
	draw_player(&data->minimap, MINIMAP_PLAYER_POS);
}