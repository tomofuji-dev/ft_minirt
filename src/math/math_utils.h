/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:33:29 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/13 17:35:05 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

t_vec	init_vec(float x, float y, float z);
t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	diff_vec(t_vec v1, t_vec v2);
t_vec	norm_vec(t_vec v);
float	inner_product(t_vec v1, t_vec v2);
float	abs_vec(t_vec v);
t_vec	constant_mul_vec(t_vec v, float c);

float	min(float x, float y);
float	max(float x, float y);

#endif