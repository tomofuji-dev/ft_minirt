/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:12:58 by hommayunosu       #+#    #+#             */
/*   Updated: 2023/01/25 14:13:16 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "rt_math.h"
#include <math.h>

static t_discrim	intersect_cone_discrim(const t_shape *shape, \
										const t_ray *ray);
static void	set_out_intp_cone(t_intersect *out_intp, const t_cone *cone, \
							const t_ray *ray, t_discrim d);

bool	intersect_cone(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_cone	*cone;
	t_discrim		d;

	//判別式を計算
	d = intersect_cone_discrim(shape, ray);
	//tが0より大きい時、つまり物体があるとき
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

static t_discrim	intersect_cone_discrim(const t_shape *shape, \
										const t_ray *ray)
{
	const t_cone	*cone;
	t_vec			pe_pc; //pe:視点位置 pc:円錐のトップ
	t_discrim		d;

	cone = &shape->u_data.cone;
	pe_pc = diff_vec(ray->start, cone->position);
	d.a = inner_product(ray->direction, ray->direction) \
			- pow(inner_product(cone->direction, ray->direction), 2) \
			- pow(cone->radius, 2) / pow(cone->height, 2) * inner_product(cone->direction, ray->direction);
	d.b = 2 * (inner_product(ray->direction, pe_pc) \
				- inner_product(ray->direction, cone->direction) \
				* inner_product(pe_pc, cone->direction)) \
				- pow(cone->radius, 2) / pow(cone->height, 2) * inner_product(pe_pc, cone->direction) * inner_product(cone->direction, ray->direction);
	d.c = inner_product(pe_pc, pe_pc) \
			- pow(inner_product(pe_pc, cone->direction), 2) \
			- pow(cone->radius, 2 \
			- pow(cone->radius, 2) / pow(cone->height, 2) * pow(inner_product(pe_pc, cone->direction), 2));
	d.d = d.b * d.b - 4 * d.a * d.c;
	process_discrim(&d);
	//d.m?
	return (d);
}

static void	set_out_intp_cone(t_intersect *out_intp, const t_cone *cone, \
							const t_ray *ray, t_discrim d)
{
	out_intp->distance = d.t;
	out_intp->position = add_vec(ray->start, \
								constant_mul_vec(ray->direction, d.t));
	out_intp->normal.x = 2 * cone->direction.z * (cone->direction.z \
					* (out_intp->position.x - cone->position.x) - cone->direction.x \
						* ((out_intp->position.z - cone->position.z))) \
						- 2 * cone->direction.y * (cone->direction.x \
					* (out_intp->position.y - cone->position.y) - cone->direction.y \
						* ((out_intp->position.x - cone->position.x)));
	out_intp->normal.y = 2 * cone->direction.x * (cone->direction.x \
					* (out_intp->position.y - cone->position.y) - cone->direction.y \
						* ((out_intp->position.x - cone->position.x))) \
						- 2 * cone->direction.z * (cone->direction.y \
					* (out_intp->position.z - cone->position.z) - cone->direction.z \
						* ((out_intp->position.y - cone->position.y)));
	out_intp->normal.z = 2 * cone->direction.y * (cone->direction.y \
					* (out_intp->position.z - cone->position.z) - cone->direction.z \
						* ((out_intp->position.y - cone->position.y))) \
						- 2 * cone->direction.x * (cone->direction.z \
					* (out_intp->position.x - cone->position.x) - cone->direction.x \
						* ((out_intp->position.z - cone->position.z)));
//	printf("[%lf]\n", out_intp->normal.x);
	out_intp->normal = norm_vec(out_intp->normal);
}