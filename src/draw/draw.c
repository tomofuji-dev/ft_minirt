/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/02/09 10:43:24 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"
#include "rt_math.h"

void			draw(t_env *env);
static t_vec	eye_ray_direction(t_env *env, int x, int y);
static void		pixel_put(t_env *env, int x, int y, int color);

void	draw(t_env *env)
{
	int		x;
	int		y;
	t_ray	eye_ray;
	t_rgb	rgb;

	y = 0;
	while (y < env->window_height)
	{
		x = 0;
		while (x < env->window_width)
		{
			eye_ray.start = env->scene->eye_pos;
			eye_ray.direction = eye_ray_direction(env, x, y);
			set_trgb(&rgb, 0, 0, 0);
			raytrace(env->scene, &eye_ray, &rgb);
			pixel_put(env, x, y, encode_trgb(rgb));
			x++;
		}
		y++;
	}
}

static t_vec	eye_ray_direction(t_env *env, int x, int y)
{
	t_vec	c;
	t_vec	u;
	t_vec	v;

	c = constant_mul_vec(env->scene->basis.c, -1);
	u = env->scene->basis.u;
	v = env->scene->basis.v;
	return (norm_vec(\
				add_vec(\
					c, \
					add_vec(\
						constant_mul_vec(u, (x - env->window_width / 2)), \
						constant_mul_vec(v, (-y + env->window_height / 2)) \
					) \
				) \
			));
}

static void	pixel_put(t_env *env, int x, int y, int color)
{
	char	*dst;

	dst = env->img_data + (y * env->bytes_per_line + x * env->bytes_per_pixel);
	*(int *)dst = color;
}
