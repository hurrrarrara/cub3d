#include "raycast.h"
#include "define.h"
#include "struct.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

# define NBRAY 1920

static __inline__ int ft_max(int a, int b)
{
	return (a * (a >= b) + b * (a < b));
}

static inline int	ft_min(int a, int b)
{
	return (a * (a <= b) + b * (a > b));
}

t_ray	set_ray(const t_camera *cam)
{
	const float	hypo = 1 * cosf(cam->fov * M_PI * 0.5 / 180.0);
	t_vec2		end;
	t_ray		ray;

	ray.ray = (t_vec2){
		cos(cam->angle - (cam->fov * M_PI * 0.5 / 180.0)) * hypo,
		sin(cam->angle - (cam->fov * M_PI * 0.5 / 180.0)) * hypo
	};
	end = (t_vec2){
		cos(cam->angle + (cam->fov * M_PI * 0.5 / 180.0)) * hypo,
		sin(cam->angle + (cam->fov * M_PI * 0.5 / 180.0)) * hypo
	};
	ray.add = (t_vec2){
		(end.x - ray.ray.x) * 1.0f/NBRAY,
		(end.y - ray.ray.y) * 1.0f/NBRAY,
	};
	ray.origin = (t_vec2){
		cam->world_pos.x,
		cam->world_pos.z
	};
	return (ray);
}
uint32_t	color_x_angle(t_color color, float angle)
{
	return ((t_color){
		.a = color.a * angle,
		.r = color.r * angle,
		.g = color.g * angle,
		.b = color.b * angle
	}.hex);
}

void	draw_line(uint16_t col, t_img *img, t_drawvars draw_vars, int a)
{
	const int16_t	height = CUB_HEIGHT / draw_vars.dist;
	const int16_t	start = (WIN_HEIGHT - (WIN_HEIGHT / 2.0)) - (WIN_HEIGHT / 10) / draw_vars.dist;
	const int16_t	end = ft_min(start + height, WIN_HEIGHT - 1);
	const float		step = draw_vars.textures->height / (float)height;
	int16_t			wall_x;
	uint32_t		color;
	uint16_t		i = 0;
	uint16_t		y = draw_vars.textures->height - 1;

	// printf("%f\n", draw_vars.x);
	draw_vars.x -= floorf(draw_vars.x);
	wall_x = draw_vars.x * draw_vars.textures->width;
	if (a)
		wall_x = draw_vars.textures->width - wall_x - 1;
	while (i < WIN_HEIGHT)
	{
		if (i >= start && i < end)
		{
			color = ((uint32_t *)draw_vars.textures->addr)[wall_x + (int)(y -((i - start) * step)) * draw_vars.textures->width];
			color = color_x_angle((t_color){color}, draw_vars.angle);
		}
		((unsigned int *)img->addr)[col + ((WIN_HEIGHT - 1) - i) * img->width] = (i < start) * FLOOR + (i >= start && i < end) * color;
		i++;
	}

}


void	dda(t_ray ray, t_map map, uint16_t col, t_img *img, t_img *textures)
{
	t_vec2		side_dist;
	t_vec2		oldside;
	t_vec2		delta;
	int8_t		stepx;
	int8_t		stepy;
	t_point2	pos;
	float		dist;
	t_drawvars	draw_vars;

	pos.x = (int)ray.origin.x;
	pos.y = (int)ray.origin.y;
	delta = (t_vec2){
		(ray.ray.x != 0) * fabsf(1 / ray.ray.x),
		(ray.ray.y != 0) * fabsf(1 / ray.ray.y),
	};
	stepx = (ray.ray.x >= 0) - (ray.ray.x < 0);
	stepy = (ray.ray.y >= 0) - (ray.ray.y < 0);
	side_dist = (t_vec2){
		(stepx * pos.x + (stepx == 1) - stepx * ray.origin.x) * delta.x,
		(stepy * pos.y + (stepy == 1) - stepy * ray.origin.y) * delta.y,
	};
	while (1)
	{
		oldside = side_dist;
		pos.x += (side_dist.x < side_dist.y) * stepx;
		pos.y += (side_dist.x >= side_dist.y) * stepy;
		if (map.map[pos.x + (pos.y * map.width)].type >= 2)
		{
			draw_vars.angle = 1 - fabs(((side_dist.x < side_dist.y) * ray.ray.y + (side_dist.x >= side_dist.y) * ray.ray.x) *(1 / sqrtf((ray.ray.x * ray.ray.x) + (ray.ray.y * ray.ray.y))));
			draw_vars.textures = textures + (side_dist.x < side_dist.y) * ((stepx == -1) * 2 + (stepx == 1) * 3) + (side_dist.x >= side_dist.y) * ((stepy == -1) * 1);
			draw_vars.dist = (side_dist.x < side_dist.y) * side_dist.x + (side_dist.x >= side_dist.y) * side_dist.y;
			draw_vars.x = (side_dist.x < side_dist.y) * (float)(ray.origin.y + draw_vars.dist * ray.ray.y) + (side_dist.x >= side_dist.y) * (float)(ray.origin.x + draw_vars.dist * ray.ray.x);
			draw_line(col, img, draw_vars, (side_dist.x < side_dist.y) * (stepx == -1) + (side_dist.x >= side_dist.y) * (stepy == 1));
			break ;
		}
		side_dist = (t_vec2){
			side_dist.x + (oldside.x < oldside.y) * delta.x,
			oldside.y + (oldside.x >= oldside.y) * delta.y
		};
	}

}

#include <immintrin.h>

void	raycaster(const t_camera *camera, t_map map, t_img *img, t_img *textures)
{
	t_ray	ray;
	int16_t	i;

	ray = set_ray(camera);
	i = -1;
	while (++i < NBRAY)
	{
		dda(ray, map, i, img, textures);
		ray.ray = (t_vec2)
		{
			ray.ray.x + ray.add.x,
			ray.ray.y + ray.add.y,
		};
	}
}