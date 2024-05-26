/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:59:02 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/24 17:13:36 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "mlx.h"

void	draw_pause(t_data *data)
{
	const uint16_t	y_offset = data->final_render.height / 2;
	const uint16_t	x_offset = \
		(data->final_render.width / 2) - (data->pause_screen.width / 2);
	uint32_t		color;
	int32_t			i;

	i = 0;
	while (i < data->pause_screen.height * data->pause_screen.width)
	{
		color = ((uint32_t *)data->pause_screen.addr)[i];
		if (color << 8)
			((uint32_t *)data->final_render.addr)[x_offset + (i % \
			data->pause_screen.width) + (y_offset + (i / \
			data->pause_screen.width)) * data->final_render.width] = color;
		i++;
	}
}

void	active_pause(t_data *data)
{
	if (data->pause_toggle > 1)
		return ;
	mlx_mouse_show(data->mlx, data->win);
	draw_pause(data);
	data->pause_toggle++;
	mlx_put_image_to_window(data->mlx, data->win, data->final_render.img, 0, 0);
}
