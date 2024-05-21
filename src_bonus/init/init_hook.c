#include "mlx.h"
#include "hook.h"
#include "quit.h"

int	xclose(t_data *data)
{
	quit(data, 0);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move_hook, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_button_hook, data);
	mlx_loop_hook(data->mlx, no_event, data);
	mlx_hook(data->win, 17, 1L << 17, xclose, data);
}
