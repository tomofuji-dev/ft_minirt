/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:59:15 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/18 13:24:33 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"

void	pixel_put(t_env *env, int x, int y, int color)
{
	char	*dst;

	dst = env->img_data + (y * env->bytes_per_line + x * env->bytes_per_pixel);
	*(int *)dst = color;
}

t_vec	screen_to_coord(t_env *env, int x, int y)
{
	t_vec	coord;

	coord = add_vec(env->scene->eye_pos, env->scene->eye_direction);
	coord.x -= (env->window_width / 2) * env->scene->pixel_width;
	coord.x += env->scene->pixel_width / 2;
	coord.x += env->scene->pixel_width * x;
	coord.y += (env->window_height / 2) * env->scene->pixel_height;
	coord.y -= env->scene->pixel_height / 2;
	coord.y -= env->scene->pixel_height * y;
	return (coord);
}
