/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 03:41:50 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 03:41:51 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "struct.h"
# include <stdint.h>

typedef struct s_ray
{
	t_vec2	add;
	t_vec2	ray;
	t_vec2	origin;
	float	angle;
}	t_ray;

typedef struct s_drawvars
{
	float		dist;
	float		angle;
	int32_t		x;
	t_img		textures;
}	t_drawvars;

typedef struct s_ddavars
{
	t_vec2		dist;
	t_vec2		delta;
	t_i8point2	step;
	t_point2	pos;
}	t_ddavrs;

typedef struct s_drawlinevars
{
	int32_t	height;
	int32_t	start;
	int32_t	end;
	float	step;
}	t_drawlinevars;

void	raycaster(const t_camera camera, t_map map, t_rendervars render_vars);
void	dda(t_ray ray, t_map map, uint16_t col, t_rendervars render_vars);
void	draw_line(uint16_t col, t_rendervars render_vars, t_drawvars draw_vars);

#endif