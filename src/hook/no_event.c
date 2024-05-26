/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:08 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 00:16:16 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "mlx.h"
#include "raycast.h"
#include "struct.h"
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "define.h"
#include "hook.h"

void	move_cam(t_camera *cam, t_map *map)
{
	const float	x = cosf(cam->angle) * cam->move.x - \
		sinf(cam->angle) * cam->move.y;
	const float	z = sinf(cam->angle) * cam->move.x + \
		cos(cam->angle) * cam->move.y;

	if (cam->world_pos.x + x > 0 && cam->world_pos.x + x < map->width)
	{
		if ((x > 0 && map->map[(int)floorf(cam->world_pos.x + x + HIT_BOX_SIZE) \
			+ (int)floorf(cam->world_pos.z) * map->width] % 4 < 2) || \
			(x < 0 && map->map[(int)floorf(cam->world_pos.x + x - HIT_BOX_SIZE) \
			+ (int)floorf(cam->world_pos.z) * map->width] % 4 < 2))
			cam->world_pos.x += x;
	}
	if (cam->world_pos.z + z > 0 && cam->world_pos.z + z < map->height)
	{
		if ((z > 0 && map->map[(int)floorf(cam->world_pos.x) + (int)floorf(\
			cam->world_pos.z + z + HIT_BOX_SIZE) * map->width] % 4 < 2) || \
			(z < 0 && map->map[(int)floorf(cam->world_pos.x) + (int)floorf(\
			cam->world_pos.z + z - HIT_BOX_SIZE) * map->width] % 4 < 2))
			cam->world_pos.z += z;
	}
	cam->move = (t_vec2){0, 0};
}

void	move(t_data *data)
{
	if (data->fw)
		data->cam.move.x += MOVE_SPEED;
	if (data->bw)
		data->cam.move.x -= MOVE_SPEED;
	if (data->l)
		data->cam.move.y -= MOVE_SPEED;
	if (data->r)
		data->cam.move.y += MOVE_SPEED;
}

int	no_event(t_data *data)
{
	move(data);
	if (data->pause_toggle >= 1)
		return (active_pause(data), 0);
	mlx_mouse_hide(data->mlx, data->win);
	data->mouse.x = WIN_WIDTH / 2;
	data->mouse.y = WIN_HEIGHT / 2;
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	move_cam(&data->cam, &data->map);
	memset(data->minimap.addr, 0, \
		data->minimap.line_length * data->minimap.height);
	raycaster(data->cam, data->map, data->render_vars);
	draw_minimap(data);
	mlx_put_image_to_window(\
		data->mlx, data->win, data->final_render.img, 0, 0);
	mlx_put_image_to_window(\
		data->mlx, data->win, data->minimap.img, WIN_WIDTH - MINIMAP_WIDTH, 0);
	return (0);
}
