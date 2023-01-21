#include "draw.h"
#include "math_utils.h"

static t_discrim	intersect_sphere_discrim(const t_shape *shape, \
											const t_ray *ray);

bool	intersect_sphere(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_sphere	*sph;
	t_discrim		d;

	d = intersect_sphere_discrim(shape, ray);
	sph = &shape->u_data.sphere;
	if (d.t > 0)
	{
		if (out_intp)
		{
			out_intp->distance = d.t;
			out_intp->position = add_vec(ray->start, \
								constant_mul_vec(ray->direction, d.t));
			out_intp->normal = diff_vec(out_intp->position, sph->center);
			out_intp->normal = norm_vec(out_intp->normal);
		}
		return (true);
	}
	else
		return (false);
}

static t_discrim	intersect_sphere_discrim(const t_shape *shape, \
											const t_ray *ray)
{
	const t_sphere	*sph;
	t_vec			pe_pc;
	t_discrim		d;

	sph = &shape->u_data.sphere;
	pe_pc = diff_vec(ray->start, sph->center);
	d.a = inner_product(ray->direction, ray->direction);
	d.b = 2 * inner_product(ray->direction, pe_pc);
	d.c = inner_product(pe_pc, pe_pc) - sph->radius * sph->radius;
	d.d = d.b * d.b - 4 * d.a * d.c;
	process_discrim(&d);
	return (d);
}
