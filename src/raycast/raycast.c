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

void	raycaster(const t_camera camera, t_map map, t_rendervars render_vars)
{
	t_ray	ray;
	int16_t	i;

	ray = set_ray(camera, WIN_WIDTH);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		dda(ray, map, i, render_vars);
		ray.ray = (t_vec2)
		{
			ray.ray.x + ray.add.x,
			ray.ray.y + ray.add.y,
		};
	}
}