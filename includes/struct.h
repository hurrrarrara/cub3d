#ifndef STRUCT_H
# define STRUCT_H

# include <stdint.h>
# include "libft.h"

typedef union u_color
{
	uint32_t	hex;
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	a;
	};
	struct
	{
		int16_t	x;
		int16_t	y;
	};
}	t_color;

typedef t_color	t_point2;

typedef struct s_i8point2
{
	int8_t	x;
	int8_t	y;
}	t_i8point2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int32_t	bits_per_pixel;
	int32_t	line_length;
	int32_t	width;
	int32_t	height;
	int32_t	endian;
}	t_img;

typedef struct s_camera
{
	t_vec3	world_pos;
	t_vec2	move;
	float	angle;
	float	fov;
}	t_camera;

typedef struct s_map
{
	uint8_t		*map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
	uint16_t	width;
	uint16_t	height;
	uint16_t	allocated;
	size_t	size[2];
}	t_map;

typedef struct s_mouse
{
	int16_t	x;
	int16_t	y;
}	t_mouse;

typedef struct s_rendervars
{
	uint32_t	*render_map;
	t_color		floor;
	t_color		ceiling;
	t_img		textures[5];
	uint16_t	anim_offset;
	uint16_t	width;
}	t_rendervars;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_img			minimap;
	t_camera		cam;
	t_mouse			mouse;
	t_rendervars	render_vars;
	t_img			final_render;
	t_img			door_notif;
	t_img			pause_screen;
	uint8_t			pause_toggle;
}	t_data;

#endif