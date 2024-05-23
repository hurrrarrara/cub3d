#include "libft.h"
#include "src/basics/basics.h"
#include "struct.h"
#include "define.h"
#include "mlx.h"
#include "init.h"
#include <math.h>
#include <stdint.h>
#include "quit.h"
#include "math_utils.h"

void	init_cam(t_map *map, t_camera *camera)
{
	int	i;

	i = 0;
	camera->fov = 120;
	while (i < map->allocated)
	{
		if (ft_strchr("NSEW", map->map[i]))
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

void	clean_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->map.allocated)
	{
		data->map.map[i] = (data->map.map[i] - 47) * (data->map.map[i] != ' ');
		i++;
	}
}

void	fetch_texture(t_data *data)
{
	if (!xpm_to_image(data, data->render_vars.textures, data->map.no))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 1, data->map.so))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 2, data->map.ea))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 3, data->map.we))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 4, DOOR_TEXT))
		quit(data, 1);
	if (!xpm_to_image(data, &data->door_notif, DOOR_NOTIF))
		quit(data, 1);
	if (!xpm_to_image(data, &data->pause_screen, PAUSE_SCREEN))
		quit(data, 1);
}

void	init_render_vars(t_data *data)
{
	data->render_vars.render_map = (uint32_t *)data->final_render.addr;
	data->render_vars.width = 549;
	data->render_vars.ceiling = (t_color){\
		.r = data->map.c[0], \
		.g = data->map.c[1], \
		.b = data->map.c[2]};
	data->render_vars.floor = (t_color){\
		.r = data->map.f[0], \
		.g = data->map.f[1], \
		.b = data->map.f[2]};
	data->render_vars.y_off = 1;
	fetch_texture(data);
}

t_bool	init_data(t_data *data)
{
	const uint16_t	width_square = ft_i16min(MINIMAP_HEIGHT / data->map.height, \
		MINIMAP_WIDTH / data->map.width);

	data->fw = FALSE;
	data->bw = FALSE;
	data->l = FALSE;
	data->r = FALSE;
	data->mlx = mlx_init();
	if (!data->mlx)
		quit(data, 1);
	if (!init_image(data, &data->final_render, WIN_WIDTH, WIN_HEIGHT))
		quit(data, 1);
	if (!init_image(data, &data->minimap, \
		width_square * data->map.width, width_square * data->map.height))
		quit(data, 1);
	init_cam(&data->map, &data->cam);
	init_render_vars(data);
	clean_map(data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "graph");
	if (!data->win)
		quit(data, 1);
	init_hook(data);
	return (TRUE);
}
