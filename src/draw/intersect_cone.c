/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:12:58 by hommayunosu       #+#    #+#             */
/*   Updated: 2023/02/03 12:51:16 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "rt_math.h"
#include <math.h>

static t_discrim	intersect_cone_discrim(const t_shape *shape, \
										const t_ray *ray);
static void			set_out_intp_cone(t_intersect *out_intp, \
									const t_cone *cone, \
									const t_ray *ray, t_discrim d);

static void			set_discrim_structure(t_discrim *d, \
										const t_cone *cone, const t_ray *ray);

bool	intersect_cone(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_cone	*cone;
	t_discrim		d;

	d = intersect_cone_discrim(shape, ray);
	cone = &shape->u_data.cone;
	if (d.t > 0)
	{
		if (out_intp)
			set_out_intp_cone(out_intp, cone, ray, d);
		return (true);
	}
	else
		return (false);
}

/*
 * Δp = (p-pa)•cos^2α|vt+Δp-(va•(vt+Δp)va)|^2 - sin^2α|va•(vt+Δp)|^2 = 0
 * a = cos^2α|v-(v•va)va|^2-sin^2α|v•va|^2
 * b = 2cos^2α((v-(v•va)va)•(Δp-(Δp•va)va))-2sin^2α(v•va)(Δp•va)
 * c = con^2α|Δp-(Δp•va)va|^2-sin^2α|Δp•va|^2
 */

static t_discrim	intersect_cone_discrim(const t_shape *shape, \
										const t_ray *ray)
{
	const t_cone	*cone;
	t_discrim		d;
	double			distance_to_intersect;

	cone = &shape->u_data.cone;
	set_discrim_structure(&d, cone, ray);
	process_discrim(&d);
	distance_to_intersect = abs_vec(diff_vec(add_vec(ray->start, \
		constant_mul_vec(ray->direction, d.t)), cone->position));
	if (distance_to_intersect < -cone->height \
		|| distance_to_intersect > cone->height)
		d.t = -1;
	return (d);
}

static void	set_discrim_structure(t_discrim *d, \
								const t_cone *cone, const t_ray *ray)
{
	t_vec			pe_pc;
	double			sin2;
	double			cos2;

	sin2 = pow(cone->radius, 2) / (pow(cone->radius, 2) + pow(cone->height, 2));
	cos2 = pow(cone->height, 2) / (pow(cone->radius, 2) + pow(cone->height, 2));
	pe_pc = diff_vec(ray->start, cone->position);
	d->a = cos2 * sum_of_squares(diff_vec(ray->direction, \
		constant_mul_vec(cone->direction, \
		inner_product(ray->direction, cone->direction)))) \
		- sin2 * pow(inner_product(ray->direction, cone->direction), 2);
	d->b = 2 * cos2 * (inner_product(diff_vec(ray->direction, \
		constant_mul_vec(cone->direction, \
		inner_product(ray->direction, cone->direction))), \
		diff_vec(pe_pc, constant_mul_vec(cone->direction, \
		inner_product(pe_pc, cone->direction))))) \
			- 2 * sin2 * inner_product(ray->direction, cone->direction) \
			* inner_product(pe_pc, cone->direction);
	d->c = cos2 * sum_of_squares(diff_vec(pe_pc, \
		constant_mul_vec(cone->direction, \
		inner_product(pe_pc, cone->direction)))) \
		- sin2 * pow(inner_product(pe_pc, cone->direction), 2);
	d->d = d->b * d->b - 4 * d->a * d->c;
}

static void	set_out_intp_cone(t_intersect *out_intp, const t_cone *cone, \
							const t_ray *ray, t_discrim d)
{
	out_intp->distance = d.t;
	out_intp->position = add_vec(ray->start, \
								constant_mul_vec(ray->direction, d.t));
	out_intp->normal.x = \
		2 * cone->direction.z * (cone->direction.z * (out_intp->position.x \
		- cone->position.x) - cone->direction.x * ((out_intp->position.z \
		- cone->position.z))) - 2 * cone->direction.y * (cone->direction.x \
		* (out_intp->position.y - cone->position.y) - cone->direction.y \
		* ((out_intp->position.x - cone->position.x)));
	out_intp->normal.y = \
		2 * cone->direction.x * (cone->direction.x * (out_intp->position.y \
		- cone->position.y) - cone->direction.y * ((out_intp->position.x \
		- cone->position.x))) - 2 * cone->direction.z * (cone->direction.y \
		* (out_intp->position.z - cone->position.z) - cone->direction.z \
		* ((out_intp->position.y - cone->position.y)));
	out_intp->normal.z = \
		2 * cone->direction.y * (cone->direction.y * (out_intp->position.z \
		- cone->position.z) - cone->direction.z * ((out_intp->position.y \
		- cone->position.y))) - 2 * cone->direction.x * (cone->direction.z \
		* (out_intp->position.x - cone->position.x) - cone->direction.x \
		* ((out_intp->position.z - cone->position.z)));
	out_intp->normal = norm_vec(out_intp->normal);
}
