#include "minimap.h"
#include "mlx.h"
#include "raycast.h"
#include "struct.h"
#include <linux/limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "define.h"


void	move_cam(t_camera *cam, t_map *map)
{
	const float	x = cosf(cam->angle) * cam->move.x - sinf(cam->angle) * cam->move.y;
	const float	z = sinf(cam->angle) * cam->move.x + cos(cam->angle) * cam->move.y;

	if (cam->world_pos.x + x > 0 && cam->world_pos.x + x < map->width)
	{
		if ((x > 0 && map->map[(int)floorf(cam->world_pos.x + x + HIT_BOX_SIZE) + (int)floorf(cam->world_pos.z) * map->width] % 4 < 2) || \
			(x < 0 && map->map[(int)floorf(cam->world_pos.x + x - HIT_BOX_SIZE) + (int)floorf(cam->world_pos.z) * map->width] % 4 < 2))
			cam->world_pos.x += x;
	}
	if (cam->world_pos.z + z > 0 && cam->world_pos.z + z < map->height)
	{
		if ((z > 0 && map->map[(int)floorf(cam->world_pos.x) + (int)floorf(cam->world_pos.z + z + HIT_BOX_SIZE) * map->width] % 4 < 2) || \
			(z < 0 && map->map[(int)floorf(cam->world_pos.x) + (int)floorf(cam->world_pos.z + z - HIT_BOX_SIZE) * map->width] % 4 < 2))
			cam->world_pos.z += z;
	}
	cam->move = (t_vec2){
		0,
		0
	};
}

// void	transpose_render_map_to_final_render(t_rendervars render_vars, t_img final_render)
// {
// 	const uint8_t	ratio = final_render.width / render_vars.render_height;

// 	int32_t	x;
// 	int32_t	y;
// 	int32_t	xi;
// 	int32_t	yi;

// 	x = 0;
// 	xi = 0;
// 	while (x < render_vars.render_height)
// 	{
// 		y = 0;
// 		yi = 0;
// 		while (y < render_vars.render_width)
// 		{
// 			((uint32_t *)final_render.addr)[(x * ratio) + xi + (final_render.height - 1 - (y * ratio) + yi) * final_render.width] = render_vars.render_map[y + (x * render_vars.render_width)];
// 			yi++;
// 			y += (yi == ratio);
// 			yi = (yi) % ratio;
// 		}
// 		xi++;
// 		x += (xi == ratio);
// 		xi = (xi) % (ratio);
// 	}
// }

void	draw_door_notif(t_data *data)
{
	const uint16_t	x = (int)(data->cam.world_pos.x);
	const uint16_t	y = (int)(data->cam.world_pos.z);
	uint32_t		i;
	uint32_t		color;
	const uint16_t	y_offset = data->final_render.height - data->door_notif.height;

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
			((uint32_t *)data->final_render.addr)[113 + (i % data->door_notif.width) + (y_offset + (i / data->door_notif.width)) * data->final_render.width] = color;
		i++;
	}
}

int	no_event(t_data *data)
{
	data->mouse.x = WIN_WIDTH / 2;
	data->mouse.y = WIN_HEIGHT / 2;
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	move_cam(&data->cam, &data->map);
	// memset(data->map.map, 0, data->map.allocated);
	memset(data->minimap.addr, 0, data->minimap.line_length * data->minimap.height);
	// memset(data->final_render.addr, 0, data->final_render.line_length * data->final_render.height);
	data->render_vars.anim_offset = (data->render_vars.anim_offset + ANIM_OFFSET) % data->render_vars.textures[0].width;
	raycaster(data->cam, data->map, data->render_vars);
	// transpose_render_map_to_final_render(data->render_vars, data->final_render);
	draw_minimap(data);
	draw_door_notif(data);
	// printf("eeee\n");
	mlx_put_image_to_window(data->mlx, data->win, data->final_render.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, WIN_WIDTH - MINIMAP_WIDTH, 0);
	return (0);
}