#ifndef INIT_H
# define INIT_H

# include "struct.h"

t_bool	init_data(t_data *data);
void	init_hook(t_data *data);

t_img	xpm_to_image(t_data *data, const char *texture_path);
t_bool	init_image(\
	const t_data *data, \
	t_img *img, \
	const uint32_t width, \
	const uint32_t height);

#endif