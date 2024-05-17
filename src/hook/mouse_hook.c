#include "struct.h"
#include "define.h"

int	mouse_move_hook(int x, int y, t_data *data)
{
	(void)y;
	data->cam.angle += (x - data->mouse.x) * ROTATE_SPEED;
	data->mouse.x = x;
	return (0);
}

int	mouse_button_hook(int button, int x, int y, t_data *data)
{
	(void)y;
	(void)x;
	if (button == 4 && data->cam.fov >= 51)
		data->cam.fov -= 5;
	if (button == 5 && data->cam.fov <= 160)
		data->cam.fov += 5;
	return (0);
}
