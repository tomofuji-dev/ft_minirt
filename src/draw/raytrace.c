/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:11:35 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/23 12:26:23 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_math.h"
#include "draw.h"
#include "color.h"
#include <math.h>

bool		raytrace(const t_scene *scene, \
					const t_ray *eye_ray, t_rgb *rgb);
static bool	is_in_shadow(const t_scene *scene, t_rt *rt);

static void	set_info(t_info *info, double max_dist, \
					bool exit_once_found, bool out_needed);

bool	raytrace(const t_scene *scene, \
					const t_ray *eye_ray, t_rgb *rgb)
{
	t_rt	rt;

	set_info(&rt.info, INFINITY, false, true);
	if (get_nearest_shape(scene, eye_ray, rt.info, &rt.shape_intp))
	{
		calc_ambient_ref(rgb, scene, &rt);
		rt.light = scene->light;
		while (rt.light != NULL)
		{
			if (is_in_shadow(scene, &rt))
				continue ;
			calc_diffuse_ref(rgb, &rt);
			if (rt.vars.nl_dot > 0)
				calc_specular_ref(rgb, eye_ray, &rt);
			rt.light = rt.light->next;
		}
		clamp_mul_rgb(rgb, 255);
		return (true);
	}
	return (false);
}

static bool	is_in_shadow(const t_scene *scene, t_rt *rt)
{
	if (rt->light->type == LT_POINT)
	{
		rt->vars.l = norm_vec(diff_vec(rt->light->vector, \
											rt->shape_intp.intp.position));
		rt->vars.dl = abs_vec(diff_vec(rt->light->vector, \
									rt->shape_intp.intp.position)) - C_EPSILON;
	}
	else if (rt->light->type == LT_DIRECTIONAL)
	{
		rt->vars.l = norm_vec(constant_mul_vec(\
									rt->light->vector, -1));
		rt->vars.dl = INFINITY;
	}
	rt->vars.shadow_ray.start = add_vec(rt->shape_intp.intp.position, \
								constant_mul_vec(rt->vars.l, C_EPSILON));
	rt->vars.shadow_ray.direction = rt->vars.l;
	set_info(&rt->info, rt->vars.dl, true, false);
	if (get_nearest_shape(scene, &rt->vars.shadow_ray, \
							rt->info, &rt->shape_intp))
	{
		rt->light = rt->light->next;
		return (true);
	}
	return (false);
}

static void	set_info(t_info *info, double max_dist, \
					bool exit_once_found, bool output_needed)
{
	info->max_dist = max_dist;
	info->exit_once_found = exit_once_found;
	info->output_needed = output_needed;
}
