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

int	mouse_button_hook(int button, int x, int y, t_rendervars *render_vars)
{
	if (button == 4 && WIN_HEIGHT / render_vars->render_width != 8)
	{
		render_vars->render_height /= 2;
		render_vars->render_width /= 2;
		render_vars->cube_height /= 2;
	}
	if (button == 5 && WIN_HEIGHT / render_vars->render_width != 1)
	{
		render_vars->render_height *= 2;
		render_vars->render_width *= 2;
		render_vars->cube_height *= 2;
	}
	return (0);
}
