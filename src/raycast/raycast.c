#include "raycast.h"
#include "define.h"
#include "struct.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "math_utils.h"


t_ray	set_ray(const t_camera cam, uint16_t nb_ray)
{
	const float		hypo = 1 * cosf(cam.fov * M_PI * 0.5 / 180.0);
	const t_vec2	end = (t_vec2){
		cos(cam.angle + (cam.fov * M_PI * 0.5 / 180.0)) * hypo,
		sin(cam.angle + (cam.fov * M_PI * 0.5 / 180.0)) * hypo
	};
	t_ray			ray;

	ray.ray = (t_vec2){
		cos(cam.angle - (cam.fov * M_PI * 0.5 / 180.0)) * hypo,
		sin(cam.angle - (cam.fov * M_PI * 0.5 / 180.0)) * hypo
	};
	ray.add = (t_vec2){
		(end.x - ray.ray.x) * 1.0f / nb_ray,
		(end.y - ray.ray.y) * 1.0f / nb_ray,
	};
	ray.origin = (t_vec2){
		cam.world_pos.x,
		cam.world_pos.z
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

void	draw_line(uint16_t col, t_rendervars *render_vars, t_drawvars draw_vars, int a)
{
	const int16_t	height = render_vars->cube_height / draw_vars.dist;
	const int16_t	start = (render_vars->render_width - (render_vars->render_width / 2.0)) - (render_vars->render_width / 10) / draw_vars.dist;
	const int16_t	end = ft_i16min(start + height, render_vars->render_width - 1);
	const float		step = draw_vars.textures->height / (float)height;
	int16_t			wall_x;
	uint32_t		color;
	uint16_t		i = 0;
	uint32_t		*img;
	uint16_t		y = draw_vars.textures->height - 1;

	img = render_vars->render_map + col * render_vars->render_width;
	draw_vars.x -= floorf(draw_vars.x);
	wall_x = draw_vars.x * draw_vars.textures->width;
	if (a)
		wall_x = draw_vars.textures->width - wall_x - 1;
	while (i < render_vars->render_width)
	{
		if (i >= start && i < end)
		{
			color = ((uint32_t *)draw_vars.textures->addr)[wall_x + (int)(y -((i - start) * step)) * draw_vars.textures->width];
			color = color_x_angle((t_color){color}, draw_vars.angle);
		}
		img[i] = (i < start) * render_vars->floor.hex + (i >= start && i < end) * color;
		i++;
	}

}


t_ddavrs	set_dda_vars(t_ray ray)
{
	t_ddavrs	final;

	final.pos = (t_point2){
		.x = (int)ray.origin.x,
		.y = (int)ray.origin.y
	};
	final.delta = (t_vec2){
		(ray.ray.x != 0) * fabsf(1 / ray.ray.x),
		(ray.ray.y != 0) * fabsf(1 / ray.ray.y),
	};
	final.step = (t_i8point2){
		(ray.ray.x >= 0) - (ray.ray.x < 0),
		(ray.ray.y >= 0) - (ray.ray.y < 0)
	};
	final.dist = (t_vec2){
		(final.step.x * final.pos.x + (final.step.x == 1) - \
			final.step.x * ray.origin.x) * final.delta.x,
		(final.step.y * final.pos.y + (final.step.y == 1) - \
			final.step.y * ray.origin.y) * final.delta.y,
	};
	return (final);
}

void	dda(t_ray ray, t_map map, uint16_t col, t_rendervars *render_vars)
{
	

	t_ddavrs	dda_vars;
	t_drawvars	draw_vars;
	t_bool		side;

	dda_vars = set_dda_vars(ray);
	while (1)
	{
		side = (dda_vars.dist.x < dda_vars.dist.y);
		dda_vars.pos.x += side * dda_vars.step.x;
		dda_vars.pos.y += (!side) * dda_vars.step.y;
		if (map.map[dda_vars.pos.x + (dda_vars.pos.y * map.width)] >= 2)
		{
			draw_vars.angle = 1.2 - fabs(((side) * ray.ray.y + (!side) * ray.ray.x) *(1 / sqrtf((ray.ray.x * ray.ray.x) + (ray.ray.y * ray.ray.y))));
			draw_vars.textures = render_vars->textures + (side) * ((dda_vars.step.x == -1) * 2 + (dda_vars.step.x == 1) * 3) + (!side) * ((dda_vars.step.y == -1) * 1);
			draw_vars.dist = (side) * dda_vars.dist.x + (!side) * dda_vars.dist.y;
			draw_vars.x = (side) * (float)(ray.origin.y + draw_vars.dist * ray.ray.y) + (!side) * (float)(ray.origin.x + draw_vars.dist * ray.ray.x);
			draw_line(col, render_vars, draw_vars, (side) * (dda_vars.step.x == -1) + (!side) * (dda_vars.step.y == 1));
			break ;
		}
		dda_vars.dist = (t_vec2){
			dda_vars.dist.x + (dda_vars.dist.x < dda_vars.dist.y) * dda_vars.delta.x,
			dda_vars.dist.y + (dda_vars.dist.x >= dda_vars.dist.y) * dda_vars.delta.y
		};
	}
}

void	raycaster(const t_camera camera, t_map map, t_rendervars *render_vars)
{
	t_ray	ray;
	int16_t	i;

	ray = set_ray(camera, render_vars->render_height);
	i = -1;
	while (++i < render_vars->render_height)
	{
		dda(ray, map, i, render_vars);
		ray.ray = (t_vec2)
		{
			ray.ray.x + ray.add.x,
			ray.ray.y + ray.add.y,
		};
	}
}