/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 11:24:10 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "rt_math.h"
#include <math.h>

bool	intersect(const t_shape *shape, const t_ray *ray, \
					t_intersect *out_intp);
bool	set_output(t_shape *nearest_shape, t_intersect nearest_intp, \
					t_info info, t_shape_intp *shape_intp);

bool	get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							t_info info, t_shape_intp *shape_intp)
{
	t_shape		*nearest_shape;
	t_intersect	nearest_intp;
	t_intersect	intp;
	t_shape		*shape;

	nearest_shape = NULL;
	nearest_intp.distance = info.max_dist;
	shape = scene->shape;
	while (shape != NULL)
	{
		if (intersect(shape, ray, &intp) && \
			intp.distance < nearest_intp.distance)
		{
			nearest_shape = shape;
			nearest_intp = intp;
			if (info.exit_once_found)
				break ;
		}
		shape = shape->next;
	}
	return (set_output(nearest_shape, nearest_intp, info, shape_intp));
}

bool	intersect(const t_shape *shape, const t_ray *ray, t_intersect *out_intp)
{
	if (shape->type == ST_SPHERE)
		return (intersect_sphere(shape, ray, out_intp));
	else if (shape->type == ST_PLANE)
		return (intersect_plane(shape, ray, out_intp));
	else if (shape->type == ST_CYLINDER)
		return (intersect_cylinder(shape, ray, out_intp));
	return (false);
}

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

void	process_discrim(t_discrim *d)
{
	d->t = -1.0f;
	if (d->d == 0)
		d->t = -d->b / (2 * d->a);
	else if (d->d > 0)
	{
		d->t1 = (-d->b + sqrt(d->d)) / (2 * d->a);
		d->t2 = (-d->b - sqrt(d->d)) / (2 * d->a);
		if (d->t1 > 0)
			d->t = d->t1;
		if (d->t2 > 0 && d->t2 < d->t)
			d->t = d->t2;
	}
}

bool	set_output(t_shape *nearest_shape, t_intersect nearest_intp, \
					t_info info, t_shape_intp *shape_intp)
{
	if (nearest_shape)
	{
		if (info.output_needed)
		{
			shape_intp->shape = nearest_shape;
			shape_intp->intp = nearest_intp;
		}
		return (true);
	}
	return (false);
}
