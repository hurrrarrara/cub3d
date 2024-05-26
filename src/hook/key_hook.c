/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:59:13 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 00:17:15 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "define.h"
#include "quit.h"

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
	if (key == 65289)
		data->pause_toggle = (data->pause_toggle == 0);
	if (key == 65307)
		quit(data, 0);
	return (0);
}
