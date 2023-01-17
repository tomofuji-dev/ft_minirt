/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:32:57 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/17 11:51:09 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vec	init_vec(double x, double y, double z);
t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	diff_vec(t_vec v1, t_vec v2);
t_vec	norm_vec(t_vec v);
double	inner_product(t_vec v1, t_vec v2);
double	sum_of_squares(t_vec v);
double	abs_vec(t_vec v);
t_vec	constant_mul_vec(t_vec v, double c);

t_vec	init_vec(double x, double y, double z)
{
	return ((t_vec){
		.x = x,
		.y = y,
		.z = z
	});
}

void	set_vec(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vec	add_vec(t_vec v1, t_vec v2)
{
	return ((t_vec){
		.x = v1.x + v2.x,
		.y = v1.y + v2.y,
		.z = v1.z + v2.z
	});
}

t_vec	diff_vec(t_vec v1, t_vec v2)
{
	return ((t_vec){
		.x = v1.x - v2.x,
		.y = v1.y - v2.y,
		.z = v1.z - v2.z
	});
}

t_vec	norm_vec(t_vec v)
{
	double	abs;

	abs = abs_vec(v);
	return ((t_vec){
		.x = v.x / abs,
		.y = v.y / abs,
		.z = v.z / abs
	});
}

double	inner_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	sum_of_squares(t_vec v)
{
	return (inner_product(v, v));
}

double	abs_vec(t_vec v)
{
	return (sqrt(sum_of_squares(v)));
}

t_vec	constant_mul_vec(t_vec v, double c)
{
	return ((t_vec){
		.x = c * v.x,
		.y = c * v.y,
		.z = c * v.z
	});
}
