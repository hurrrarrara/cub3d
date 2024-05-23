#include "struct.h"
#include "define.h"
#include <stdint.h>
#include "quit.h"

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
	if (key == 65289)
		data->pause_toggle = (data->pause_toggle == 0);
	if (key == 65307)
		quit(data, 0);
	return (0);
}
