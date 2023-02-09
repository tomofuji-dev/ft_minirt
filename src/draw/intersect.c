/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 12:24:55 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

bool		get_nearest_shape(const t_scene *scene, const t_ray *ray, \
							t_info info, t_shape_intp *shape_intp);
static bool	intersect(const t_shape *shape, const t_ray *ray, \
						t_intersect *out_intp);

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
	if (set_output(nearest_shape, nearest_intp, info, shape_intp))
		return (true);
	return (false);
}

static bool	intersect(const t_shape *shape, \
						const t_ray *ray, t_intersect *out_intp)
{
	if (shape->type == ST_SPHERE)
		return (intersect_sphere(shape, ray, out_intp));
	else if (shape->type == ST_PLANE)
		return (intersect_plane(shape, ray, out_intp));
	else if (shape->type == ST_CYLINDER)
		return (intersect_cylinder(shape, ray, out_intp));
	else if (shape->type == ST_CONE)
		return (intersect_cone(shape, ray, out_intp));
	return (false);
}
