/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:58:54 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/30 15:04:31 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "hook.h"
#include "quit.h"
#include "struct.h"

int	xclose(t_data *data)
{
	quit(data, 0);
	return (0);
}

int	loose_focus(t_data *data)
{
	if (data->pause_toggle)
		mlx_mouse_show(data->mlx, data->win);
	data->pause_toggle = 1;
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_hook, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move_hook, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_button_hook, data);
	mlx_hook(data->win, 17, 1L << 17, xclose, data);
	mlx_hook(data->win, 10, 1L << 21, loose_focus, data);
	mlx_loop_hook(data->mlx, no_event, data);
}
