/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_calc_ref.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:21:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 12:31:49 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "draw.h"
#include "rt_math.h"
#include "color.h"
#include <math.h>

void	calc_ambient_ref(t_rgb *rgb, const t_scene *scene, t_rt *rt);
void	calc_diffuse_ref(t_rgb *rgb, t_rt *rt);
void	calc_specular_ref(t_rgb *rgb, const t_ray *eye_ray, t_rt *rt);

void	calc_ambient_ref(t_rgb *rgb, const t_scene *scene, t_rt *rt)
{
	multiple_rgb(rgb, scene->ambient_illuminance, \
				rt->shape_intp.shape->material.ambient_ref);
}

void	calc_diffuse_ref(t_rgb *rgb, t_rt *rt)
{
	rt->vars.nl_dot = inner_product(rt->shape_intp.intp.normal, rt->vars.l);
	rt->vars.nl_dot = rt_clamp(rt->vars.nl_dot, 0, 1);
	add_on_rgb(rgb, rt->shape_intp.shape->material.diffuse_ref, \
				*rt->light, rt->vars.nl_dot);
}

void	calc_specular_ref(t_rgb *rgb, const t_ray *eye_ray, t_rt *rt)
{
	rt->vars.r = norm_vec(diff_vec(constant_mul_vec(\
							rt->shape_intp.intp.normal, 2 * rt->vars.nl_dot), \
							rt->vars.l));
	rt->vars.v = norm_vec(constant_mul_vec(eye_ray->direction, -1));
	rt->vars.vr_dot = inner_product(rt->vars.v, rt->vars.r);
	rt->vars.vr_dot = rt_clamp(rt->vars.vr_dot, 0, 1);
	rt->vars.vr_dot_pow = pow(rt->vars.vr_dot, \
							rt->shape_intp.shape->material.shininess);
	add_on_rgb(rgb, rt->shape_intp.shape->material.specular_ref, \
				*rt->light, rt->vars.vr_dot_pow);
}
