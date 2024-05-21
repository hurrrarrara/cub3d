#include "struct.h"
#include "define.h"
#include "mlx.h"
#include "init.h"
#include <stdint.h>
#include "quit.h"

void	init_cam(t_camera *camera)
{
	camera->world_pos = (t_vec3){
		5,
		0.1,
		10.5
	};
	camera->fov = 120;
}

void	init_render_vars(t_data *data)
{
	data->render_vars.render_map = (uint32_t *)data->final_render.addr;
	data->render_vars.width = 549;
	data->render_vars.ceiling = (t_color){0xfa00a0};
	data->render_vars.floor = (t_color){FLOOR};
	data->render_vars.textures[0] = xpm_to_image(data, NORTH_TEXT);
	data->render_vars.textures[1] = xpm_to_image(data, SOUTH_TEXT);
	data->render_vars.textures[2] = xpm_to_image(data, EAST_TEXT);
	data->render_vars.textures[3] = xpm_to_image(data, WEST_TEXT);
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
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init();
	if (!data->mlx)
		quit(data, 1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "graph");
	if (!data->win)
		quit(data, 1);
	init_hook(data);
	if (!init_image(data, &data->final_render, WIN_WIDTH, WIN_HEIGHT))
		quit(data, 1);
	init_cam(&data->cam);
	init_render_vars(data);
	return (TRUE);
}
