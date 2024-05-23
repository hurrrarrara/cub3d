#include "define.h"
#include "raycast.h"
#include <math.h>
#include <stdint.h>
#include "struct.h"

static __inline__ t_ddavrs	set_dda_vars(t_ray ray)
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

static __inline__ \
	t_drawvars	set_draw_vars(\
		t_ray ray, \
		t_ddavrs dda_vars, \
		t_rendervars render_vars, \
		t_point2 wall)
{
	t_drawvars		draw_vars;
	float			x;
	const uint8_t	text_nb = \
		(wall.x && wall.y != 3) * ((dda_vars.step.x == -1) * 2 + \
		(dda_vars.step.x == 1) * 3) + (!wall.x && wall.y != 3) * \
		((dda_vars.step.y == -1) * 1) + (wall.y == 3) * 4;

	draw_vars.angle = fminf(1, \
		1.1 - fabs(((wall.x) * ray.ray.y + (!wall.x) * ray.ray.x) * \
		(1 / sqrtf((ray.ray.x * ray.ray.x) + (ray.ray.y * ray.ray.y)))));
	draw_vars.textures = render_vars.textures[text_nb];
	draw_vars.dist = (wall.x) * dda_vars.dist.x + (!wall.x) * dda_vars.dist.y;
	x = (wall.x) * (float)(ray.origin.y + draw_vars.dist * ray.ray.y) + \
		(!wall.x) * (float)(ray.origin.x + draw_vars.dist * ray.ray.x);
	x -= floorf(x);
	if (text_nb == 4)
		draw_vars.x = x * ANIM_OFFSET;
	else
		draw_vars.x = x * draw_vars.textures.width;
	if ((wall.x) * (dda_vars.step.x == -1) + (!wall.x) * (dda_vars.step.y == 1))
		draw_vars.x = draw_vars.textures.width - draw_vars.x - 1;
	draw_vars.x += (text_nb == 4) * render_vars.anim_offset;
	return (draw_vars);
}

void	dda(t_ray ray, t_map map, uint16_t col, t_rendervars render_vars)
{
	t_drawvars	draw_vars;
	t_ddavrs	dda_v;
	t_point2	wall;

	dda_v = set_dda_vars(ray);
	while (1)
	{
		wall.x = (dda_v.dist.x < dda_v.dist.y);
		dda_v.pos.x += wall.x * dda_v.step.x;
		dda_v.pos.y += (!wall.x) * dda_v.step.y;
		wall.y = map.map[dda_v.pos.x + (dda_v.pos.y * map.width)] % 4;
		if (wall.y > 1)
		{
			draw_vars = set_draw_vars(ray, dda_v, render_vars, wall);
			draw_line(col, render_vars, draw_vars);
			break ;
		}
		dda_v.dist = (t_vec2){
			dda_v.dist.x + (dda_v.dist.x < dda_v.dist.y) * dda_v.delta.x,
			dda_v.dist.y + (dda_v.dist.x >= dda_v.dist.y) * dda_v.delta.y
		};
	}
}
