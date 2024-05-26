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

#include <stdint.h>
#include "struct_bonus.h"
#include "define_bonus.h"
#include "math_utils_bonus.h"

void	draw_chunk(t_img *img, t_point2 pos, uint8_t type, const uint16_t width)
{
	const uint32_t	color = (type == 1) * FLOOR_COLOR + \
		(type == 2) * WALL_COLOR + (type == 3) * DOOR_CLOSE_COLOR + \
		(type == 4) * DOOR_OPEN_COLOR;
	int16_t			i;

	i = 0;
	while (i < (width) * (width))
	{
		((unsigned int *)img->addr)[(pos.x * (width)) + (i % (width)) + \
			((pos.y * (width) + (i / (width))) * img->width)] = color;
		i++;
	}
	if (type <= 1)
		return ;
}

void	draw_player(t_img *img, const t_vec3 pos, const uint16_t width)
{
	const int32_t	i = (width * pos.x) + (img->width * (int)(width * pos.z));

	((unsigned int *)img->addr)[i] = PLAYER_COLOR;
	if (i % img->width < img->width - 1)
	{
		if (i / img->width > 0)
			((unsigned int *)img->addr)[i + 1 - img->width] = PLAYER_COLOR;
		if (i / img->width < img->height - 1)
			((unsigned int *)img->addr)[i + 1 + img->width] = PLAYER_COLOR;
		((unsigned int *)img->addr)[i + 1] = PLAYER_COLOR;
	}
	if (i % img->width > 0)
	{
		if (i / img->width > 0)
			((unsigned int *)img->addr)[i - 1 - img->width] = PLAYER_COLOR;
		if (i / img->width < img->height - 1)
			((unsigned int *)img->addr)[i - 1 + img->width] = PLAYER_COLOR;
		((unsigned int *)img->addr)[i - 1] = PLAYER_COLOR;
	}
	if (i / img->width > 0)
		((unsigned int *)img->addr)[i - img->width] = PLAYER_COLOR;
	if (i / img->width < img->height - 1)
		((unsigned int *)img->addr)[i + img->width] = PLAYER_COLOR;
}

void	draw_minimap(t_data *data)
{
	const uint16_t	width_square = \
		ft_i16min(data->minimap.height / data->map.height, \
		data->minimap.width / data->map.width);
	int16_t			i;

	i = -1;
	while (++i < data->map.allocated)
	{
		draw_chunk(&data->minimap, (t_point2){\
			.x = i % data->map.width, \
			.y = i / data->map.width}, \
			data->map.map[i], width_square);
	}
	draw_player(&data->minimap, data->cam.world_pos, width_square);
}
