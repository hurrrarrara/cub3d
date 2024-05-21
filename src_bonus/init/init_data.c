#include "src/basics/basics.h"
#include "struct.h"
#include "define.h"
#include "mlx.h"
#include "init.h"
#include <math.h>
#include <stdint.h>
#include "quit.h"

void	init_cam(t_map *map, t_camera *camera)
{
	camera->fov = 120;
	int	i;

	i = 0;
	while (i < map->allocated)
	{
		if (ft_strchr("NSEW",map->map[i]))
		{
			camera->world_pos = (t_vec3){
				(i % map->width) + 0.5,
				0.1,
				(int)(i / map->width) + 0.5
			};
			camera->angle = ((map->map[i] == 'S') * M_PI / 2) - \
				((map->map[i] == 'N') * M_PI / 2) + \
				((map->map[i] == 'W') * M_PI);
			map->map[i] = '0';
		}
		i++;
	}
}

void	init_render_vars(t_data *data)
{
	data->render_vars.render_map = (uint32_t *)data->final_render.addr;
	data->render_vars.width = 549;
	data->render_vars.ceiling = (t_color){.r = data->map.c[0], .g = data->map.c[1], .b = data->map.c[2]};
	data->render_vars.floor = (t_color){.r = data->map.f[0], .g = data->map.f[1], .b = data->map.f[2]};
	data->render_vars.textures[0] = xpm_to_image(data, data->map.no);
	data->render_vars.textures[1] = xpm_to_image(data, data->map.so);
	data->render_vars.textures[2] = xpm_to_image(data, data->map.ea);
	data->render_vars.textures[3] = xpm_to_image(data, data->map.we);
	data->render_vars.textures[4] = xpm_to_image(data, DOOR_TEXT);
	data->door_notif = xpm_to_image(data, DOOR_NOTIF);
	data->pause_screen = xpm_to_image(data, PAUSE_SCREEN);
	if (!data->render_vars.textures[0].img || \
		!data->render_vars.textures[1].img || \
		!data->render_vars.textures[2].img || \
		!data->render_vars.textures[3].img || \
		!data->render_vars.textures[4].img || \
		!data->door_notif.img || \
		!data->pause_screen.img)
		quit(data, 1);
}

t_bool	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		quit(data, 1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "graph");
	if (!data->win)
		quit(data, 1);
	init_hook(data);
	if (!init_image(data, &data->final_render, WIN_WIDTH, WIN_HEIGHT))
		quit(data, 1);
	init_cam(&data->map, &data->cam);
	init_render_vars(data);
	return (TRUE);
}
