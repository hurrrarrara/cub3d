#include "struct.h"
#include "mlx.h"
#include <strings.h>

t_bool	init_image(\
	const t_data *data, \
	t_img *img, \
	const uint32_t width, \
	const uint32_t height)
{
	img->img = mlx_new_image(data->mlx, width, height);
	if (!img->img)
		return (FALSE);
	img->addr = mlx_get_data_addr(\
		img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		return (FALSE);
	img->width = width;
	img->height = height;
	return (TRUE);
}

t_img	xpm_to_image(t_data *data, const char *texture_path)
{
	t_img	texture;

	bzero(&texture, sizeof(texture));
	texture.img = mlx_xpm_file_to_image(\
		data->mlx, (char *)texture_path, &texture.width, &texture.height);
	if (!texture.img)
		return (texture);
	texture.addr = mlx_get_data_addr(\
		texture.img, \
		&texture.bits_per_pixel, \
		&texture.line_length, \
		&texture.endian);
	if (!texture.addr)
		return (texture);
	return (texture);
}
