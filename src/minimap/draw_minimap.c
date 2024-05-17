#include "define.h"
#include "math_utils.h"
#include "struct.h"
#include <stdint.h>
#include <stdnoreturn.h>

void	draw_chunk(t_img *img, t_point2 pos, uint8_t type, const uint16_t width)
{
	const uint32_t	color = (type == 1) * FLOOR_COLOR + \
		(type == 2) * WALL_COLOR + (type == 3) * DOOR_CLOSE_COLOR + \
		(type == 4) * DOOR_OPEN_COLOR;
	int16_t			i;

	i = 0;
	while (i < (width) * (width))
	{
		((unsigned int *)img->addr)[(pos.x * (width + 2)) + (i % (width)) + \
			((pos.y * (width + 2) + (i / (width))) * img->width)] = color;
		i++;
	}
	if (type <= 1)
		return ;
}

void	draw_cam(t_img *img, const t_vec3 pos, const uint16_t width)
{
	const int32_t	i = (width * pos.x) + (img->width * (int)(width * pos.z));

	((unsigned int *)img->addr)[i] = 0xff0000;
	((unsigned int *)img->addr)[i + 1] = 0xff0000;
	((unsigned int *)img->addr)[i + 2] = 0xff0000;
	((unsigned int *)img->addr)[i + 3] = 0xff0000;
	((unsigned int *)img->addr)[i + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 1 + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 2 + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 3 + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 1 + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 2 + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 3 + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr) \
		[i + img->width + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr) \
		[i + 1 + img->width + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr) \
		[i + 2 + img->width + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr) \
		[i + 3 + img->width + img->width + img->width] = 0xff0000;
}

void	draw_minimap(t_data *data)
{
	const uint16_t	width_square = \
		ft_i16min(data->minimap.height / data->map.height, \
		data->minimap.width / data->map.width);
	int16_t			i;

	i = -1;
	while (++i < data->map.allocated)
	{
		draw_chunk(&data->minimap, (t_point2){\
			.x = i % data->map.width, \
			.y = i / data->map.width}, \
			data->map.map[i], width_square - 2);
	}
	draw_cam(&data->minimap, data->cam.world_pos, width_square);
}
