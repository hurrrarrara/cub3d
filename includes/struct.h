#ifndef STRUCT_H
#define STRUCT_H

#include <stdint.h>

typedef enum
{
	FALSE,
	TRUE
}t_bool;

typedef union
{
	uint32_t	hex;
	struct
	{
		uint8_t	a;
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
	};
	struct
	{
		int16_t	x;
		int16_t	y;
	};
}t_color;

typedef t_color t_point2;

typedef struct
{
	float	x;
	float	y;
	float	z;
	float	w;
}t_vec4;

typedef struct
{
	float	x;
	float	y;
	float	z;
}t_vec3;

typedef struct
{
	float	x;
	float	y;
}t_vec2;

typedef struct
{
	int16_t	x;
	int16_t	y;
	int16_t	z;
	int16_t	w;
}t_ivec4;

typedef struct
{
	t_vec3		pos;
	t_point2	uv;
}t_vertex;

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

typedef struct s_face
{
	t_vertex	vertices[3];
	uint16_t	material;
	t_color		normal;
}t_face;

typedef struct
{
	t_face		*faces;
	uint16_t	faces_count;
}t_obj;

typedef struct	s_material
{
	t_img	ao_map;
	t_img	normal_map;
	t_img	albedo_map;
}t_material;

typedef struct 
{
	uint16_t	materials_count;
	uint16_t	objects_count;

	t_material	*materials;
	t_obj		*objects;
}t_mesh;

typedef struct s_camera
{
	t_vec3	world_pos;
	t_vec2	move;
	float	angle;
	float	fov;
}t_camera;

typedef struct s_chunk
{
	int16_t	x;
	int16_t	y;
	union
	{
		struct
		{
			uint8_t	face:5;
			uint8_t	type:3;
		};
		uint8_t	mask;
	};
}	t_chunk;


typedef struct
{
	t_chunk		*map;
	uint16_t	width;
	uint16_t	height;
	uint16_t	allocated;
}t_map;

typedef struct s_mouse
{
	int16_t	x;
	int16_t	y;
}t_mouse;

typedef struct s_gbuffer
{
	t_img	albedo;
	t_img	normal;
	float	*zbuffer;
}t_gbuffer;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		minimap;
	t_camera	cam;
	t_mouse		mouse;
	t_gbuffer	gbuffer;
	t_img		render;
	t_img		textures[4]; //0->NO, 1->SO, 2->EA, 3->WE
	t_color		floor;
	t_color		ceiling;
}t_data;

#endif