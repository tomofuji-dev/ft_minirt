/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:35:43 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"
#include "util.h"
#include "init.h"
#include "math_utils.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void	draw(t_env *env);

void	draw(t_env *env)
{
	int		x;
	int		y;
	t_ray	eye_ray;
	t_rgb	rgb;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			eye_ray.start = env->scene->eye_pos;
			eye_ray.direction = diff_vec(screen_to_coord(x, y), eye_ray.start);
			set_trgb(&rgb, 100, 149, 237);
			raytrace(env->scene, &eye_ray, &rgb);
			pixel_put(env, x, y, encode_trgb(rgb));
			x++;
		}
		y++;
	}
}
