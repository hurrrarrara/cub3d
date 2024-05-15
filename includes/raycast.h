#ifndef RAYCAST_H
# define RAYCAST_H

# include "struct.h"
# include <stdint.h>

typedef struct
{
	t_vec2	add;
	t_vec2	ray;
	t_vec2	origin;
	// int8_t	height;
	float	angle;
}t_ray;

typedef struct s_drawvars
{
	float		dist;
	float		angle;
	float		x;
	t_img		*textures;
}t_drawvars;

void	raycaster(const t_camera *camera, t_map map, t_img *img, t_img *textures);

#endif