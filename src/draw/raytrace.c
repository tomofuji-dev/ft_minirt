/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:11:35 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 19:01:49 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "draw.h"
#include <math.h>
#include <stdio.h>

bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb)
{
	t_shape		*shape;
	t_intersect	intp;
	size_t		i;
	t_raytrace	vars;

	if (get_nearest_shape(scene, eye_ray, INFINITY, false, &shape, &intp))
	{
		rgb->r = scene->ambient_illuminance.r * shape->material.ambient_ref.r;
		rgb->g = scene->ambient_illuminance.g * shape->material.ambient_ref.g;
		rgb->b = scene->ambient_illuminance.b * shape->material.ambient_ref.b;
		i = 0;
		while (i < scene->num_lights)
		{
			if (scene->lights[i].type == LT_POINT)
				vars.l = norm_vec(diff_vec(scene->lights[i].vector, \
											intp.position));
			else if (scene->lights[i].type == LT_DIRECTIONAL)
				vars.l = norm_vec(constant_mul_vec(\
									scene->lights[i].vector, -1));
			vars.nl_dot = inner_product(intp.normal, vars.l);
			vars.nl_dot = clamp(vars.nl_dot, 0, 1);
			rgb->r += shape->material.diffuse_ref.r * scene->lights[i].illuminance.r * vars.nl_dot;
			rgb->g += shape->material.diffuse_ref.g * scene->lights[i].illuminance.g * vars.nl_dot;
			rgb->b += shape->material.diffuse_ref.b * scene->lights[i].illuminance.b * vars.nl_dot;
			if (vars.nl_dot > 0)
			{
				vars.r = norm_vec(diff_vec(constant_mul_vec(\
									intp.normal, 2 * vars.nl_dot), vars.l));
				vars.v = norm_vec(constant_mul_vec(\
										eye_ray->direction, -1));
				vars.vr_dot = inner_product(vars.v, vars.r);
				vars.vr_dot = clamp(vars.vr_dot, 0, 1);
				vars.vr_dot_pow = pow(vars.vr_dot, shape->material.shininess);
				rgb->r += shape->material.specular_ref.r * scene->lights[i].illuminance.r * vars.vr_dot_pow;
				rgb->g += shape->material.specular_ref.g * scene->lights[i].illuminance.g * vars.vr_dot_pow;
				rgb->b += shape->material.specular_ref.b * scene->lights[i].illuminance.b * vars.vr_dot_pow;
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
