/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:32:57 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 15:26:14 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	init_vec(float x, float y, float z)
{
	return ((t_vec){
		.x = x,
		.y = y,
		.z = z
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

float	inner_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	abs_vec(t_vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
