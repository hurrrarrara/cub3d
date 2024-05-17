#include "struct.h"
#include "define.h"
#include <stdio.h>

int	mouse_move_hook(int x, int y, t_data *data)
{
	data->cam.angle += (x - data->mouse.x) * ROTATE_SPEED;
	// data->cam.angle.y -= (y - data->mouse.y) * ROTATE_SPEED;
	data->mouse.x = x;
	// data->mouse.y = y;
	return (0);
}

int	mouse_button_hook(int button, int x, int y, t_data *data)
{
	printf("%f\n", data->cam.fov);
	if (button == 4 && data->cam.fov >= 51)
		data->cam.fov -= 5;
	if (button == 5 && data->cam.fov <= 160)
		data->cam.fov += 5;
	return (0);
}
