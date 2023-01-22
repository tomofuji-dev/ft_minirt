/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:17:59 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/22 11:25:42 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_math.h"
#include <math.h>

t_vec	init_vec(double x, double y, double z);
t_vec	norm_vec(t_vec v);
double	sum_of_squares(t_vec v);
double	abs_vec(t_vec v);

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

double	sum_of_squares(t_vec v)
{
	return (inner_product(v, v));
}

double	abs_vec(t_vec v)
{
	return (sqrt(sum_of_squares(v)));
}
