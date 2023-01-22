/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:32:57 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 17:54:36 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_math.h"

t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	diff_vec(t_vec v1, t_vec v2);
double	inner_product(t_vec v1, t_vec v2);
t_vec	outer_product(t_vec v1, t_vec v2);
t_vec	constant_mul_vec(t_vec v, double c);

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

double	inner_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	outer_product(t_vec v1, t_vec v2)
{
	return ((t_vec){
		.x = v1.y * v2.z - v1.z * v2.y,
		.y = v1.z * v2.x - v1.x * v2.z,
		.z = v1.x * v2.y - v1.y * v2.x,
	});
}

t_vec	constant_mul_vec(t_vec v, double c)
{
	return ((t_vec){
		.x = c * v.x,
		.y = c * v.y,
		.z = c * v.z
	});
}
