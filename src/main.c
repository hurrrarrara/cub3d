#include "raycast.h"
#include "struct.h"
#include "init.h"
#include "parser.h"
#include "mlx.h"
#include "define.h"
#include "math_utils.h"
#include "quit.h"

void	set_minimap(t_data *data)
{
	const uint16_t	width_square = ft_i16min(MINIMAP_HEIGHT / data->map.height, MINIMAP_WIDTH / data->map.width);

	if (!init_image(data, &data->minimap, width_square * data->map.width, width_square * data->map.height))
		quit(data, 1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	init_data(&data);
	if (!parser(&data.map, av[1]))
		return (1);
	set_minimap(&data);
	mlx_mouse_hide(data.mlx, data.win);
	raycaster(data.cam, data.map, data.render_vars);
	mlx_put_image_to_window(data.mlx, data.win, data.final_render.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}