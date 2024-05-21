#include "raycast.h"
#include "src/basics/basics.h"
#include "struct.h"
#include "init.h"
#include "parser.h"
#include "mlx.h"
#include "define.h"
#include "math_utils.h"
#include "quit.h"
#include "parsing.h"
#include <stdio.h>

void	set_minimap(t_data *data)
{
	const uint16_t	width_square = ft_i16min(MINIMAP_HEIGHT / data->map.height, MINIMAP_WIDTH / data->map.width);

	if (!init_image(data, &data->minimap, width_square * data->map.width, width_square * data->map.height))
		quit(data, 1);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 2)
		return (1);
	if (parsing(&data.map, av))
		return (1);
	init_data(&data);
	data.map.width = data.map.size[0];
	data.map.height = data.map.size[1];
	data.map.allocated = data.map.width * data.map.height;
	printf("%lu\n",ft_strlen((char *)data.map.map));
	for (size_t i = 0; i < data.map.width * data.map.height; i++)
	{
		if (i && !(i % data.map.width))
			printf("\n");
		printf("%c",data.map.map[i]);
	}
	for (size_t i = 0; i < data.map.width * data.map.height; i++)
	{
		if (data.map.map[i] == 32)
			data.map.map[i] = 0;
		else
			data.map.map[i] -= '0' - 1;
	}
	printf("\n");
	set_minimap(&data);
	mlx_mouse_hide(data.mlx, data.win);
	raycaster(data.cam, data.map, data.render_vars);
	mlx_put_image_to_window(data.mlx, data.win, data.final_render.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}