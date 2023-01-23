/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:12:45 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 11:16:09 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_math.h"
#include <math.h>

bool	intersect_plane(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp)
{
	const t_plane	*pln;
	double			dn_dot;
	double			t;
	t_vec			s_p;

	pln = &shape->u_data.plane;
	dn_dot = inner_product(ray->direction, pln->normal);
	if (dn_dot != 0)
	{
		s_p = diff_vec(ray->start, pln->position);
		t = -1 * inner_product(s_p, pln->normal) / dn_dot;
		if (t > 0)
		{
			if (out_intp)
			{
				out_intp->distance = t;
				out_intp->position = add_vec(ray->start, \
										constant_mul_vec(ray->direction, t));
				out_intp->normal = pln->normal;
			}
			return (true);
		}
		return (false);
	}
	return (false);
}
