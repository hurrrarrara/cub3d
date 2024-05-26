/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:59:29 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 03:35:27 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "mlx.h"
#include "struct_bonus.h"
#include "parsing_bonus.h"

void	clean_img(t_data *data)
{
	if (data->final_render.img)
		mlx_destroy_image(data->mlx, data->final_render.img);
	if (data->door_notif.img)
		mlx_destroy_image(data->mlx, data->door_notif.img);
	if (data->pause_screen.img)
		mlx_destroy_image(data->mlx, data->pause_screen.img);
	if (data->render_vars.textures[0].img)
		mlx_destroy_image(data->mlx, data->render_vars.textures[0].img);
	if (data->render_vars.textures[1].img)
		mlx_destroy_image(data->mlx, data->render_vars.textures[1].img);
	if (data->render_vars.textures[2].img)
		mlx_destroy_image(data->mlx, data->render_vars.textures[2].img);
	if (data->render_vars.textures[3].img)
		mlx_destroy_image(data->mlx, data->render_vars.textures[3].img);
	if (data->render_vars.textures[4].img)
		mlx_destroy_image(data->mlx, data->render_vars.textures[4].img);
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
}

void	free_data(t_data *data)
{
	if (data->mlx)
		clean_img(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_map(&data->map);
}

void	quit(t_data *data, const uint8_t code)
{
	free_data(data);
	exit(code);
}
