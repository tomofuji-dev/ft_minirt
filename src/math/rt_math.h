/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:33:29 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/21 17:54:45 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

// init_vec.c
t_vec	init_vec(double x, double y, double z);
t_vec	norm_vec(t_vec v);
double	sum_of_squares(t_vec v);
double	abs_vec(t_vec v);
// vec.c
t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	diff_vec(t_vec v1, t_vec v2);
double	inner_product(t_vec v1, t_vec v2);
t_vec	outer_product(t_vec v1, t_vec v2);
t_vec	constant_mul_vec(t_vec v, double c);
// utils.c
double	rt_min(double x, double y);
double	rt_max(double x, double y);
double	rt_clamp(double f, double min, double max);
double	rand_range(double a, double b);

#endif