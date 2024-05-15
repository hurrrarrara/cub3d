#include "raycast.h"
#include "struct.h"
#include "init.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "minimap.h"
#include "mlx.h"
#include "define.h"
#include "math_utils.h"


t_bool	set_minimap(t_data *data)
{
	const uint16_t	width_square = ft_i16min(MINIMAP_HEIGHT / data->map.height, MINIMAP_WIDTH / data->map.width);

	if (!init_image(data, &data->minimap, width_square * data->map.width, width_square * data->map.height))
		return (FALSE);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	if (!init_data(&data))
		return (1);
	if (!parser(&data.map, av[1]))
		return (1);
	// if (!init_image(&data, &data.minimap, MINIMAP_WIDTH / data.map.width, MINIMAP_HEIGHT / data.map.height))
	// 	return (FALSE);
	if (!set_minimap(&data))
		return (1);
	printf("parsing done: %i | %i\n", data.map.width, data.map.height);
	mlx_mouse_hide(data.mlx, data.win);
	for (int i = 0; i < data.map.width * data.map.height; i++)
	{
		if (i && i % data.map.width == 0)
			printf("\n");
		int a = data.map.map[i];
		printf("%i",a);
		// printf("%i|%i:%i  ", data.map.map[i].x, data.map.map[i].y, a);
	}
	raycaster(data.cam, data.map, &data.render_vars);
	// return (0);
	mlx_loop(data.mlx);
	return (0);
}