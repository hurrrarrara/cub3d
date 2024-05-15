#include "minimap.h"
#include "mlx.h"
#include "raycast.h"
#include "struct.h"
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "define.h"

void	reset_map(t_map map)
{
	uint16_t	i;

	i = 0;
	while (i < map.allocated - 8)
	{
		map.map[i].face = 0;
		map.map[i++].face = 0;
		map.map[i++].face = 0;
		map.map[i++].face = 0;
		map.map[i++].face = 0;
		map.map[i++].face = 0;
		map.map[i++].face = 0;
		map.map[i++].face = 0;
	}
	while (i < map.allocated)
		map.map[i++].face = 0;
}

void	move_cam(t_camera *cam, t_map *map)
{
	const float	x = cosf(cam->angle) * cam->move.x - sinf(cam->angle) * cam->move.y;
	const float	z = sinf(cam->angle) * cam->move.x + cos(cam->angle) * cam->move.y;

	if (x && cam->world_pos.x + x > 0 && cam->world_pos.x + x < map->width)
	{
		if ((x > 0 && map->map[(int)floorf(cam->world_pos.x + x + HIT_BOX_SIZE) + (int)floorf(cam->world_pos.z) * map->width].type == 1) || \
			(x < 0 && map->map[(int)floorf(cam->world_pos.x + x - HIT_BOX_SIZE) + (int)floorf(cam->world_pos.z) * map->width].type == 1))
			cam->world_pos.x += x;
	}
	if (z && cam->world_pos.z + z > 0 && cam->world_pos.z + z < map->height)
	{
		if ((z > 0 && map->map[(int)floorf(cam->world_pos.x) + (int)floorf(cam->world_pos.z + z + HIT_BOX_SIZE) * map->width].type == 1) || \
			(z < 0 && map->map[(int)floorf(cam->world_pos.x) + (int)floorf(cam->world_pos.z + z - HIT_BOX_SIZE) * map->width].type == 1))
			cam->world_pos.z += z;
	}
	// cam->world_pos.x += cosf(cam->angle.x) * cam->move.x - sinf(cam->angle.x) * cam->move.y;
	// cam->world_pos.z += sinf(cam->angle.x) * cam->move.x + cos(cam->angle.x) * cam->move.y;
	// cam->world_pos.x += cam->move.y;
	// cam->world_pos.z -= cam->move.x;
	cam->move = (t_vec2){
		0,
		0
	};
}

int	no_event(t_data *data)
{
	data->mouse.x = WIN_WIDTH / 2;
	data->mouse.y = WIN_HEIGHT / 2;
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	move_cam(&data->cam, &data->map);
	reset_map(data->map);
	memset(data->minimap.addr, 0, data->minimap.line_length * data->minimap.height);
	memset(data->render.addr, 0, data->render.line_length * data->render.height);
	raycaster(&data->cam, data->map, &data->render, data->textures);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->render.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, WIN_WIDTH - MINIMAP_WIDTH, 0);
	return (0);
}