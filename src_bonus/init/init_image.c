#include "define.h"
#include "libft.h"
#include "src/basics/basics.h"
#include "struct.h"
#include "mlx.h"
#include <stdio.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>

static void	print_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	perror(msg);
}

t_bool	init_image(\
	const t_data *data, \
	t_img *img, \
	const uint32_t width, \
	const uint32_t height)
{
	img->img = mlx_new_image(data->mlx, width, height);
	if (!img->img)
		return (print_error("mlx"), FALSE);
	img->addr = mlx_get_data_addr(\
		img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		return (print_error("mlx"), FALSE);
	img->width = width;
	img->height = height;
	return (TRUE);
}

t_bool	reverse_img(t_img *img)
{
	size_t		i;
	uint32_t	*tempo;

	i = 0;
	tempo = ft_calloc(img->width * img->height, sizeof(uint32_t));
	if (!tempo)
		return (FALSE);
	while (i < (size_t)(img->width * img->height))
	{
		// tempo[i] = ((uint32_t *)img->addr)[(i / img->width) + ((img->height - 1 - (i % img->height))) * img->width];
		tempo[(img->height - 1 - (i / img->width) ) + (i % img->width) * img->height] = ((uint32_t *)img->addr)[i];
		i++;
	}
	while (i-- > 0)
	{
		((uint32_t *)img->addr)[i] = tempo[i];
	}
	free(tempo);
	return (TRUE);
}

t_bool	xpm_to_image(t_data *data, t_img *texture, const char *texture_path)
{
	const int	fd = open(texture_path, O_RDONLY);

	if (fd < 0)
		return (print_error(texture_path), FALSE);
	close(fd);
	ft_bzero(texture, sizeof(t_img));
	texture->img = mlx_xpm_file_to_image(\
		data->mlx, (char *)texture_path, &texture->width, &texture->height);
	if (!texture->img)
		return (print_error("mlx"), FALSE);
	texture->addr = mlx_get_data_addr(\
		texture->img, \
		&texture->bits_per_pixel, \
		&texture->line_length, \
		&texture->endian);
	if (!texture->addr)
		return (print_error("mlx"), FALSE);
	return (TRUE);
}
