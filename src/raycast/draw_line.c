#include <stdint.h>
#include "struct.h"
#include <define.h>
#include "raycast.h"
#include "math_utils.h"


static __inline__ uint32_t	color_x_angle(t_color color, float angle)
{
	return ((t_color){
		.a = color.a * angle,
		.r = color.r * angle,
		.g = color.g * angle,
		.b = color.b * angle
	}.hex);
}

static __inline__ t_drawlinevars	set_drawline_vars(const t_drawvars draw_vars)
{
	t_drawlinevars	final;

	final.height = CUB_HEIGHT / draw_vars.dist;;
	final.start = (WIN_HEIGHT - (WIN_HEIGHT / 2.0)) - (WIN_HEIGHT / 2) / draw_vars.dist;
	final.end = ft_i32min(final.start + final.height, WIN_HEIGHT - 1);
	final.step = draw_vars.textures.height / (float)final.height;
	return (final);
}

void	draw_line(uint16_t col, t_rendervars render_vars, t_drawvars draw_vars)
{
	const t_drawlinevars	vars = set_drawline_vars(draw_vars);
	const uint16_t			y = draw_vars.textures.height - 1;
	uint32_t				color;
	uint16_t				i;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		if (i >= vars.start && i < vars.end)
		{
			color = ((uint32_t *)draw_vars.textures.addr)\
				[draw_vars.x + (int)(y -((i - vars.start) * vars.step)) * draw_vars.textures.width];
			color = color_x_angle((t_color){color}, draw_vars.angle);
		}
		render_vars.render_map\
			[col + (WIN_HEIGHT - 1 - i) * WIN_WIDTH] = \
			(i < vars.start) * render_vars.floor.hex + (i >= vars.start && i < vars.end) * color + (i >= vars.end) * render_vars.ceiling.hex;
		i++;
	}
}
