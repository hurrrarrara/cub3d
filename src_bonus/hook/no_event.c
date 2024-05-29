/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:08 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/28 15:26:44 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "mlx.h"
#include "struct_bonus.h"
#include "minimap_bonus.h"
#include "raycast_bonus.h"
#include "define_bonus.h"
#include "hook_bonus.h"

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

void	draw_door_notif(t_data *data)
{
	const uint16_t	x = (int)(data->cam.world_pos.x);
	const uint16_t	y = (int)(data->cam.world_pos.z);
	const uint16_t	y_offset = \
		data->final_render.height - data->door_notif.height;
	int32_t			i;
	uint32_t		color;

	if (data->map.map[x + 1 + y * data->map.width] < 3 \
		&& data->map.map[x - 1 + y * data->map.width] < 3 \
		&& data->map.map[x + (y + 1) * data->map.width] < 3 \
		&& data->map.map[x + (y - 1) * data->map.width] < 3)
		return ;
	i = 0;
	while (i < data->door_notif.width * data->door_notif.height)
	{
		color = ((uint32_t *)data->door_notif.addr)[i];
		if (color << 8)
			((uint32_t *)data->final_render.addr)\
			[113 + (i % data->door_notif.width) + (y_offset + \
			(i / data->door_notif.width)) * data->final_render.width] = color;
		i++;
	}
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
	if (data->cam.rot_l)
		data->cam.angle -= ROTATE_SPEED * 100;
	if (data->cam.rot_r)
		data->cam.angle += ROTATE_SPEED * 100;
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
	data->render_vars.anim_offset = (data->render_vars.anim_offset + \
		(ANIM_OFFSET * data->render_vars.textures[4].height)) % \
		(data->render_vars.textures[4].width * \
		data->render_vars.textures[4].height);
	raycaster(data->cam, data->map, data->render_vars);
	draw_minimap(data);
	draw_door_notif(data);
	mlx_put_image_to_window(\
		data->mlx, data->win, data->final_render.img, 0, 0);
	mlx_put_image_to_window(\
		data->mlx, data->win, data->minimap.img, WIN_WIDTH - MINIMAP_WIDTH, 0);
	return (0);
}
