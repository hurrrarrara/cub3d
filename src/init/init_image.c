#include "struct.h"
#include "mlx.h"

t_bool	init_image(const t_data *data, t_img *img, const uint32_t width, const uint32_t height)
{
	img->img = mlx_new_image(data->mlx, width, height);
	if (!img->img)
		return (FALSE);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		return (FALSE);
	img->width = width;
	img->height = height;
	return (TRUE);
}