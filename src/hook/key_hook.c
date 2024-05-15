#include "struct.h"
#include "define.h"


int	key_press_hook(int key, t_data *data)
{
	if (key == KEY_FRWD)
		data->cam.move.x += MOVE_SPEED;
	if (key == KEY_BCKWRD)
		data->cam.move.x -= MOVE_SPEED;
	if (key == KEY_LEFT)
		data->cam.move.y -= MOVE_SPEED;
	if (key == KEY_RIGHT)
		data->cam.move.y += MOVE_SPEED;
	return (0);
}