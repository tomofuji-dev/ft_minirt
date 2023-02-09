/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_in_shape.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:40:46 by hommayunosu       #+#    #+#             */
/*   Updated: 2023/02/07 16:41:32 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minirt.h"
#include "rt_math.h"

bool		is_camera_in_shape(t_scene *scene, t_shape *shape);
static bool	is_camera_in_sphere(t_scene *scene, t_sphere *sphere);
static bool	is_camera_in_cylinder(t_scene *scene, t_cylinder *cy);

bool	is_camera_in_shape(t_scene *scene, t_shape *shape)
{
	if (shape->type == ST_SPHERE)
		return (is_camera_in_sphere(scene, &shape->u_data.sphere));
	if (shape->type == ST_CYLINDER)
		return (is_camera_in_cylinder(scene, &shape->u_data.cylinder));
	return (false);
}

static bool	is_camera_in_sphere(t_scene *scene, t_sphere *sphere)
{
	double	dist_to_center;

	dist_to_center = abs_vec(diff_vec(scene->eye_pos, sphere->center));
	if (dist_to_center <= sphere->radius)
		return (true);
	return (false);
}

static bool	is_camera_in_cylinder(t_scene *scene, t_cylinder *cy)
{
	double	shortest_dist_to_axis;
	double	h;

	h = inner_product(diff_vec(scene->eye_pos, cy->position), cy->direction);
	if (-cy->height / 2 <= h && h <= cy->height / 2)
	{
		shortest_dist_to_axis = abs_vec(diff_vec(scene->eye_pos, \
			add_vec(cy->position, constant_mul_vec(norm_vec(cy->direction), \
			inner_product(diff_vec(scene->eye_pos, cy->position), \
			norm_vec(cy->direction))))));
		if (shortest_dist_to_axis <= cy->radius)
			return (true);
	}
	return (false);
}
