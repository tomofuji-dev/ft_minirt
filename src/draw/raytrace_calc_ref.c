/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_calc_ref.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:21:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/25 11:18:49 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "draw.h"
#include "rt_math.h"
#include "color.h"
#include <math.h>

void			calc_ambient_ref(t_rgb *rgb, const t_scene *scene, t_rt *rt);
void			calc_diffuse_ref(t_rgb *rgb, t_rt *rt);
void			calc_specular_ref(t_rgb *rgb, const t_ray *eye_ray, t_rt *rt);
static t_rgb	calc_solid_rgb(t_shape_intp shape_intp);
static t_rgb	calc_solid_rgb_plane(t_shape_intp shape_intp);

void	calc_ambient_ref(t_rgb *rgb, const t_scene *scene, t_rt *rt)
{
	multiple_rgb(rgb, scene->ambient_illuminance, \
				rt->shape_intp.shape->material.ambient_ref);
}

void	calc_diffuse_ref(t_rgb *rgb, t_rt *rt)
{
	t_rgb	solid_rgb;

	rt->vars.nl_dot = inner_product(rt->shape_intp.intp.normal, rt->vars.l);
	rt->vars.nl_dot = rt_clamp(rt->vars.nl_dot, 0, 1);
	solid_rgb = calc_solid_rgb(rt->shape_intp);
	add_on_rgb(rgb, solid_rgb, \
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

static t_rgb	calc_solid_rgb(t_shape_intp shape_intp)
{
	if (shape_intp.shape->type == ST_PLANE)
		return (calc_solid_rgb_plane(shape_intp));
	else
		return (shape_intp.shape->material.diffuse_ref);
}

static t_rgb	calc_solid_rgb_plane(t_shape_intp shape_intp)
{
	t_shape	*shape;
	t_plane	pl;
	t_vec	vec_pl_to_intp;
	double	x;
	double	y;

	shape = shape_intp.shape;
	pl = shape->u_data.plane;
	if (shape->checker_board_w == 0)
		return (shape_intp.shape->material.diffuse_ref);
	vec_pl_to_intp = diff_vec(shape_intp.intp.position, pl.position);
	x = inner_product(vec_pl_to_intp, pl.basis.u) * shape->checker_board_w;
	y = inner_product(vec_pl_to_intp, pl.basis.v) * shape->checker_board_w;
	if (checker_board(x, y))
		return ((t_rgb){.r = 0.0, .g = 0.0, .b = 0.0});
	else
		return ((t_rgb){.r = 1.0, .g = 1.0, .b = 1.0});
}
