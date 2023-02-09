/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:01:53 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/03 13:13:59 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "rt_math.h"
#include <math.h>

bool		init_sphere(t_scene *scene, char ***splited);
bool		init_plane(t_scene *scene, char ***splited);
bool		init_cylinder(t_scene *scene, char ***splited);
bool		init_cone(t_scene *scene, char ***splited);
static void	set_basis_plane(t_plane *pl, t_scene *scene);

bool	init_sphere(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 4;
	const size_t	dp_lens[4] = {1, 3, 1, 3};
	t_shape			*shape;
	t_sphere		*sph;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_lens) \
		|| !append_shape(scene))
		return (false);
	shape = lst_last_shape(scene->shape);
	shape->type = ST_SPHERE;
	sph = &shape->u_data.sphere;
	if (!is_valid_vec(splited[1], &sph->center, false) \
		|| !is_valid_double(splited[2][0], &sph->radius, 0.0, INFINITY))
		return (false);
	if (!is_valid_rgb(splited[3], &rgb))
		return (false);
	sph->radius /= 2;
	shape->material.diffuse_ref = calc_rgb_ratio(rgb, 1.0);
	default_material(&shape->material);
	shape->checker_board_w = 0;
	return (true);
}

bool	init_plane(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 5;
	const size_t	dp_lens[5] = {1, 3, 3, 3, 1};
	t_shape			*shape;
	t_plane			*pl;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_lens) \
		|| !append_shape(scene))
		return (false);
	shape = lst_last_shape(scene->shape);
	shape->type = ST_PLANE;
	pl = &shape->u_data.plane;
	if (!is_valid_vec(splited[1], &pl->position, false) \
		|| !is_valid_vec(splited[2], &pl->normal, true))
		return (false);
	if (!is_valid_rgb(splited[3], &rgb))
		return (false);
	if (!is_valid_double(splited[4][0], &shape->checker_board_w, 0.0, INFINITY))
		return (false);
	if (shape->checker_board_w != 0.0)
		set_basis_plane(pl, scene);
	shape->material.diffuse_ref = calc_rgb_ratio(rgb, 1.0);
	default_material(&shape->material);
	return (true);
}

bool	init_cylinder(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 6;
	const size_t	dp_lens[6] = {1, 3, 3, 1, 1, 3};
	t_shape			*shape;
	t_cylinder		*cy;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_lens) \
		|| !append_shape(scene))
		return (false);
	shape = lst_last_shape(scene->shape);
	shape->type = ST_CYLINDER;
	cy = &shape->u_data.cylinder;
	if (!is_valid_vec(splited[1], &cy->position, false) \
		|| !is_valid_vec(splited[2], &cy->direction, true) \
		|| !is_valid_double(splited[3][0], &cy->radius, 0.0, INFINITY) \
		|| !is_valid_double(splited[4][0], &cy->height, 0.0, INFINITY))
		return (false);
	if (!is_valid_rgb(splited[5], &rgb))
		return (false);
	cy->radius /= 2;
	shape->material.diffuse_ref = calc_rgb_ratio(rgb, 1.0);
	default_material(&shape->material);
	shape->checker_board_w = 0;
	return (true);
}

bool	init_cone(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 6;
	const size_t	dp_len[6] = {1, 3, 3, 1, 1, 3};
	t_shape			*shape;
	t_cone			*cone;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_len) \
		|| !append_shape(scene))
		return (false);
	shape = lst_last_shape(scene->shape);
	shape->type = ST_CONE;
	cone = &shape->u_data.cone;
	if (!is_valid_vec(splited[1], &cone->position, false) \
		|| !is_valid_vec(splited[2], &cone->direction, true) \
		|| !is_valid_double(splited[3][0], &cone->radius, 0.0, INFINITY) \
		|| !is_valid_double(splited[4][0], &cone->height, 0.0, INFINITY))
		return (false);
	if (!is_valid_rgb(splited[5], &rgb))
		return (false);
	cone->radius /= 2;
	shape->material.diffuse_ref = calc_rgb_ratio(rgb, 1.0);
	default_material(&shape->material);
	return (true);
}

static void	set_basis_plane(t_plane *pl, t_scene *scene)
{
	pl->basis.c = diff_vec(pl->position, scene->eye_pos);
	calc_basis(&pl->basis);
}
