/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 15:52:18 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"
#include "util.h"
#include "vec.h"
#include <stdio.h>

void		draw(t_env *env);
static bool	is_cross_with_sphere(t_vec s, t_vec d, float r);

void	draw(t_env *env)
{
	int		x;
	int		y;
	t_vec	s;
	t_vec	d;
	float	r;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			s = init_vec(0, 0, -5);
			d = diff_vec(screen_to_coord(x, y), s);
			r = 0.5;
			if (is_cross_with_sphere(s, d, r))
				pixel_put(env, x, y, encode_rgb(255, 0, 0));
			else
				pixel_put(env, x, y, encode_rgb(0, 0, 255));
			x++;
		}
		y++;
	}
}

static bool	is_cross_with_sphere(t_vec s, t_vec d, float r)
{
	float	a;
	float	b;
	float	c;

	a = abs_vec(d);
	b = 2 * inner_product(s, d);
	c = abs_vec(s) - r * r;
	return (b * b - 4 * a * c >= 0);
}
