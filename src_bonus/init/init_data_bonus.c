/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:58:58 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/28 15:10:33 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include "mlx.h"
#include "libft.h"
#include "struct_bonus.h"
#include "define_bonus.h"
#include "init_bonus.h"
#include "quit_bonus.h"
#include "math_utils_bonus.h"

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
	if (!xpm_to_image(data, data->render_vars.textures, data->map.no) \
		|| !reverse_img(data->render_vars.textures))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 1, data->map.so) \
		|| !reverse_img(data->render_vars.textures + 1))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 2, data->map.ea) \
		|| !reverse_img(data->render_vars.textures + 2))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 3, data->map.we) \
		|| !reverse_img(data->render_vars.textures + 3))
		quit(data, 1);
	if (!xpm_to_image(data, data->render_vars.textures + 4, DOOR_TEXT) \
		|| !reverse_img(data->render_vars.textures + 4))
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
	data->fw = FALSE;
	data->bw = FALSE;
	data->l = FALSE;
	data->r = FALSE;
	data->cam.rot_l = FALSE;
	data->cam.rot_r = FALSE;
	data->mlx = mlx_init();
	if (!data->mlx)
		quit(data, 1);
	if (!init_image(data, &data->final_render, WIN_WIDTH, WIN_HEIGHT))
		quit(data, 1);
	if (!init_image(data, &data->minimap, \
		MINIMAP_WIDTH, MINIMAP_HEIGHT))
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
