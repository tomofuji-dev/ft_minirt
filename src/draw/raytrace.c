/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:11:35 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/18 10:48:47 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "draw.h"
#include "color.h"
#include <math.h>
#include <stdio.h>

bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb)
{
	t_shape_intp	shape_intp;
	size_t		i;
	t_raytrace	vars;
	t_info		info;

	info.max_dist = INFINITY;
	info.exit_once_found = false;
	info.out_needed = true;
	if (get_nearest_shape(scene, eye_ray, info, &shape_intp))
	{
		rgb->r = scene->ambient_illuminance.r * shape_intp.shape->material.ambient_ref.r;
		rgb->g = scene->ambient_illuminance.g * shape_intp.shape->material.ambient_ref.g;
		rgb->b = scene->ambient_illuminance.b * shape_intp.shape->material.ambient_ref.b;
		i = 0;
		while (i < scene->num_lights)
		{
			if (scene->lights[i].type == LT_POINT)
			{
				vars.l = norm_vec(diff_vec(scene->lights[i].vector, \
											shape_intp.intp.position));
				vars.dl = abs_vec(diff_vec(scene->lights[i].vector, \
											shape_intp.intp.position)) - C_EPSILON;
			}
			else if (scene->lights[i].type == LT_DIRECTIONAL)
			{
				vars.l = norm_vec(constant_mul_vec(\
									scene->lights[i].vector, -1));
				vars.dl = INFINITY;
			}
			vars.shadow_ray.start = add_vec(shape_intp.intp.position, constant_mul_vec(vars.l, C_EPSILON));
			vars.shadow_ray.direction = vars.l;
			info.max_dist = vars.dl;
			info.exit_once_found = true;
			info.out_needed = true;
			if (get_nearest_shape(scene, &vars.shadow_ray, info, &shape_intp))
			{
				i++;
				continue ;
			}
			vars.nl_dot = inner_product(shape_intp.intp.normal, vars.l);
			vars.nl_dot = clamp(vars.nl_dot, 0, 1);
			add_on_rgb(rgb, shape_intp.shape->material.diffuse_ref, scene->lights[i], vars.nl_dot);
			if (vars.nl_dot > 0)
			{
				vars.r = norm_vec(diff_vec(constant_mul_vec(\
									shape_intp.intp.normal, 2 * vars.nl_dot), vars.l));
				vars.v = norm_vec(constant_mul_vec(\
										eye_ray->direction, -1));
				vars.vr_dot = inner_product(vars.v, vars.r);
				vars.vr_dot = clamp(vars.vr_dot, 0, 1);
				vars.vr_dot_pow = pow(vars.vr_dot, shape_intp.shape->material.shininess);
				add_on_rgb(rgb, shape_intp.shape->material.specular_ref, scene->lights[i], vars.vr_dot_pow);
			}
			i++;
		}
		rgb->r = 255 * clamp(rgb->r, 0, 1);
		rgb->g = 255 * clamp(rgb->g, 0, 1);
		rgb->b = 255 * clamp(rgb->b, 0, 1);
		return (true);
	}
	return (false);
}
