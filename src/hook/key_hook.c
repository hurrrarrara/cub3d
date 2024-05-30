/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:59:13 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/30 15:04:40 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "define.h"
#include "quit.h"
#include <X11/keysym.h>
#include "mlx.h"

int	key_release_hook(int key, t_data *data)
{
	if (key == KEY_FRWD)
		data->fw = FALSE;
	if (key == KEY_BCKWRD)
		data->bw = FALSE;
	if (key == KEY_LEFT)
		data->l = FALSE;
	if (key == KEY_RIGHT)
		data->r = FALSE;
	if (key == XK_Left)
		data->cam.rot_l = FALSE;
	if (key == XK_Right)
		data->cam.rot_r = FALSE;
	return (0);
}

int	key_press_hook(int key, t_data *data)
{
	if (key == KEY_FRWD)
		data->fw = TRUE;
	if (key == KEY_BCKWRD)
		data->bw = TRUE;
	if (key == KEY_LEFT)
		data->l = TRUE;
	if (key == KEY_RIGHT)
		data->r = TRUE;
	if (key == XK_Left)
		data->cam.rot_l = TRUE;
	if (key == XK_Right)
		data->cam.rot_r = TRUE;
	if (key == XK_Tab)
	{
		data->pause_toggle = (data->pause_toggle == 0);
		if (!data->pause_toggle)
			mlx_mouse_hide(data->mlx, data->win);
		else
			mlx_mouse_show(data->mlx, data->win);
	}
	if (key == XK_Escape)
		quit(data, 0);
	return (0);
}
