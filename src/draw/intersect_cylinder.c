/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:23:52 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 11:23:53 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "rt_math.h"
#include <math.h>

static t_discrim	intersect_cylinder_discrim(const t_shape *shape, \
											const t_ray *ray);
static bool			intersect_cylinder_bottom(const t_shape *shape, \
								const t_ray *ray, t_intersect *out_intp);
void				set_out_intp(t_intersect *out_intp, const t_cylinder *cy, \
						const t_ray *ray, t_discrim d);

bool	intersect_cylinder(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_cylinder	*cy;
	t_discrim			d;

	d = intersect_cylinder_discrim(shape, ray);
	if (intersect_cylinder_bottom(shape, ray, out_intp))
	{
		if (d.t <= 0 || (d.t > 0 && out_intp->distance < d.t))
			return (true);
	}
	cy = &shape->u_data.cylinder;
	if (d.t > 0)
	{
		if (out_intp)
		{
			set_out_intp(out_intp, cy, ray, d);
		}
		return (true);
	}
	else
		return (false);
}

static t_discrim	intersect_cylinder_discrim(const t_shape *shape, \
											const t_ray *ray)
{
	const t_cylinder	*cy;
	t_vec				pe_pc;
	t_discrim			d;

	cy = &shape->u_data.cylinder;
	pe_pc = diff_vec(ray->start, cy->position);
	d.a = inner_product(ray->direction, ray->direction) \
			- pow(inner_product(cy->direction, ray->direction), 2);
	d.b = 2 * (inner_product(ray->direction, pe_pc) \
				- inner_product(ray->direction, cy->direction) \
				* inner_product(pe_pc, cy->direction));
	d.c = inner_product(pe_pc, pe_pc) \
			- pow(inner_product(pe_pc, cy->direction), 2) \
			- pow(cy->radius, 2);
	d.d = d.b * d.b - 4 * d.a * d.c;
	d.t = -1.0f;
	process_discrim(&d);
	d.m = inner_product(pe_pc, cy->direction) \
			+ d.t * inner_product(ray->direction, cy->direction);
	if (d.m < -cy->height / 2 || d.m > cy->height / 2)
		d.t = -1;
	return (d);
}

static bool	intersect_cylinder_bottom(const t_shape *shape, \
								const t_ray *ray, t_intersect *out_intp)
{
	const t_cylinder	*cy;
	t_shape				s;
	t_vec				plane_pos;
	bool				ret;
	t_intersect			intp;

	ret = false;
	cy = &shape->u_data.cylinder;
	s.u_data.plane.normal = constant_mul_vec(cy->direction, -1);
	/* same */
	plane_pos = add_vec(cy->position, \
				constant_mul_vec(cy->direction, -1 * cy->height / 2));
	s.u_data.plane.position = plane_pos;
	/*  */
	if (intersect_plane(&s, ray, &intp) && \
		abs_vec(diff_vec(intp.position, plane_pos)) <= cy->radius)
	{
		ret = true;
		*out_intp = intp;
	}
	s.u_data.plane.normal = cy->direction;
	/* same */
	plane_pos = add_vec(cy->position, \
				constant_mul_vec(cy->direction, cy->height / 2));
	s.u_data.plane.position = plane_pos;
	/*  */
	if (intersect_plane(&s, ray, &intp) && \
		abs_vec(diff_vec(intp.position, plane_pos)) <= cy->radius)
	{
		if (!ret || intp.distance < out_intp->distance)
		{
			ret = true;
			*out_intp = intp;
		}
	}
	return (ret);
}

bool

void	set_out_intp(t_intersect *out_intp, const t_cylinder *cy, \
						const t_ray *ray, t_discrim d)
{
	out_intp->distance = d.t;
	out_intp->position = add_vec(ray->start, \
								constant_mul_vec(ray->direction, d.t));
	out_intp->normal.x = 2 * cy->direction.z * (cy->direction.z \
					* (out_intp->position.x - cy->position.x) - cy->direction.x \
						* ((out_intp->position.z - cy->position.z))) \
						- 2 * cy->direction.y * (cy->direction.x \
					* (out_intp->position.y - cy->position.y) - cy->direction.y \
						* ((out_intp->position.x - cy->position.x)));
	out_intp->normal.y = 2 * cy->direction.x * (cy->direction.x \
					* (out_intp->position.y - cy->position.y) - cy->direction.y \
						* ((out_intp->position.x - cy->position.x))) \
						- 2 * cy->direction.z * (cy->direction.y \
					* (out_intp->position.z - cy->position.z) - cy->direction.z \
						* ((out_intp->position.y - cy->position.y)));
	out_intp->normal.z = 2 * cy->direction.y * (cy->direction.y \
					* (out_intp->position.z - cy->position.z) - cy->direction.z \
						* ((out_intp->position.y - cy->position.y))) \
						- 2 * cy->direction.x * (cy->direction.z \
					* (out_intp->position.x - cy->position.x) - cy->direction.x \
						* ((out_intp->position.z - cy->position.z)));
	out_intp->normal = norm_vec(out_intp->normal);
}
