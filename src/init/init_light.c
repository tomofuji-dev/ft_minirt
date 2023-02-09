/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:14:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/06 15:38:01 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "utils.h"
#include "error.h"

bool	init_ambient_light(t_scene *scene, char ***splited);
bool	init_light(t_scene *scene, char ***splited);
bool	init_camera(t_scene *scene, char ***splited);

bool	init_ambient_light(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 3;
	const size_t	dp_lens[3] = {1, 1, 3};
	double			ambient_light_ratio;
	t_rgb			rgb;

	if (scene->ambient_light_is_already_exist)
		return (print_err_return_false(ERR_AMBIENT_LIGHT));
	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!is_valid_double(splited[1][0], &ambient_light_ratio, 0.0, 1.0))
		return (false);
	if (!is_valid_rgb(splited[2], &rgb))
		return (false);
	scene->ambient_illuminance = calc_rgb_ratio(rgb, ambient_light_ratio);
	scene->ambient_light_is_already_exist = true;
	return (true);
}

bool	init_light(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 4;
	const size_t	dp_lens[4] = {1, 3, 1, 3};
	t_light			*light;
	double			light_ratio;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!append_light(scene))
		return (false);
	light = lst_last_light(scene->light);
	if (!is_valid_vec(splited[1], &light->vector, false))
		return (false);
	if (!is_valid_double(splited[2][0], &light_ratio, 0.0, 1.0))
		return (false);
	if (!is_valid_rgb(splited[3], &rgb))
		return (false);
	light->type = LT_POINT;
	light->illuminance = calc_rgb_ratio(rgb, light_ratio);
	return (true);
}

bool	init_camera(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 4;
	const size_t	dp_lens[4] = {1, 3, 3, 1};
	int				fov;

	if (scene->camera_is_already_exist)
		return (print_err_return_false(ERR_CAMERA));
	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!is_valid_vec(splited[1], &scene->eye_pos, false))
		return (false);
	if (!is_valid_vec(splited[2], &scene->eye_direction, true))
		return (false);
	if (!is_valid_int(splited[3][0], &fov, 0, 180))
		return (false);
	if (fov == 0 || fov == 180)
		return (print_err_return_false(ERR_RANGE));
	scene->fov = (double)fov;
	scene->camera_is_already_exist = true;
	return (true);
}
