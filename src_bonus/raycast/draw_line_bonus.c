/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:58:37 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 03:37:24 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include "define_bonus.h"
#include "struct_bonus.h"
#include "raycast_bonus.h"
#include "math_utils_bonus.h"

static __inline__ uint32_t	color_x_angle(t_color color, float angle)
{
	return ((t_color){
		.a = color.a * angle,
		.r = color.r * angle,
		.g = color.g * angle,
		.b = color.b * angle
	}.hex);
}

static __inline__ \
	t_drawlinevars	set_vars(const t_drawvars draw_vars, float y_off)
{
	t_drawlinevars	final;

	final.height = CUB_HEIGHT / draw_vars.dist;
	final.start = ((WIN_HEIGHT / powf(2, y_off))) - \
		(WIN_HEIGHT / 1) / draw_vars.dist;
	final.end = ft_i32min(final.start + final.height, WIN_HEIGHT);
	final.step = draw_vars.textures.height / (float)final.height;
	(void)y_off;
	return (final);
}

void	draw_line(uint16_t col, t_rendervars render_vars, t_drawvars draw_vars)
{
	const t_drawlinevars	vars = set_vars(draw_vars, render_vars.y_off);
	const uint32_t			*text = \
		((uint32_t *)draw_vars.textures.addr) + draw_vars.x;
	uint32_t				color;
	uint16_t				i;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		if (i >= vars.start && i < vars.end)
		{
			color = text[(int)((i - vars.start) * vars.step)];
			color = color_x_angle((t_color){color}, draw_vars.angle);
		}
		render_vars.render_map \
			[col + (WIN_HEIGHT - 1 - i) * WIN_WIDTH] = \
			(i < vars.start) * render_vars.floor.hex + \
			(i >= vars.start && i < vars.end) * color + \
			(i >= vars.end) * render_vars.ceiling.hex;
		i++;
	}
}
