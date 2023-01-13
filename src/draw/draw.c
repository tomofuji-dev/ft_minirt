/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:47 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 18:17:41 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"
#include "util.h"
#include "math_utils.h"
#include <math.h>
#include <stdio.h>

void			draw(t_env *env);
static float	light_sphere(int x, int y);
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
			color = light_sphere(x, y);
			pixel_put(env, x, y, color);
			x++;
		}
		y++;
	}
}

static float	light_sphere(int x, int y)
{
	float	Ra, Rd, Rs, t, l_n, v_r, gray;
	t_vec	d, p, l, n, r, v;

	Ra = 0.01 * 0.1;
	t = intersect_sphere(x, y);
	if (t <= 0)
		return (encode_rgb(100, 149, 237));
	d = diff_vec(screen_to_coord(x, y), init_vec(0, 0, -5));
	p = add_vec(init_vec(0, 0, -5), constant_mul_vec(d, t));
	l = norm_vec(diff_vec(init_vec(-5, 5, -5), p));
	n = norm_vec(diff_vec(p, init_vec(0, 0, 5)));
	l_n = inner_product(l, n);
	if (l_n <= 0)
	{
		Rd = 0;
		Rs = 0;
	}
	else
	{
		Rd = 0.69 * 1.0 * l_n;
		r = diff_vec(constant_mul_vec(n, 2 * inner_product(l, n)), l);
		v = norm_vec(constant_mul_vec(d, -1));
		v_r = inner_product(v, r);
		if (v_r <= 0)
			v_r = 0;
		Rs = 0.3 * 1.0 * pow(v_r, 8);
	}
	gray = 255 * (Ra + Rd + Rs);
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
