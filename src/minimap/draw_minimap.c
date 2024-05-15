#include "define.h"
#include "struct.h"
#include <stdint.h>
#include <stdnoreturn.h>





void	draw_face_hori(t_img *img, uint16_t x, uint16_t y, uint16_t width, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < width)
		{
			((unsigned int *)img->addr)[(x * (width + 2)) + j + ((y  + i) * img->width)] = color;
			j++;
		}
		i++;
	}
}

void	draw_face_verti(t_img *img, int16_t x, int16_t y, uint16_t width, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < 2)
		{
			((unsigned int *)img->addr)[x + j + ((y * (width + 2) + i) * img->width)] = color;
			j++;
		}
		i++;
	}
}

void	draw_chunk(t_img *img, t_chunk chunk, const uint16_t width)
{
	const uint32_t	color = (chunk.type > 1) * (BLOCK_B | (chunk.type * BLOCK_R)) + (chunk.type == 1) * FLOOR + (chunk.type == 1 && chunk.face != 0) * TOP_COLOR;
	int16_t	i;

	i = 0;
	while (i < (width) * (width))
	{
		((unsigned int *)img->addr)[(chunk.x * (width + 2)) + (i % (width)) + ((chunk.y * (width + 2) +( i / (width))) * img->width)] = color;
		i++;
	}
	if (chunk.type <= 1)
		return ;
	if (chunk.face & NORTH)
		draw_face_hori(img, chunk.x, chunk.y * (width + 2), width, NORTH_COLOR);
	if (chunk.face & SOUTH)
		draw_face_hori(img, chunk.x, (chunk.y * (width + 2)) + width - 2, width, SOUTH_COLOR);
	if (chunk.face & WEST)
		draw_face_verti(img, chunk.x * (width +2), chunk.y, width, WEST_COLOR);
	if (chunk.face & EAST)
		draw_face_verti(img, chunk.x * (width + 2) + width, chunk.y, width, EAST_COLOR);

}


void	draw_cam(t_img *img, const t_vec3 pos, const uint16_t width)
{
	const int32_t i = (width * pos.x) + ((int)((width) * pos.z) * img->width);

	((unsigned int *)img->addr)[i] = 0xff0000;
	((unsigned int *)img->addr)[i + 1] = 0xff0000;
	((unsigned int *)img->addr)[i + 2] = 0xff0000;
	((unsigned int *)img->addr)[i + 3] = 0xff0000;
	((unsigned int *)img->addr)[i + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 1 + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 2 + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 3 +img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 1 + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 2 + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 3 +img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + img->width + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 1 + img->width + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 2 + img->width + img->width + img->width] = 0xff0000;
	((unsigned int *)img->addr)[i + 3 +img->width + img->width + img->width] = 0xff0000;
}

static __inline__ int	mini_min(int a, int b)
{
	return (a * (a <= b) + b * (a > b));
}

void	draw_minimap(t_data *data)
{
	const uint16_t	width_square = mini_min(data->minimap.height / data->map.height, data->minimap.width / data->map.width);
	int16_t	i;

	i = -1;
	while (++i < data->map.allocated)
	{
		draw_chunk(&data->minimap, data->map.map[i], width_square - 2);
	}
	draw_cam(&data->minimap, data->cam.world_pos, width_square);
}