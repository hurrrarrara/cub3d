/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:59:13 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/27 08:24:01 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "struct_bonus.h"
#include "define_bonus.h"
#include "quit_bonus.h"
#include <X11/keysym.h>

void	toogle_door(t_data *data)
{
	const uint16_t	x = (int)(data->cam.world_pos.x);
	const uint16_t	y = (int)(data->cam.world_pos.z);

	if (data->map.map[x + 1 + y * data->map.width] == 3)
		data->map.map[x + 1 + y * data->map.width] = 4;
	else if (data->map.map[x + 1 + y * data->map.width] == 4)
		data->map.map[x + 1 + y * data->map.width] = 3;
	if (data->map.map[x - 1 + y * data->map.width] == 3)
		data->map.map[x - 1 + y * data->map.width] = 4;
	else if (data->map.map[x - 1 + y * data->map.width] == 4)
		data->map.map[x - 1 + y * data->map.width] = 3;
	if (data->map.map[x + (y + 1) * data->map.width] == 3)
		data->map.map[x + (y + 1) * data->map.width] = 4;
	else if (data->map.map[x + (y + 1) * data->map.width] == 4)
		data->map.map[x + (y + 1) * data->map.width] = 3;
	if (data->map.map[x + (y - 1) * data->map.width] == 3)
		data->map.map[x + (y - 1) * data->map.width] = 4;
	else if (data->map.map[x + (y - 1) * data->map.width] == 4)
		data->map.map[x + (y - 1) * data->map.width] = 3;
}

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
	if (key == 'f')
		toogle_door(data);
	if (key == XK_Left)
		data->cam.angle -= ROTATE_SPEED * 10;
	if (key == XK_Right)
		data->cam.angle += ROTATE_SPEED * 10;
	if (key == XK_Tab)
		data->pause_toggle = (data->pause_toggle == 0);
	if (key == XK_Escape)
		quit(data, 0);
	return (0);
}
