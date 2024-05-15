#include "struct.h"
#include "define.h"

int	mouse_move_hook(int x, int y, t_data *data)
{
	data->cam.angle += (x - data->mouse.x) * ROTATE_SPEED;
	// data->cam.angle.y -= (y - data->mouse.y) * ROTATE_SPEED;
	data->mouse.x = x;
	// data->mouse.y = y;
	return (0);
}