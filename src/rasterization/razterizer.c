#include "define.h"
#include "struct.h"
#include <smmintrin.h>
#include <stdint.h>
#include <xmmintrin.h>
#include "immintrin.h"

typedef struct s_rendervars
{
	float	rotation[4];
	t_material	material;

	__m256	rotate_x;
	__m256	rotate_y;
	__m128	world_pos;
	__m128	project_coeff;
}t_rendervars;

typedef struct s_raster_vars
{
	__m128		weight;
	__m128		z_vals;
	__m128		w_vals;
	__m128		uv_x;
	__m128		uv_y;
	uint32_t	normal;
	t_img		albedo_map;
}t_raster_vars;


typedef struct s_barycentric_vars
{
	__m128	weight;
	__m128	add_x;
	__m128	add_y;
}t_barycentric_vars;

void	put_to_gbuffer(t_gbuffer *gbuffer, t_raster_vars raster_vars, uint32_t i)
{
	__m128	z_;
	__m128	u;
	__m128	v;
	float	z;

	z_ = _mm_mul_ps(raster_vars.weight, raster_vars.z_vals);
	z = z_[0] + z_[1] + z_[2];
	if (z > gbuffer->zbuffer[i])
		return ;
	z_ = _mm_mul_ps(raster_vars.weight, raster_vars.w_vals);
	z = 1.0f / (z_[0] + z_[1] + z_[2]);
	u = _mm_mul_ps(raster_vars.weight, raster_vars.uv_x);
	v = _mm_mul_ps(raster_vars.weight, raster_vars.uv_y);
	((uint32_t *)(gbuffer->albedo.addr))[i] = ((uint32_t *)raster_vars.albedo_map.addr)[(int)(v[0] + v[1] + v[2] * z) * raster_vars.albedo_map.width + (int)(u[0] + u[1] + u[2] * z)];
	((uint32_t *)gbuffer->normal.addr)[i] = raster_vars.normal;
}

/*
	CAN CHANGE raster_vars.weight  into __m256 to work on 2 pixels at same time
		->need to change barycentric_vars to use __m256 as well
		->addx need to be time 2
		->mask check condition need to be put in variable and two condition using bitshift to check independantly x and x+1
*/

void	rasterization(t_gbuffer *gbuffer, t_raster_vars raster_vars, t_barycentric_vars barycentric_vars, t_ivec4 bounding_box)
{
	uint32_t		x;
	uint32_t		y;
	const __m128	zero = _mm_set1_ps(0);

	y = bounding_box.z - 1;
	while (y <= bounding_box.w)
	{
		x = bounding_box.x - 1;
		raster_vars.weight = barycentric_vars.weight;
		while (++x <= bounding_box.y)
		{
			if (_mm_movemask_ps(_mm_cmp_ps(raster_vars.weight, zero, _MM_CMPINT_GT)) == 7)
				put_to_gbuffer(gbuffer, raster_vars, y * RENDER_WIDTH + x);
			raster_vars.weight = _mm_add_ps(raster_vars.weight, barycentric_vars.add_x);
		}
		barycentric_vars.weight = _mm_add_ps(barycentric_vars.weight, barycentric_vars.add_y);
	}
}


__m128	vec3_to_m128(t_vec3 v)
{
	return (__extension__ (__m128){ v.x, v.y, v.z, 1});
}

__m128	to_raster_space(__m128 v, __m128 project_coeff)
{
	const float		w = -1 / v[2];
	const __m128	add_one = __extension__ (__m128){1, -1, 1, 0};
	const __m128	div_2 = __extension__ (__m128){0.5 * RENDER_WIDTH, -0.5 * RENDER_HEIGHT, 0.5, 1};
	const __m128	div_w = __extension__ (__m128){w, w, w, w};

	v = _mm_mul_ps(v, project_coeff);
	v = _mm_add_ps(v, add_one);
	v = _mm_mul_ps(v, div_2);
	v = _mm_mul_ps(v, div_w);
	return (v);
}

t_ivec4	get_bounding_box(__m128 a, __m128 b, __m128 c)
{
	t_ivec4	bound;
	__m128	min;
	__m128	max;

	min = _mm_max_ps(_mm_min_ps(_mm_min_ps(a, b), c),__extension__ (__m128){0,0,0,0});
	max = _mm_min_ps(_mm_max_ps(_mm_max_ps(a, b), c),__extension__ (__m128){RENDER_WIDTH,RENDER_HEIGHT,0,0});
	bound.x = min[0];
	bound.y = max[0];
	bound.z = min[1];
	bound.w = max[1];
	return (bound);
}

t_raster_vars	set_raster_vars(t_face face, __m128 a, __m128 b, __m128 c)
{
	t_raster_vars	final;

	final.z_vals = __extension__ (__m128){a[2],b[2],c[2],0};
	final.w_vals = __extension__ (__m128){a[3],b[3],c[3],0};
	final.uv_x = __extension__ (__m128){face.vertices[0].uv.x,face.vertices[1].uv.x,face.vertices[2].uv.x,0};
	final.uv_x = __extension__ (__m128){face.vertices[0].uv.y,face.vertices[1].uv.y,face.vertices[2].uv.y,0};
	final.normal = face.normal.hex;
	return	(final);
}

t_barycentric_vars	set_barycentric_vars(__m128 a, __m128 b, __m128 c, t_ivec4 bounding_box)
{
	t_barycentric_vars	final;
	__m128	tempoa;
	__m128	tempob;
	__m128	tempoc;
	__m128	tempod;

	final.add_x = __extension__ (__m128){b[1] - c[1], c[1] - a[1], a[1] - b[1], 0};
	final.add_x = __extension__ (__m128){c[0] - b[0], a[0] - c[0], b[0] - a[0], 0};
	final.weight = _mm_add_ps(_mm_add_ps(final.add_x, _mm_set1_ps(bounding_box.x + 0.5)), \
					_mm_add_ps(final.add_y, _mm_set1_ps(bounding_box.z + 0.5)));
	tempoa = __extension__ (__m128){b[0], c[0], a[0], 0};
	tempob = __extension__ (__m128){c[1], a[1], b[1], 0};
	tempoc = __extension__ (__m128){b[1], c[1], a[1], 0};
	tempod = __extension__ (__m128){c[0], a[0], b[0], 0};
	final.weight = _mm_add_ps(final.weight, _mm_sub_ps(_mm_mul_ps(tempoa, tempob), _mm_mul_ps(tempoc, tempod)));
	tempoa = _mm_set1_ps(1.0f / (((b[0] - a[0]) * (c[1]- a[1])) - ((b[1] * a[1]) * (c[0] - a[0]))));
	final.add_x = _mm_mul_ps(final.add_x, tempoa);
	final.add_y = _mm_mul_ps(final.add_y, tempoa);
	final.weight = _mm_mul_ps(final.weight, tempoa);
	final.add_x[3] = 0;
	final.add_y[3] = 0;
	final.weight[3] = 0;
	return (final);
}

void	render_face(t_face face, t_gbuffer *gbuffer, t_rendervars rendervars)
{
	__m128		a;
	__m128		b;
	__m128		c;
	t_ivec4		bounding_box;
	t_raster_vars	raster_vars;
	t_barycentric_vars	barycentric_vars;

	a = vec3_to_m128(face.vertices[0].pos);
	b = vec3_to_m128(face.vertices[1].pos);
	c = vec3_to_m128(face.vertices[2].pos);
	a = _mm_add_ps(a, rendervars.world_pos);
	b = _mm_add_ps(b, rendervars.world_pos);
	c = _mm_add_ps(c, rendervars.world_pos);
	/*
	ROTATE
	*/
	if (a[2] > -CAM_NEAR || b[2] > -CAM_NEAR || c[2] > -CAM_NEAR)
		return ;
	a = to_raster_space(a, rendervars.project_coeff);
	b = to_raster_space(b, rendervars.project_coeff);
	c = to_raster_space(c, rendervars.project_coeff);
	bounding_box = get_bounding_box(a, b, c);
	if (bounding_box.x >= RENDER_WIDTH || bounding_box.y < 0 || bounding_box.z >= RENDER_HEIGHT || bounding_box.w < 0)
		return ;
	raster_vars = set_raster_vars(face, a, b, c);
	barycentric_vars = set_barycentric_vars(a, b, c, bounding_box);
	raster_vars.albedo_map = rendervars.material.albedo_map;
	rasterization(gbuffer, raster_vars, barycentric_vars, bounding_box);
}

void	render_obj(t_gbuffer *gbuffer, t_rendervars rendervars, t_mesh *mesh, uint8_t obj_nb)
{
	uint8_t	i;
	t_obj	obj;

	i = -1;
	obj = mesh->objects[obj_nb];
	while (++i < obj.faces_count)
	{
		rendervars.material = mesh->materials[obj.faces[i].material];
		render_face(obj.faces[i], gbuffer, rendervars);
	}
}

void	render_map(t_map map, t_gbuffer *gbuffer, t_rendervars rendervars, t_mesh *mesh)
{
	uint16_t	i;

	i = -1;
	while (++i < map.allocated)
	{
		if (!map.map[i].face)
			continue ;
		if (map.map[i].face & NORTH)
			render_obj(gbuffer, rendervars, mesh, NORTH | map.map[i].type << 5); //NOT SURE IN THE BITSHIFT ON WHAT
	}
}