/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 17:35:13 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"
#include "util.h"
#include "math_utils.h"
#include <math.h>
#include <stdio.h>

void			draw(t_env *env);
static int		diffuse_reflected_sphere(int x, int y);
static float	intersect_sphere(int x, int y);

void	draw(t_env *env)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = diffuse_reflected_sphere(x, y);
			pixel_put(env, x, y, color);
			x++;
		}
		y++;
	}
}

static int	diffuse_reflected_sphere(int x, int y)
{
	float	t, nl_product, gray;
	t_vec	d, p, l, n;

	t = intersect_sphere(x, y);
	if (t <= 0)
		return (encode_rgb(100, 149, 237));
	d = diff_vec(screen_to_coord(x, y), init_vec(0, 0, -5));
	p = add_vec(init_vec(0, 0, -5), constant_mul_vec(d, t));
	l = norm_vec(diff_vec(init_vec(-5, 5, -5), p));
	n = norm_vec(diff_vec(p, init_vec(0, 0, 5)));
	nl_product = inner_product(l, n);
	if (nl_product <= 0)
		gray = 0;
	else
		gray = 255 * nl_product;
	return (encode_rgb(gray, gray, gray));
}

static float	intersect_sphere(int x, int y)
{
	t_vec	s, d;
	float	r, A, B, C, D, t1, t2;

	s = diff_vec(init_vec(0, 0, -5), init_vec(0, 0, 5));
	d = diff_vec(screen_to_coord(x, y), init_vec(0, 0, -5));
	r = 1;
	A = abs_vec(d);
	B = 2 * inner_product(s, d);
	C = abs_vec(s) - r * r;
	D = B * B - 4 * A * C;
	if (D > 0)
	{
		t1 = (-B + sqrt(D)) / (2 * A);
		t2 = (-B - sqrt(D)) / (2 * A);
		if (t1 > 0 && t2 > 0)
			return (min(t1, t2));
		else
			return (max(t1, t2));
	}
	if (D == 0)
		return (-B / (2 * A));
	return (-1);
}
