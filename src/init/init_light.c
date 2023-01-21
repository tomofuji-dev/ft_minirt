/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:14:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 13:38:52 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "utils.h"
#include "color.h"

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
		return (false);
	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!rt_strtod(splited[1][0], &ambient_light_ratio))
		return (false);
	if (!(0.0 <= ambient_light_ratio && ambient_light_ratio <= 1.0))
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
	if (!rt_strtod(splited[2][0], &light_ratio))
		return (false);
	if (!(0.0 <= light_ratio && light_ratio <= 1.0))
		return (false);
	if (!is_valid_rgb(splited[3], &rgb))
		return (false);
	scene->light->type = LT_POINT;
	scene->light->illuminance = calc_rgb_ratio(rgb, light_ratio);
	return (true);
}

bool	init_camera(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 4;
	const size_t	dp_lens[4] = {1, 3, 3, 1};
	int				fov;

	if (scene->camera_is_already_exist)
		return (false);
	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!is_valid_vec(splited[1], &scene->eye_pos, false))
		return (false);
	if (!is_valid_vec(splited[2], &scene->eye_direction, true))
		return (false);
	if (!rt_atoi(splited[3][0], &fov))
		return (false);
	if (!(0 <= fov && fov <= 180))
		return (false);
	scene->fov = (double)fov;
	scene->camera_is_already_exist = true;
	return (true);
}
