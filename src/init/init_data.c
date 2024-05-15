#include "struct.h"
#include "define.h"
#include "mlx.h"
#include "init.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


void	init_cam(t_camera *camera)
{
	camera->world_pos = (t_vec3){
		3,
		0.1,
		3.5
	};
	camera->fov = 120;
}

t_img	xpm_to_image(t_data *data, const char *texture_path)
{
	t_img	texture;

	bzero(&texture, sizeof(texture));
	
	texture.img = mlx_xpm_file_to_image(data->mlx, (char *)texture_path, &texture.width, &texture.height);
	if (!texture.img)
		return (texture);

	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
	if (!texture.addr)
		return (texture);

	return (texture);
}
t_bool	init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (FALSE);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "graph");
	if (!data->win)
		return (FALSE);
	init_hook(data);
	if (!init_image(data, &data->final_render, WIN_WIDTH, WIN_HEIGHT))
		return (FALSE);
	init_cam(&data->cam);
	data->render_vars.render_map = calloc(RENDER_WIDTH * RENDER_HEIGHT, sizeof(uint32_t));
	data->render_vars.render_width = RENDER_WIDTH;
	data->render_vars.render_height = RENDER_HEIGHT;
	data->render_vars.cube_height = CUB_HEIGHT;
	data->render_vars.ceiling = (t_color){0xff0000};
	data->render_vars.floor = (t_color){FLOOR};
	data->render_vars.textures[0] = xpm_to_image(data, NORTH_TEXT);
	data->render_vars.textures[1] = xpm_to_image(data, SOUTH_TEXT);
	data->render_vars.textures[2] = xpm_to_image(data, EAST_TEXT);
	data->render_vars.textures[3] = xpm_to_image(data, WEST_TEXT);
	return (TRUE);
}